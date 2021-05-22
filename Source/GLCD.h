#ifndef __GLCD_H__
#define __GLCD_H__

#include <stdio.h>
#include <stdarg.h>

#include "Utility.h"
#include "../Resource/Resource.h"

#define Black           0x0000  /*   0,   0,   0 */
#define Navy            0x000F  /*   0,   0, 128 */
#define DarkGreen       0x03E0  /*   0, 128,   0 */
#define DarkCyan        0x03EF  /*   0, 128, 128 */
#define Maroon          0x7800  /* 128,   0,   0 */
#define Purple          0x780F  /* 128,   0, 128 */
#define Olive           0x7BE0  /* 128, 128,   0 */
#define LightGrey       0xC618  /* 192, 192, 192 */
#define DarkGrey        0x7BEF  /* 128, 128, 128 */
#define Red             0x001F  /*   0,   0, 255 */
#define Green           0x07E0  /*   0, 255,   0 */
#define Cyan            0x07FF  /*   0, 255, 255 */
#define Blue            0xF800  /* 255,   0,   0 */
#define Magenta         0xF81F  /* 255,   0, 255 */
#define Yellow          0xFFE0  /* 255, 255, 0   */
#define White           0xFFFF  /* 255, 255, 255 */

#define Line0                0
#define Line1               24
#define Line2               48
#define Line3               72
#define Line4               96
#define Line5              120
#define Line6              144
#define Line7              168
#define Line8              192
#define Line9              216

void GLCD_Init           (void);
void GLCD_PutPixel       (uint16_t x, uint16_t y);
void GLCD_Clear          (uint16_t color);
void GLCD_SetTextColor   (uint16_t color);
void GLCD_SetBackColor   (uint16_t color);
void GLCD_DisplayChar    (uint16_t x, uint16_t y, uint8_t ascii);
void GLCD_DisplayStringLn(uint16_t line, char* str);
void GLCD_ClearLn        (uint16_t line);
void GLCD_PutBitmap      (uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* bitmap);
void GLCD_Printf         (uint16_t line, char* format, ...);

#endif
