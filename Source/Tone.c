#include <math.h>
#ifndef M_PI
#define M_PI 3.141592f
#endif

#include "Tone.h"

#define TONE_SAMPLE_COUNT 512

uint8_t                Tone_Volume = 50;   // 0~100
bool                   Tone_State  = false; // play state
uint32_t               dacSamples[TONE_SAMPLE_COUNT]; // 2 KB
GPDMA_LLI_Type         dmaLinkListItem;
GPDMA_Channel_CFG_Type gpdmaConfig;

static void Tone_DmaInit(void) {
    // Prepare DMA Link-List-Item structure
    dmaLinkListItem.SrcAddr = (uint32_t)dacSamples;
    dmaLinkListItem.DstAddr = (uint32_t)&(LPC_DAC->DACR);
    dmaLinkListItem.NextLLI = (uint32_t)&dmaLinkListItem;
    dmaLinkListItem.Control = TONE_SAMPLE_COUNT // [11:00] Transfer Size (manual p.577)
                            | (2 << 18)        // [20:18] Source Transfer Width (2=32bit)
                            | (2 << 21)        // [23:21] Destination Transfer Width (2=32bit)
                            | (1 << 26);       // [26]    Source Increment (1=true)

    GPDMA_Init();
    gpdmaConfig.ChannelNum    = 0;                          // Channel 0
    gpdmaConfig.SrcMemAddr    = (uint32_t)(dacSamples);     // Source memory
    gpdmaConfig.DstMemAddr    = 0; // (unused)
    gpdmaConfig.TransferSize  = TONE_SAMPLE_COUNT;          // Transfer size
    gpdmaConfig.TransferWidth = 0; // (unused)
    gpdmaConfig.TransferType  = GPDMA_TRANSFERTYPE_M2P;     // Transfer type
    gpdmaConfig.SrcConn       = 0; // (unused)
    gpdmaConfig.DstConn       = GPDMA_CONN_DAC;             // Destination connection
    gpdmaConfig.DMALLI        = (uint32_t)&dmaLinkListItem; // Linker List Item - unused
    GPDMA_Setup(&gpdmaConfig); // Setup channel with given parameter
}

static void Tone_GenerateSineWave(float volume) {
    uint32_t i;
    float baseLevel = 512.0f * (float)volume / 100.0f;
    for (i = 0; i < TONE_SAMPLE_COUNT; i++) {
        dacSamples[i] = baseLevel + baseLevel * sinf((float)i * (2.0f * M_PI / TONE_SAMPLE_COUNT));
        dacSamples[i] = DAC_VALUE(dacSamples[i]);
    }
}

void Tone_Init(uint8_t volume) {
    AF_ConfigPin(GPIO_PORT_0, PINSEL_PIN_26, PINSEL_FUNC_2); //	P0.26 Pin AF Configuration (DAC)
    DAC_Init(LPC_DAC);
    Tone_Volume = volume;

    // Tone_GenerateSineWave();
    Tone_DmaInit();
	GPDMA_ChannelCmd(0, ENABLE);
}

void Tone_Play(uint32_t frequency) {
    uint32_t clockPerSample = (float)(SystemCoreClock / 4) / (float)frequency / TONE_SAMPLE_COUNT;

    DAC_CONVERTER_CFG_Type dacConfig;
    dacConfig.CNT_ENA = SET; //	Auto Reload
    dacConfig.DMA_ENA = SET; // Use DMA in DAC

    float r = 0.2f;
    if (frequency <= NOTE_E4)
        r = 1.0f;
    else if (frequency <= NOTE_A4)
        r = 0.5f;
    Tone_GenerateSineWave((float)Tone_Volume * r);
    Tone_Stop();
    DAC_SetDMATimeOut(LPC_DAC, clockPerSample - 1);
    DAC_ConfigDAConverterControl(LPC_DAC, &dacConfig);

    
    Tone_State = TRUE;
}

void Tone_Stop(void) {
    if (Tone_State) {
            DAC_CONVERTER_CFG_Type dacConfig;
    dacConfig.CNT_ENA = RESET; //	Auto Reload
    dacConfig.DMA_ENA = RESET; // Use DMA in DAC
			DAC_ConfigDAConverterControl(LPC_DAC, &dacConfig);
    }
    Tone_State = false;
}

bool Tone_IsPlaying(void) {
    return Tone_State;
}

void Tone_Test(uint32_t millis) {
    Tone_Play(NOTE_C4); DelayMs(millis); // 도
    Tone_Play(NOTE_D4); DelayMs(millis); // 레
    Tone_Play(NOTE_E4); DelayMs(millis); // 미
    Tone_Play(NOTE_F4); DelayMs(millis); // 파
    Tone_Play(NOTE_G4); DelayMs(millis); // 솔
    Tone_Play(NOTE_A4); DelayMs(millis); // 라
    Tone_Play(NOTE_B4); DelayMs(millis); // 시
    Tone_Play(NOTE_C5); DelayMs(millis); // 도
    Tone_Stop();
}
