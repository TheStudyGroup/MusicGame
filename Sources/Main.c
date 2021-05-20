#include "GLCD.h"
#include "Tone.h"
#include "Timer.h"
#include "Keypad.h"
#include "Utility.h"

#include "Game.h"

uint8_t led = 0;


// 작은별(LittleStar=LS)
// 도도솔솔 라라 솔 파파미미 레레도
// 솔솔 파파미미레 솔솔 파파미미레
// 도도솔솔 라라 솔 파파미미 레레도

#define LS_COUNT 14        // 절 하나에 음표 14개
#define LS_VERSE 3         // 3절까지 있음 
uint16_t LS_NOTE[LS_VERSE][LS_COUNT] = {
    { NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4 },
    { NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4 },
    { NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4 },
};
int LS_XPOS[LS_VERSE][LS_COUNT] = { // 각각음표 x좌표
    { 50*1, 50*2, 50*3, 50*4, 50*5, 50*6,   50*6, 50*6,   50*6, 50*5, 50*4, 50*3, 50*2, 50*1 },
    { 50*6, 50*5, 50*4, 50*3, 50*2, 50*1,   50*1, 50*1,   50*1, 50*2, 50*3, 50*4, 50*5, 50*6 },
    { 50*1, 50*2, 50*3, 50*4, 50*5, 50*6,   50*6, 50*6,   50*6, 50*5, 50*4, 50*3, 50*2, 50*1 },
};
int LS_YPOS[LS_VERSE][LS_COUNT] = { // y좌표
    { 90, 90, 90, 90, 90, 90            ,   130, 170,     210, 210, 210, 210, 210, 210 },
    { 210, 210, 210, 210, 210, 210      ,   170, 130,     90, 90, 90, 90, 90, 90       },
    { 90, 90, 90, 90, 90, 90            ,   130, 170,     210, 210, 210, 210, 210, 210 },
};
// 박자표는 TODO...


uint32_t gameLevel, gameScore;
void startGame(uint16_t* note, int* xpos, int* ypos, int count, int verse);

int main(void) {
    SystemInit();
    LED_Init();
    Keypad_Init(KEYPAD_TYPE_C);
    Tone_Init();
    Tone_PlaySineWave(NOTE_C4); DelayMs(200); // 도
    Tone_PlaySineWave(NOTE_D4); DelayMs(200); // 레
    Tone_PlaySineWave(NOTE_E4); DelayMs(200); // 미
    Tone_PlaySineWave(NOTE_F4); DelayMs(200); // 파
    Tone_PlaySineWave(NOTE_G4); DelayMs(200); // 솔
    Tone_PlaySineWave(NOTE_A4); DelayMs(200); // 라
    Tone_PlaySineWave(NOTE_B4); DelayMs(200); // 시
    Tone_PlaySineWave(NOTE_C5); DelayMs(200); // 도
    Tone_Stop();
    DelayMs(500);
	
    GLCD_Init();
    Timer0_Init(100); // timer 100ms
    Timer0_Start();

    GLCD_Clear(Black);
    GLCD_SetBackColor(Black);
    GLCD_SetTextColor(White);
    GLCD_DisplayStringLn(Line4, " < MicroProcessor > ");
    GLCD_DisplayStringLn(Line5, "    Music TokTok    ");
    GLCD_DisplayStringLn(Line6, "    - by Team 2 -   ");
    DelayMs(500);



    // GLCD_SetBackColor(White);
	// GLCD_SetTextColor(Green);
	// GLCD_DisplayChar(320-6*16- 100*16, Line4, 0x80+1); 

    startGame((uint16_t*)LS_NOTE, (int*)LS_XPOS, (int*)LS_YPOS, LS_COUNT, LS_VERSE);
}

void startGame(uint16_t* note, int* xpos, int* ypos, int notePerVerse, int verseCount) {
    int i, noteIndex, currVerse = 0, keyState;

    gameLevel = 0;
    gameScore = 0;

    while (currVerse != verseCount) {
        GLCD_Clear(Black);
        GLCD_DisplayStringLn(Line0, "LEVEL:0 / SCORE:0000");
        GLCD_DisplayStringLn(Line9, "TIME: 100           ");
        for (i = 0; i < notePerVerse; i++) { // draw map
            noteIndex = currVerse * notePerVerse + i;
            GLCD_DisplayChar(xpos[noteIndex], ypos[noteIndex], Game_NoteToCharIndex(note[noteIndex]));
        }

        for (i = 0; i < notePerVerse; i++) {
            noteIndex = currVerse * notePerVerse + i;
            keyState  = KEYPAD_NOKEY;
            while (keyState != KEYPAD_NOKEY) {
                keyState = Keypad_Scan();
            }

            if (keyState == Game_NoteToKeypad(note[noteIndex])) { // OK
                Tone_PlaySineWave(note[noteIndex]);
                GLCD_DisplayChar(xpos[noteIndex], ypos[noteIndex], 0x80);
            } else { // FAIL
                Tone_PlaySineWave(NOTE_D6);
                GLCD_DisplayChar(xpos[noteIndex], ypos[noteIndex], 'X');         
            }
            DelayMs(800);
        }
        currVerse ++;
    }
}

void TIMER0_IRQHandler(void) { // 100ms
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
    
    LED_OffAll();
    LED_On(led+1); // 1-based
    led = (led + 1) % 8;
}
