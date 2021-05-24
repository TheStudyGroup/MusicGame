#ifndef _Tone_h_
#define _Tone_h_

#include "Utility.h"
#include "../Resource/Note.h"

void Tone_Init     (int masterVolume);
void Tone_SetVolume(int volume);
void Tone_Play     (int frequency);
void Tone_Stop     (void);
int  Tone_IsPlaying(void);
void Tone_Delay    (volatile uint32_t millis);

#endif
