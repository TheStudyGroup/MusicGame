#include "Timer.h"

uint8_t Led_Status = 0;

TIM_TIMERCFG_Type __Timer_Config;
TIM_MATCHCFG_Type __Timer_MatchConfig;


void Timer0_Init(void) {
    Led_Init(LED_ALL);

    __Timer0_Config();
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &__Timer_Config);
    TIM_ConfigMatch(LPC_TIM0, &__Timer_MatchConfig);
    NVIC_EnableIRQ(TIMER0_IRQn); // TIMER0 Interrupt 활성화
}

void Timer0_Start(void) {
    TIM_Cmd(LPC_TIM0, ENABLE);
}

void Timer0_Stop(void) {
    TIM_Cmd(LPC_TIM0, DISABLE);
}

void __Timer0_Config(void) {
    __Timer_Config.PrescaleOption = TIM_PRESCALE_USVAL; // us(microsecond) 기준으로 Prescale 설정
    __Timer_Config.PrescaleValue = 100; // 100us
    __Timer_MatchConfig.MatchChannel = 0; // 0번 채널 사용
    __Timer_MatchConfig.IntOnMatch = ENABLE; // Timer가 일치할 때  Interrupt 발생 Enable
    __Timer_MatchConfig.ResetOnMatch = ENABLE; // Timer가 일치할 때  Reset Enable
    __Timer_MatchConfig.StopOnMatch = DISABLE; // Timer가 일치할 때 Timer Stop Disable
    __Timer_MatchConfig.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; // Timer 일치할때 아무런 외부 출력 하지 않음 (외부로 출력하지 않기 때문에 GPIO를 설정하지 않아도 됨.)
    __Timer_MatchConfig.MatchValue = 10000; // Timer 일치 값 설정 100us * 10000번 = 1초
}



void TIMER0_IRQHandler(void) {
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT); //TIM0 interrupt clear
    
    Led_All_Off();
    Led_On(Led_Status+1); // 1-based
    Led_Status = (Led_Status + 1) % 8;
}
