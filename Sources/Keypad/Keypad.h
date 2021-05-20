#ifndef __Keypad_H__
#define __Keypad_H__

#include "../Utility/Utility.h"

#define KEYPAD_TYPE_A 1
#define KEYPAD_TYPE_B 2
#define KEYPAD_TYPE_C 3

//  0     1(U)  2      3
//  4(L)  5(M)   6(R)  7
//  8     9(D)  10    11
// 12    13     14    15

#define KEYPAD_UP    (1 << 1)
#define KEYPAD_LEFT  (1 << 4)
#define KEYPAD_MID   (1 << 5)
#define KEYPAD_RIGHT (1 << 6)
#define KEYPAD_DOWN  (1 << 9)

void Keypad_Init(uint32_t keypadType);
uint32_t Keypad_ScanColumn(void); // 4bit column result
uint32_t Keypad_Scan(void);       // 16bit full result

#endif
