#ifndef _Tone_h_
#define _Tone_h_

#include "LPC1768_utility.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"

#include "Note.h"

void Tone_Init(void);
void Tone_PlaySineWave(uint32_t frequency);
void Tone_Stop(void);
Bool Tone_IsPlaying(void);

void __Tone_GenerateSineWave(void);
void __Tone_DmaInit(void);

#endif
