#ifndef __Resource_H__
#define __Resource_H__

#include <stdint.h>

#include "Note.h"

extern const uint16_t ASCII_Table[];

#define IMAGE_WIDTH  24
#define IMAGE_HEIGHT 24

extern const uint16_t Image_ArrowLeftYellow [IMAGE_HEIGHT][IMAGE_WIDTH];
extern const uint16_t Image_ArrowRightRed   [IMAGE_HEIGHT][IMAGE_WIDTH];
extern const uint16_t Image_ArrowUpGreen    [IMAGE_HEIGHT][IMAGE_WIDTH];
extern const uint16_t Image_ArrowDownBlue   [IMAGE_HEIGHT][IMAGE_WIDTH];
extern const uint16_t Image_PlayerWhite     [IMAGE_HEIGHT][IMAGE_WIDTH];

typedef struct {
    char      name[20];
    int       time;
    int       notePerVerse;
    int       verseCount;
    uint16_t* notes;
    int*      xpos;
    int*      ypos;
} GameLevel;

extern const GameLevel gameLevels[];


uint16_t* Res_GetNoteImage  (uint16_t note);
uint16_t* Res_GetPlayerImage(void);
int       Res_NoteToKeypad  (uint16_t note);

#endif
