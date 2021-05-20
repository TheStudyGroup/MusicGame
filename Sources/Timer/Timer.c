#include "Timer.h"

void Timer0_Init(void) {
    TIM_TIMERCFG_Type config;
    TIM_MATCHCFG_Type matchConfig;

    config.PrescaleOption          = TIM_PRESCALE_USVAL; // us(microsecond) 기준으로 Prescale 설정
    config.PrescaleValue           = 100; // 100us
    matchConfig.MatchChannel       = 0;   // 0번 채널
    matchConfig.IntOnMatch         = ENABLE;  // Timer가 일치할 때 Interrupt 발생 Enable
    matchConfig.ResetOnMatch       = ENABLE;  // Timer가 일치할 때 Reset Enable
    matchConfig.StopOnMatch        = DISABLE; // Timer가 일치할 때 Timer Stop Disable
    matchConfig.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; // Timer 일치할 때 아무런 외부 출력 하지 않음
    matchConfig.MatchValue         = 10000; // Timer 일치 값 설정 100us * 10000번 = 1초

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &config);
    TIM_ConfigMatch(LPC_TIM0, &matchConfig);
    NVIC_EnableIRQ(TIMER0_IRQn); // TIMER0 Interrupt 활성화
}

void Timer0_Start(void) {
    TIM_Cmd(LPC_TIM0, ENABLE);
}

void Timer0_Stop(void) {
    TIM_Cmd(LPC_TIM0, DISABLE);
}
