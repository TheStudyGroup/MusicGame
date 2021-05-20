#ifndef _Utility_H_
#define _Utility_H_

#include "LPC17xx.h"
#include "lpc_types.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_gpdma.h"
#include "lpc17xx_uart.h"

#define OUTPUT 1
#define INPUT  0

#define GPIO_PORT_0 0 // Port P0 
#define GPIO_PORT_1 1 // Port P1 
#define GPIO_PORT_2 2 // Port P2
#define GPIO_PORT_3 3 // Port P3
#define GPIO_PORT_4 4 // Port P4  

#define GPIO_PIN_0  0x00000001 // == (1)
#define GPIO_PIN_1  0x00000002 // == (1 << 1)
#define GPIO_PIN_2  0x00000004 // == (1 << 2)
#define GPIO_PIN_3  0x00000008 // == (1 << 3)

#define GPIO_PIN_4  0x00000010 // == (1 << 4)
#define GPIO_PIN_5  0x00000020 // == (1 << 5)
#define GPIO_PIN_6  0x00000040 // == (1 << 6)
#define GPIO_PIN_7  0x00000080 // == (1 << 7)

#define GPIO_PIN_8  0x00000100 // == (1 << 8)
#define GPIO_PIN_9  0x00000200 // == (1 << 9)
#define GPIO_PIN_10 0x00000400 // == (1 << 10
#define GPIO_PIN_11 0x00000800 // == (1 << 11)

#define GPIO_PIN_12 0x00001000 // == (1 << 12)
#define GPIO_PIN_13 0x00002000 // == (1 << 13)
#define GPIO_PIN_14 0x00004000 // == (1 << 14)
#define GPIO_PIN_15 0x00008000 // == (1 << 15)

#define GPIO_PIN_16 0x00010000 // == (1 << 16)
#define GPIO_PIN_17 0x00020000 // == (1 << 17)
#define GPIO_PIN_18 0x00040000 // == (1 << 18)
#define GPIO_PIN_19 0x00080000 // == (1 << 19)

#define GPIO_PIN_20 0x00100000 // == (1 << 20)
#define GPIO_PIN_21 0x00200000 // == (1 << 21)
#define GPIO_PIN_22 0x00400000 // == (1 << 22)
#define GPIO_PIN_23 0x00800000 // == (1 << 23)

#define GPIO_PIN_24 0x01000000 // == (1 << 24)
#define GPIO_PIN_25 0x02000000 // == (1 << 25)
#define GPIO_PIN_26 0x04000000 // == (1 << 26)
#define GPIO_PIN_27 0x08000000 // == (1 << 27)

#define GPIO_PIN_28 0x10000000 // == (1 << 28)
#define GPIO_PIN_29 0x20000000 // == (1 << 29)
#define GPIO_PIN_30 0x40000000 // == (1 << 30)
#define GPIO_PIN_31 0x80000000 // == (1 << 31)


void DelayMs(uint32_t millis);

void LED_Init  (void);
void LED_On    (uint8_t index);
void LED_Off   (uint8_t index);
void LED_OnAll (void);
void LED_OffAll(void);
void LED_Toggle(uint8_t Led);

#endif
