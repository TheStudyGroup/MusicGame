#include <math.h>
#ifndef M_PI
#define M_PI 3.141592f
#endif

#include "Tone.h"

#define PCLK_DAC_IN_MHZ   25 //CCLK divided by 4
#define TONE_SAMPLE_COUNT 512

Bool     __Tone_Status = FALSE;
uint32_t __Tone_DacSamples[TONE_SAMPLE_COUNT]; // 2 KB


GPDMA_LLI_Type         __Tone_DmaLinkListItem;
GPDMA_Channel_CFG_Type __Tone_GpdmaCfg;

void Tone_Init(void) {
    AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_26, PINSEL_FUNC_2); //	P0.26 Pin AF Configuration (DAC)
    DAC_Init(LPC_DAC);

    __Tone_GenerateSineWave();
    __Tone_DmaInit();
}

void Tone_PlaySineWave(uint32_t frequency) {
    uint32_t clockPerSample = (float)(SystemCoreClock / 4) / (float)frequency / TONE_SAMPLE_COUNT;
    // uint32_t clockPerSample = (PCLK_DAC_IN_MHZ * 1000000) / frequency / TONE_SAMPLE_COUNT;

    DAC_CONVERTER_CFG_Type dacConfig;
    dacConfig.CNT_ENA = SET; //	Auto Reload
    dacConfig.DMA_ENA = SET; // Use DMA in DAC

    Tone_Stop();
    DAC_SetDMATimeOut(LPC_DAC, clockPerSample - 1);
    DAC_ConfigDAConverterControl(LPC_DAC, &dacConfig);
    GPDMA_ChannelCmd(0, ENABLE);
    __Tone_Status = TRUE;
}

void Tone_Stop(void) {
    if (__Tone_Status) {
        GPDMA_ChannelCmd(0, DISABLE);
    }
    __Tone_Status = FALSE;
}

Bool Tone_IsPlaying(void) {
    return __Tone_Status;
}


void __Tone_GenerateSineWave(void) {
    uint32_t i;
    for (i = 0; i < TONE_SAMPLE_COUNT; i++) {
        __Tone_DacSamples[i] = 512.0f + 512.0f * sinf((float)i * (2.0f * M_PI / TONE_SAMPLE_COUNT));
        // __Tone_DacSamples[i] = 32767.5f + 32767.5f * sinf((float)i * (2.0f * M_PI / TONE_SAMPLE_COUNT));
        __Tone_DacSamples[i] = DAC_VALUE(__Tone_DacSamples[i]);
    }
}

void __Tone_DmaInit(void) {
    // Prepare DMA Link-List-Item structure
    __Tone_DmaLinkListItem.SrcAddr = (uint32_t)__Tone_DacSamples;
    __Tone_DmaLinkListItem.DstAddr = (uint32_t)&(LPC_DAC->DACR);
    __Tone_DmaLinkListItem.NextLLI = (uint32_t)&__Tone_DmaLinkListItem;
    __Tone_DmaLinkListItem.Control = TONE_SAMPLE_COUNT // [11:00] Transfer Size (manual p.577)
                            | (2 << 18)        // [20:18] Source Transfer Width (2=32bit)
                            | (2 << 21)        // [23:21] Destination Transfer Width (2=32bit)
                            | (1 << 26);       // [26]    Source Increment (1=true)

    GPDMA_Init();
    __Tone_GpdmaCfg.ChannelNum    = 0;                                 // Channel 0
    __Tone_GpdmaCfg.SrcMemAddr    = (uint32_t)(__Tone_DacSamples);     // Source memory
    __Tone_GpdmaCfg.DstMemAddr    = 0; // (unused)
    __Tone_GpdmaCfg.TransferSize  = TONE_SAMPLE_COUNT;                 // Transfer size
    __Tone_GpdmaCfg.TransferWidth = 0; // (unused)
    __Tone_GpdmaCfg.TransferType  = GPDMA_TRANSFERTYPE_M2P;            // Transfer type
    __Tone_GpdmaCfg.SrcConn       = 0; // (unused)
    __Tone_GpdmaCfg.DstConn       = GPDMA_CONN_DAC;                    // Destination connection
    __Tone_GpdmaCfg.DMALLI        = (uint32_t)&__Tone_DmaLinkListItem; // Linker List Item - unused
    GPDMA_Setup(&__Tone_GpdmaCfg); // Setup channel with given parameter
}
