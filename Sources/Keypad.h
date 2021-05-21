#ifndef __Keypad_H__
#define __Keypad_H__

#include "Utility.h"

typedef enum {
    KEYPAD_TYPE_A,
    KEYPAD_TYPE_B,
    KEYPAD_TYPE_C,
} KeypadType;

//  0     1(U)  2      3
//  4(L)  5(M)   6(R)  7
//  8     9(D)  10    11
// 12    13     14    15

#define KEYPAD_NOKEY 0
#define KEYPAD_UP    (1 << 1)
#define KEYPAD_LEFT  (1 << 4)
#define KEYPAD_MID   (1 << 5)
#define KEYPAD_RIGHT (1 << 6)
#define KEYPAD_DOWN  (1 << 9)

void Keypad_Init(KeypadType type);
int Keypad_Scan(void);       // 16bit full result

#endif
