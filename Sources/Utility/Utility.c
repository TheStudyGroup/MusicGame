#include "Utility.h"

void DelayMs(uint32_t millis) {
    uint32_t i;
    millis = SystemCoreClock / 4000 * millis; // SystemCoreClock/4 == 1sec
    for(i = 0; i < millis; i++); // 4 cycles
}


void LED_Init(void) {
    GPIO_SetDir(GPIO_PORT_1, GPIO_PIN_28 | GPIO_PIN_29 | GPIO_PIN_31, OUTPUT);
    GPIO_SetDir(GPIO_PORT_2, GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, OUTPUT);

    GPIO_ClearValue(GPIO_PORT_1,  GPIO_PIN_28 | GPIO_PIN_29 | GPIO_PIN_31);
    GPIO_ClearValue(GPIO_PORT_2,  GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
}

void LED_On(uint8_t index) {
    if (index == 1) {
        GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_28);
    } else if (index == 2) {
        GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_29);
    } else if (index == 3) {
        GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_31);
    } else if (index == 4) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_2);
    } else if (index == 5) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_3);
    } else if (index == 6) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_4);
    } else if (index == 7) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_5);
    } else if (index == 8) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_6);
    }
}

void LED_Off(uint8_t index) {
    if (index == 1) {
        GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_28);
    } else if (index == 2) {
        GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_29);
    } else if (index == 3) {
        GPIO_SetValue(GPIO_PORT_1, GPIO_PIN_31);
    } else if (index == 4) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_2);
    } else if (index == 5) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_3);
    } else if (index == 6) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_4);
    } else if (index == 7) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_5);
    } else if (index == 8) {
        GPIO_SetValue(GPIO_PORT_2, GPIO_PIN_6);
    }
}

void LED_OnAll(void) {
    GPIO_SetValue(GPIO_PORT_1,  GPIO_PIN_28 | GPIO_PIN_29 | GPIO_PIN_31);
    GPIO_SetValue(GPIO_PORT_2,  GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
}

void LED_OffAll(void) {
    GPIO_ClearValue(GPIO_PORT_1,  GPIO_PIN_28 | GPIO_PIN_29 | GPIO_PIN_31);
    GPIO_ClearValue(GPIO_PORT_2,  GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
}
