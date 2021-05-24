#include "GLCD.h"
#include "Tone.h"
#include "Timer.h"
#include "Keypad.h"
#include "Utility.h"

#include "Game.h"

uint8_t led = 0;


// ≥™∫Òæﬂ 
// º÷πÃπÃπÃ  ∆ƒ∑π∑π µµ∑ππÃ∆ƒ º÷º÷º÷ 
// º÷πÃπÃπÃ ∆ƒ∑π∑π µµπÃº÷º÷ πÃπÃπÃ
// ∑π∑π∑π∑π ∑ππÃ∆ƒ  πÃπÃπÃπÃ πÃ∆ƒº÷ 
// º÷πÃπÃπÃ ∆ƒ∑π∑π µµπÃº÷º÷ πÃπÃπÃ 
// c d e f g a b
#define LS_NOTE_PER_VERSE 14        // ¿˝ «œ≥™¥Á 14∞≥ 
#define LS_VERSE_COUNT     4         // √— 4¿˝ 
uint16_t LS_NOTE[(LS_NOTE_PER_VERSE+1) * LS_VERSE_COUNT] = {
    0, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
    0, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4,
	0, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
    0, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4,
};
int LS_XPOS[(LS_NOTE_PER_VERSE+1) * LS_VERSE_COUNT] = { // X√‡ 
    /* player */ 20,  /* 1st verse */   70, 120, 170, 220, 270, 270, 270, 220, 170, 120,  70,  20,  20,  70,
    /* player */ 70,  /* 2nd verse */  120, 170, 220, 270, 270, 270, 270, 220, 170, 170, 120,  70,  20,  20,
    /* player */ 20,  /* 3rd verse */   20,  70, 120, 120, 120, 120, 170, 220, 270, 270, 270, 220, 220, 170,
    /* player */ 170,  /* 3rd verse */ 120,  70,  20,  20,  20,  20,  70, 120, 170, 170, 220, 270, 270, 270,
};
int LS_YPOS[(LS_NOTE_PER_VERSE+1) * LS_VERSE_COUNT] = { // y√‡
    /* player */  45,  /* 1st verse */  45,  45,  45, 45, 45, 85, 125, 125, 125, 125, 125, 165, 165,
    /* player */ 165,  /* 2nd verse */ 165, 165, 165, 165, 125, 85, 45, 45, 45, 85,  85,  85,  85, 125,
    /* player */ 125,  /* 3rd verse */ 165, 165, 165, 125,  85, 45, 45, 45, 45, 85, 125, 125, 165, 165,
    /* player */ 165,  /* 3rd verse */ 165, 165, 165, 125,  85, 45, 45, 45, 45, 85,  85,  85, 125, 165,
};
// Î∞ïÏûêÌëúÎäî TODO...


int gameLevel, gameScore;
void startGame(uint16_t* note, int* xpos, int* ypos, int notePerVerse, int verseCount);
void Keypad_Test(void);


int main(void) {
    SystemInit();
    LED_Init();
    Keypad_Init(KEYPAD_TYPE_C);
    Tone_Init(50); // volume
    GLCD_Init();
    Timer0_Init(100); // timer 100ms
    Timer0_Start();

    GLCD_Clear(Black);
    GLCD_SetBackColor(Black);
    GLCD_SetTextColor(White);
    GLCD_DisplayStringLn(Line3, " < MicroProcessor > ");
    GLCD_DisplayStringLn(Line4, "    Music TokTok    ");
    GLCD_DisplayStringLn(Line5, "    - by Team 2 -   ");
    // Keypad_Test();
    // Tone_Test(100);
    DelayMs(500);


    startGame((uint16_t*)LS_NOTE, (int*)LS_XPOS, (int*)LS_YPOS, LS_NOTE_PER_VERSE, LS_VERSE_COUNT);
    while(1);
}

void startGame(uint16_t* note, int* xpos, int* ypos, int notePerVerse, int verseCount) {
    int i, j, currVerse = 0, keyState, playerX, playerY;
    gameLevel = 1;
    gameScore = 100;

    while (currVerse != verseCount) {
        GLCD_Clear(Black);

        // Draw player
        j = currVerse * (notePerVerse + 1);
        playerX = xpos[j];
        playerY = ypos[j];
        GLCD_DrawBitmap(playerX, playerY, IMAGE_HEIGHT, IMAGE_WIDTH, Game_GetPlayerImage());

        for (i = 1; i <= notePerVerse; i++) { // Draw notes
            j = currVerse * (notePerVerse + 1) + i;
            GLCD_DrawBitmap(xpos[j], ypos[j], IMAGE_HEIGHT, IMAGE_WIDTH, Game_GetNoteImage(note[j]));
        }

        for (i = 1; i <= notePerVerse; i++) {
            GLCD_Printf(Line0, "LEVEL:%d / SCORE:%-4d", gameLevel, gameScore);
            GLCD_DisplayStringLn(Line9, "TIME:|||||||| ");

            j = currVerse * (notePerVerse + 1) + i;
            keyState = KEYPAD_NOKEY;
            while (keyState == KEYPAD_NOKEY) {
                keyState = Keypad_Scan();
            }
            while (Keypad_Scan() != KEYPAD_NOKEY);

            GLCD_ClearRect(playerX, playerY, IMAGE_HEIGHT, IMAGE_WIDTH, Black);
            playerX = xpos[j];
            playerY = ypos[j];
            GLCD_DrawBitmap(playerX, playerY, IMAGE_HEIGHT, IMAGE_WIDTH, Game_GetPlayerImage());
                
            if (keyState == Game_NoteToKeypad(note[j])) { // OK
                gameScore += 10;
                Tone_Play(note[j]);
                DelayMs(200);
            } else { // FAIL
                gameScore -= 50;
                Tone_Play(NOTE_D6);
                DelayMs(50);
            }
            Tone_Stop();
        }
        currVerse ++;
    }
}

// ÌÉÄÏù¥Î®∏Îäî 0.1Ï¥àÍ∞ÑÍ≤© -> ÏúÑÏ™ΩÏóê ÎÇ®ÏùÄÏãúÍ∞Ñ ÌëúÏãú TODO
void TIMER0_IRQHandler(void) { // 100ms
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

    //LED_OffAll();
    LED_On(led + 1); // 1-based
    led = (led + 1) % 8;
}

void Keypad_Test(void) {
    int keyState;
    char buf[20];
    while (1) {
        keyState = Keypad_Scan();
        sprintf(buf, "%6d", keyState);
        GLCD_DisplayStringLn(Line8, buf);
    }
}
