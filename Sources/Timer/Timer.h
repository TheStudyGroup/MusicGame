#ifndef _Timer_H_
#define _Timer_H_

#include "../Utility/Utility.h"

void DelayMs(uint32_t millis);

void Timer0_Init(void);
void Timer0_Start(void);
void Timer0_Stop(void);

#endif
