#include "GLCD.h"

#define DELAY_2N    18

#define GLCD_WIDTH  320
#define GLCD_HEIGHT 240
#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

#define SSP_DATA    (0x100)             /* RS bit 1 within start byte         */
#define SSP_INDEX   (0x00)              /* RS bit 0 within start byte         */


static volatile unsigned short TextColor = Black, BackColor = White;


static void delay(int cnt) {
    cnt <<= DELAY_2N;
    while (cnt--);
}


static __inline uint8_t SSP_Send(uint16_t byte) {
    LPC_SSP1->DR = byte & 0x1FF;
    while (LPC_SSP1->SR & (1 << 4)); // Wait for transfer to finish
    return (LPC_SSP1->DR) & 0xFF;    // Return received value
}
static __inline void GLCD_WriteCmd(uint8_t command) {
    LPC_GPIO0->FIOPIN &= ~(1 << 6);
    SSP_Send(command | SSP_INDEX);
    LPC_GPIO0->FIOPIN |=  (1 << 6);
}
static __inline void GLCD_WriteData(uint16_t data) {
    LPC_GPIO0->FIOPIN &= ~(1 << 6);
    SSP_Send(data | SSP_DATA); // Write : RS = 1, RW = 0
    LPC_GPIO0->FIOPIN |=  (1 << 6);
}
static __inline void GLCD_WritePixel(uint16_t pixel) {
    LPC_GPIO0->FIOPIN &= ~(1 << 6);
    SSP_Send((pixel >> 8)   | SSP_DATA); // Write D8..D15
    SSP_Send((pixel & 0xFF) | SSP_DATA); // Write D0..D7
    LPC_GPIO0->FIOPIN |=  (1 << 6);
}
// static __inline void GLCD_WriteReg(uint8_t command, uint16_t data) {
//     GLCD_WriteCmd(command);
//     GLCD_WriteData(data);
// }



void GLCD_Init(void) {
    /* Configure the LCD Control pins ------------------------------------------*/
    LPC_PINCON->PINSEL9 &= ~(3 << 24);    /* Pin P4.28 used for backlight       */
    LPC_GPIO4->FIODIR   |=  (1 << 28);    /* Pin P2.28 is output                */
    LPC_PINCON->PINSEL9 &= ~(3 << 26);    /* Pin P4.29 used for LCD CS          */
    LPC_GPIO4->FIODIR   |=  (1 << 29);    /* Pin P2.29 is output                */
    LPC_GPIO4->FIOPIN   |=  (1 << 29);    /* Pin P2.29 is high                  */

    /*-- SSP Configuration -----------------------------------------------------*/
    LPC_SC->PCONP       |=  (1 << 10);    /* Enable power to SSP1 block         */
    LPC_SC->PCLKSEL0    |=  (2 << 20);    /* SSP1 clock = CCLK / 2              */
    LPC_GPIO0->FIODIR   |=  (1 <<  6);    /* Pin P0.6 is GPIO output (SSEL1)    */
    LPC_GPIO0->FIOSET    =  (1 <<  6);    /* Set P0.6 high                      */
    LPC_PINCON->PINSEL0 &= ~0x000FC000;
    LPC_PINCON->PINSEL0 |=  0x000A8000;   /* Select SSP mode for SSP pins       */

    LPC_SSP1->CR0        =  (   0 << 7) | /* CPHA = 0                           */
                            (   0 << 6) | /* CPOL = 0                           */
                            (   0 << 4) | /* Frame format = SPI                 */
                            ((9-1)<< 0) ; /* Data size = 9 bits                 */
    LPC_SSP1->CPSR       =  6;            /* Clock Rate = 6.25MHz               */
    LPC_SSP1->CR1        =  (   1 << 1);  /* Enable SSP1                        */

    delay(5);                             /* Delay 50 ms                        */

    //************* Start Initial Sequence **********//
    GLCD_WriteCmd(0xCF); // Power Control B
    GLCD_WriteData(0x00);
    GLCD_WriteData(0x83);
    GLCD_WriteData(0X30);

    GLCD_WriteCmd(0xED); // Power on sequence control
    GLCD_WriteData(0x64);
    GLCD_WriteData(0x03);
    GLCD_WriteData(0X12);
    GLCD_WriteData(0X81);

    GLCD_WriteCmd(0xE8); // Driver timing control A
    GLCD_WriteData(0x85);
    GLCD_WriteData(0x01);
    GLCD_WriteData(0x79);

    GLCD_WriteCmd(0xCB); // Power Control A
    GLCD_WriteData(0x39);
    GLCD_WriteData(0x2C);
    GLCD_WriteData(0x00);
    GLCD_WriteData(0x34);
    GLCD_WriteData(0x02);

    GLCD_WriteCmd(0xF7); // Pump ratio control
    GLCD_WriteData(0x20);

    GLCD_WriteCmd(0xEA); // Driver timing control B
    GLCD_WriteData(0x00);
    GLCD_WriteData(0x00);

    GLCD_WriteCmd(0xC0); //Power control
    GLCD_WriteData(0x1D); //VRH[5:0]

    GLCD_WriteCmd(0xC1); //Power control
    GLCD_WriteData(0x11); //SAP[2:0];BT[3:0]

    GLCD_WriteCmd(0xC5); //VCM control
    GLCD_WriteData(0x33);
    GLCD_WriteData(0x34);

    GLCD_WriteCmd(0xC7); //VCM control2
    GLCD_WriteData(0Xbe);

    GLCD_WriteCmd(0xF6); // Memory Access Control
    GLCD_WriteData(0x01);
    GLCD_WriteData(0x10);// RGB16bit -> RGB18bit
    GLCD_WriteData(0x00);

    GLCD_WriteCmd(0x3A); // COLMOD: Pixel Format Set
    GLCD_WriteData(0x55); // 16bits/pixel

    GLCD_WriteCmd(0x36); // Memory Access Control
    GLCD_WriteData((1<<7)|(0<<6)|(1<<5)|(1<<4)|(0<<3)|(0<<2)); // MY, MX, MV, ML, BGR, MH

    GLCD_WriteCmd(0xB1); // Frame Rate Control
    GLCD_WriteData(0x00);
    GLCD_WriteData(0x1B);

    GLCD_WriteCmd(0xB6); // Display Function Control
    GLCD_WriteData(0x0A);
    GLCD_WriteData(0xA2);

    GLCD_WriteCmd(0xF2); // 3Gamma Function Disable
    GLCD_WriteData(0x00);

    GLCD_WriteCmd(0x26); //Gamma curve selected
    GLCD_WriteData(0x01);

    GLCD_WriteCmd(0xE0); //Set Gamma
    GLCD_WriteData(0x0F);
    GLCD_WriteData(0x23);
    GLCD_WriteData(0x1F);
    GLCD_WriteData(0x09);
    GLCD_WriteData(0x0f);
    GLCD_WriteData(0x08);
    GLCD_WriteData(0x4B);
    GLCD_WriteData(0Xf2);
    GLCD_WriteData(0x38);
    GLCD_WriteData(0x09);
    GLCD_WriteData(0x13);
    GLCD_WriteData(0x03);
    GLCD_WriteData(0x12);
    GLCD_WriteData(0x07);
    GLCD_WriteData(0x04);

    GLCD_WriteCmd(0XE1); //Set Gamma
    GLCD_WriteData(0x00);
    GLCD_WriteData(0x1d);
    GLCD_WriteData(0x20);
    GLCD_WriteData(0x02);
    GLCD_WriteData(0x11);
    GLCD_WriteData(0x07);
    GLCD_WriteData(0x34);
    GLCD_WriteData(0x81);
    GLCD_WriteData(0x46);
    GLCD_WriteData(0x06);
    GLCD_WriteData(0x0e);
    GLCD_WriteData(0x0c);
    GLCD_WriteData(0x32);
    GLCD_WriteData(0x38);
    GLCD_WriteData(0x0F);

    GLCD_WriteCmd(0x11); //Exit Sleep

    delay(12);

    GLCD_WriteCmd(0x29); //Display on

    LPC_GPIO4->FIOPIN |=  (1 << 28);    /* Turn backlight on */
}


static void GLCD_SetX(uint16_t x, uint16_t width) {
    GLCD_WriteCmd(0x2A);
    GLCD_WriteData((x>>8) & 0xFF);
    GLCD_WriteData(x & 0xFF);
    GLCD_WriteData(((x+width-1)>>8) & 0xFF);
    GLCD_WriteData((x+width-1) & 0xFF);
}
static void GLCD_SetY(uint16_t y, uint16_t height) {
    GLCD_WriteCmd(0x2B);
    GLCD_WriteData((y>>8) & 0xFF);
    GLCD_WriteData(y & 0xFF);
    GLCD_WriteData(((y+height-1)>>8) & 0xFF);
    GLCD_WriteData((y+height-1) & 0xFF);
}


void GLCD_PutPixel(uint16_t x, uint16_t y) {
    GLCD_SetX(x, 1);
    GLCD_SetY(y, 1);
    GLCD_WriteCmd(0x2C);
    GLCD_WritePixel(TextColor);
}
void GLCD_Clear(uint16_t color) {
    uint16_t i;
    GLCD_SetX(0, GLCD_WIDTH);
    GLCD_SetY(0, GLCD_HEIGHT);
    GLCD_WriteCmd(0x2C); // RAM Write
    for(i = 0; i < GLCD_WIDTH * GLCD_HEIGHT; i++) {
        GLCD_WritePixel(color);
    }
}


void GLCD_SetTextColor(uint16_t color) {
    TextColor = color;
}
void GLCD_SetBackColor(uint16_t color) {
    BackColor = color;
}
static void GLCD_DrawChar(uint16_t x, uint16_t y, uint16_t* c) {
    uint16_t index = 0, i = 0;
    GLCD_SetX(x, 16);
    GLCD_SetY(y, 24);
    GLCD_WriteCmd(0x2C);
    for(index = 0; index < 24; index++) {
        for(i = 0; i <16; i++) {
            if((c[index] & (1 << i)) == 0x00) {
                GLCD_WritePixel(BackColor);
            } else {
                GLCD_WritePixel(TextColor);
            }
        }
    }
}
void GLCD_DisplayChar(uint16_t x, uint16_t y, uint8_t ascii) {
    ascii -= 32;
    GLCD_DrawChar(x, y, &ASCII_Table[ascii * 24]);
}
void GLCD_DisplayStringLn(uint16_t line, char* str) {
    uint16_t i = 0;
    uint16_t refcolumn = 0;
    while ((*str != 0) & (i < 20)) {
        GLCD_DisplayChar(refcolumn, line, *str);
        refcolumn += 16;
        str++;
        i++;
    }
}
void GLCD_ClearLn(uint16_t line) {
    GLCD_DisplayStringLn(line, "                    ");
}

void GLCD_PutBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, unsigned char *bitmap) {
    unsigned int   i;
    unsigned int   len = w*h;
    unsigned short *bitmap_ptr = (unsigned short *)bitmap;

    GLCD_SetX(x, w);
    GLCD_SetY(y, h);

    GLCD_WriteCmd(0x2C);
    for (i = 0; i < len; i++)
    {
        GLCD_WritePixel(*bitmap_ptr++);
    }
}
