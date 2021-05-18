#ifndef _Timer_H_
#define _Timer_H_

#include "LPC1768_utility.h"
#include "lpc17xx_timer.h"

void Timer0_Init(void);
void Timer0_Start(void);
void Timer0_Stop(void);

void __Timer0_Config(void);
void TIMER0_IRQHandler(void);

#endif
