#include "Resource.h"
#include "../Source/Keypad.h"

uint16_t* Res_GetNoteImage(uint16_t note) {
    if (note == NOTE_C4) return (uint16_t*)Image_ArrowLeftYellow;
    if (note == NOTE_D4) return (uint16_t*)Image_ArrowUpGreen;
    if (note == NOTE_E4) return (uint16_t*)Image_ArrowRightRed;
    if (note == NOTE_F4) return (uint16_t*)Image_ArrowDownBlue;
    if (note == NOTE_G4) return (uint16_t*)Image_ArrowLeftYellow;
    if (note == NOTE_A4) return (uint16_t*)Image_ArrowUpGreen;
    if (note == NOTE_B4) return (uint16_t*)Image_ArrowRightRed;
    if (note == NOTE_C5) return (uint16_t*)Image_ArrowDownBlue;
    return (uint16_t*)Image_ArrowDownBlue; // TODO
}

uint16_t* Res_GetPlayerImage(void) {
    return (uint16_t*)Image_PlayerWhite;
}

int Res_NoteToKeypad(uint16_t note) {
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
