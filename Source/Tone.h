#ifndef _Tone_h_
#define _Tone_h_

#include "Utility.h"
#include "../Resource/Note.h"

void Tone_Init     (uint8_t  volume);
void Tone_Play     (uint32_t frequency);
void Tone_Stop     (void);
bool Tone_IsPlaying(void);
void Tone_Test     (uint32_t millis);

#endif
