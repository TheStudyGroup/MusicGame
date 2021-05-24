#ifndef __Game_H__
#define __Game_H__

#include "GLCD.h"
#include "Tone.h"
#include "Timer.h"
#include "Keypad.h"
#include "Utility.h"
#include "../Resource/Resource.h"


uint16_t* Game_GetNoteImage  (uint16_t note);
uint16_t* Game_GetPlayerImage(void);

int       Game_NoteToKeypad  (uint16_t note);

#endif
