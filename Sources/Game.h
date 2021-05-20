#ifndef __Game_H__
#define __Game_H__

#include "Note.h"
#include "Keypad.h"
#include "Utility.h"

#define CHAR_LEFT  (0x80 + 9)
#define CHAR_RIGHT (0x80 + 11)
#define CHAR_UP    (0x80 + 5)
#define CHAR_DOWN  (0x80 + 7)
#define CHAR_MID   (0x80 + 1)

int Game_NoteToCharIndex(uint16_t note);
int Game_NoteToKeypad(uint16_t note);

#endif
