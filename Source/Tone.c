#include <math.h>
#ifndef M_PI
#define M_PI 3.141592f
#endif

#include "Tone.h"

#define TONE_SAMPLE_COUNT 512

uint32_t Tone_State = 0;  // play state
uint32_t Samples_Sine[TONE_SAMPLE_COUNT]; // 2 KB
uint32_t Samples_DAC [TONE_SAMPLE_COUNT]; // 2 KB
GPDMA_LLI_Type         dmaLinkListItem;
GPDMA_Channel_CFG_Type gpdmaConfig;

static void Tone_DmaInit(void) {
    // Prepare DMA Link-List-Item structure
    dmaLinkListItem.SrcAddr = (uint32_t)Samples_DAC;
    dmaLinkListItem.DstAddr = (uint32_t)&(LPC_DAC->DACR);
    dmaLinkListItem.NextLLI = (uint32_t)&dmaLinkListItem;
    dmaLinkListItem.Control = TONE_SAMPLE_COUNT // [11:00] Transfer Size (manual p.577)
                            | (2 << 18)        // [20:18] Source Transfer Width (2=32bit)
                            | (2 << 21)        // [23:21] Destination Transfer Width (2=32bit)
                            | (1 << 26);       // [26]    Source Increment (1=true)

    GPDMA_Init();
    gpdmaConfig.ChannelNum    = 0;                          // Channel 0
    gpdmaConfig.SrcMemAddr    = (uint32_t)(Samples_DAC);     // Source memory
    gpdmaConfig.DstMemAddr    = 0; // (unused)
    gpdmaConfig.TransferSize  = TONE_SAMPLE_COUNT;          // Transfer size
    gpdmaConfig.TransferWidth = 0; // (unused)
    gpdmaConfig.TransferType  = GPDMA_TRANSFERTYPE_M2P;     // Transfer type
    gpdmaConfig.SrcConn       = 0; // (unused)
    gpdmaConfig.DstConn       = GPDMA_CONN_DAC;             // Destination connection
    gpdmaConfig.DMALLI        = (uint32_t)&dmaLinkListItem; // Linker List Item - unused
    GPDMA_Setup(&gpdmaConfig); // Setup channel with given parameter
}

static void Tone_GenerateSineWave(int voulme) {
    if (voulme > 100) voulme = 100;
    if (voulme < 1)   voulme = 1;
    for (int i = 0; i < TONE_SAMPLE_COUNT; i++) {
        Samples_Sine[i] = 512.0f + 512.0f * sinf((float)i * (2.0f * M_PI / TONE_SAMPLE_COUNT));
        Samples_Sine[i] = (uint32_t)((float)Samples_Sine[i] * (float)voulme / 100.0f);
    }
}

void Tone_SetVolume(int volume) {
    if (volume > 100) volume = 100;
    if (volume < 1)   volume = 1;
    for (int i = 0; i < TONE_SAMPLE_COUNT; i++) {
        Samples_DAC[i] = DAC_VALUE((int)((float)Samples_Sine[i] * (float)volume / 100.0f));
    }
}

void Tone_Init(int masterVolume) {
    AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_26, PINSEL_FUNC_2); //	P0.26 Pin AF Configuration (DAC)
    Tone_DmaInit();
    Tone_GenerateSineWave(masterVolume);
    Tone_SetVolume(100);
    DAC_Init(LPC_DAC);
    GPDMA_ChannelCmd(0, ENABLE);
}

void Tone_Play(int frequency) {
    uint32_t clockPerSample = (float)(SystemCoreClock / 4) / (float)frequency / TONE_SAMPLE_COUNT;

    Tone_Stop();
    if (frequency <= NOTE_E4)
        Tone_SetVolume(100);
    else if (frequency <= NOTE_A4)
        Tone_SetVolume(50);
    else
        Tone_SetVolume(30);

    DAC_CONVERTER_CFG_Type DAC_Config;
    DAC_Config.CNT_ENA = SET; // Auto Reload
    DAC_Config.DMA_ENA = SET; // Use DMA in DAC
    DAC_SetDMATimeOut(LPC_DAC, clockPerSample - 1);
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_Config);
    Tone_State = 1;
}

void Tone_Stop(void) {
    if (Tone_State) {
        DAC_CONVERTER_CFG_Type DAC_Config;
        DAC_Config.CNT_ENA = RESET;
        DAC_Config.DMA_ENA = RESET;
        DAC_ConfigDAConverterControl(LPC_DAC, &DAC_Config);
    }
    Tone_State = 0;
}

int Tone_IsPlaying(void) {
    return Tone_State;
}

#pragma O0
void Tone_Delay(volatile uint32_t millis) {
    millis = SystemCoreClock / 4000 * millis;
    while(millis--);
}
