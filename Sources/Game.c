#include "Game.h"

int Game_NoteToCharIndex(uint16_t note) {
    if (note == NOTE_C4) return CHAR_LEFT;
    if (note == NOTE_D4) return CHAR_UP;
    if (note == NOTE_E4) return CHAR_RIGHT;
    if (note == NOTE_F4) return CHAR_DOWN;
    if (note == NOTE_G4) return CHAR_LEFT;
    if (note == NOTE_A4) return CHAR_UP;
    if (note == NOTE_B4) return CHAR_RIGHT;
    if (note == NOTE_C5) return CHAR_DOWN;
    return CHAR_MID;
}

int Game_NoteToKeypad(uint16_t note) {
    if (note == NOTE_C4) return KEYPAD_LEFT;
    if (note == NOTE_D4) return KEYPAD_UP;
    if (note == NOTE_E4) return KEYPAD_RIGHT;
    if (note == NOTE_F4) return KEYPAD_DOWN;
    if (note == NOTE_G4) return KEYPAD_LEFT;
    if (note == NOTE_A4) return KEYPAD_UP;
    if (note == NOTE_B4) return KEYPAD_RIGHT;
    if (note == NOTE_C5) return KEYPAD_DOWN;
    return KEYPAD_MID;
}
