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


#endif
