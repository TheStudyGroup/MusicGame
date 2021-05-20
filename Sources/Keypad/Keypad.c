#include "Keypad.h"

static void EXT_IO_Init() {
    /*EXT_IO on PORT0 as Output*/
    LPC_GPIO0->FIODIR |= (1 << 4) | (1 << 19) | (1 << 20) | (1 << 21); // Mainboard Chip Select
    LPC_GPIO1->FIODIR |= (1 << 21);
    LPC_GPIO2->FIODIR |= (1 << 11);
}
static void EXT_IO_A_CS() {
    /* EXT_IO_A, DIR nOE setting B->A*/
    LPC_GPIO0->FIOPIN &= ~(1 << 19); // EXT_IO_A On
    LPC_GPIO0->FIOPIN |= (1 << 20);  // EXT_IO_B Off
    LPC_GPIO0->FIOPIN |= (1 << 21);  // EXT_IO_C Off
}
static void EXT_IO_B_CS() {
    /* EXT_IO_B, DIR nOE setting B->A*/
    LPC_GPIO0->FIOPIN |= (1 << 19);  // EXT_IO_A Off
    LPC_GPIO0->FIOPIN &= ~(1 << 20); // EXT_IO_B On
    LPC_GPIO0->FIOPIN |= (1 << 21);  // EXT_IO_C Off
}
static void EXT_IO_C_CS() {
    /* EXT_IO_C, DIR nOE setting B->A*/
    LPC_GPIO0->FIOPIN |= (1 << 19);  // EXT_IO_A Off
    LPC_GPIO0->FIOPIN |= (1 << 20);  // EXT_IO_B Off
    LPC_GPIO0->FIOPIN &= ~(1 << 21); // EXT_IO_C On
}


static void Keypad_SetDirOutput() {
    /* PORT0 defined as Output */
    LPC_GPIO0->FIODIR |= (1 << 5);
    LPC_GPIO0->FIODIR |= (1 << 10);
    /* PORT2 defined as Output */
    LPC_GPIO2->FIODIR |= (1 << 12);
    LPC_GPIO2->FIODIR |= (1 << 13);
}
// static void Keypad_SetDirInput() {
//     LPC_GPIO0->FIOPIN |= (1 << 4); // DIR A->B
//     /* PORT0 defined as Input */
//     LPC_GPIO0->FIODIR &= ~(1 << 23);
//     LPC_GPIO0->FIODIR &= ~(1 << 24);
//     /* PORT3 defined as Input */
//     LPC_GPIO3->FIODIR &= ~(1 << 25);
//     LPC_GPIO3->FIODIR &= ~(1 << 26);
// }


static void Keypad_UseRow1() {
    Keypad_SetDirOutput();
    /* PORT0 defined as Output */
    LPC_GPIO0->FIOPIN &= ~(1 << 5);
    LPC_GPIO0->FIOPIN |= (1 << 10);
    /* PORT2 defined as Output */
    LPC_GPIO2->FIOPIN |= (1 << 12);
    LPC_GPIO2->FIOPIN |= (1 << 13);
    // CS Clock High Edge
    LPC_GPIO2->FIOPIN |= (1 << 11); 
    LPC_GPIO2->FIOPIN &= ~(1 << 11);
}
static void Keypad_UseRow2() {
    Keypad_SetDirOutput();
    /* PORT0 defined as Output */
    LPC_GPIO0->FIOPIN |= (1 << 5);
    LPC_GPIO0->FIOPIN &= ~(1 << 10);
    /* PORT2 defined as Output */
    LPC_GPIO2->FIOPIN |= (1 << 12);
    LPC_GPIO2->FIOPIN |= (1 << 13);
    // CS Clock High Edge
    LPC_GPIO2->FIOPIN |= (1 << 11); 
    LPC_GPIO2->FIOPIN &= ~(1 << 11);
}
static void Keypad_UseRow3() {
    Keypad_SetDirOutput();
    /* PORT0 defined as Output */
    LPC_GPIO0->FIOPIN |= (1 << 5);
    LPC_GPIO0->FIOPIN |= (1 << 10);
    /* PORT2 defined as Output */
    LPC_GPIO2->FIOPIN &= ~(1 << 12);
    LPC_GPIO2->FIOPIN |= (1 << 13);
    // CS Clock High Edge
    LPC_GPIO2->FIOPIN |= (1 << 11); 
    LPC_GPIO2->FIOPIN &= ~(1 << 11);
}
static void Keypad_UseRow4() {
    Keypad_SetDirOutput();
    /* PORT0 defined as Output */
    LPC_GPIO0->FIOPIN |= (1 << 5);
    LPC_GPIO0->FIOPIN |= (1 << 10);
    /* PORT2 defined as Output */
    LPC_GPIO2->FIOPIN |= (1 << 12);
    LPC_GPIO2->FIOPIN &= ~(1 << 13);
    // CS Clock High Edge
    LPC_GPIO2->FIOPIN |= (1 << 11); 
    LPC_GPIO2->FIOPIN &= ~(1 << 11);
}

void Keypad_Init(uint32_t keypadType) {
    EXT_IO_Init();
    if (keypadType == KEYPAD_TYPE_A) // see arm_cortexm3_keypad_v11.pdf
        EXT_IO_A_CS();
    else if (keypadType == KEYPAD_TYPE_B)
        EXT_IO_B_CS();
    else 
        EXT_IO_C_CS();
}

uint32_t Keypad_ScanColumn() {
    uint32_t result = 0;
    LPC_GPIO1->FIOPIN &= ~(1 << 21); // Keypad Input CS On

    if ((~LPC_GPIO0->FIOPIN >> 26) & 0x01)
        result |= (1 << 0);
    if ((~LPC_GPIO0->FIOPIN >> 25) & 0x01)
        result |= (1 << 1);
    if ((~LPC_GPIO3->FIOPIN >> 24) & 0x01)
        result |= (1 << 2);
    if ((~LPC_GPIO3->FIOPIN >> 23) & 0x01)
        result |= (1 << 3);

    LPC_GPIO1->FIOPIN |= (1 << 21); // Keypad Input CS Off
    return result;
}

uint32_t Keypad_Scan() {
    uint32_t result = 0;

    Keypad_UseRow1();
    result |= Keypad_ScanColumn();
    Keypad_UseRow2();
    result |= Keypad_ScanColumn() << 4;
    Keypad_UseRow3();
    result |= Keypad_ScanColumn() << 8;
    Keypad_UseRow4();
    result |= Keypad_ScanColumn() << 12;

    return result;
}
