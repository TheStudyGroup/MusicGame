#include "GLCD.h"
#include "Tone.h"
#include "Timer.h"
#include "Keypad.h"
#include "Utility.h"

#include "Game.h"

#include "stdbool.h"

uint8_t led = 0;


// 작은별(LittleStar=LS)
// 도도솔솔 라라 솔 파파미미 레레도
// 솔솔 파파미미레 솔솔 파파미미레
// 도도솔솔 라라 솔 파파미미 레레도

#define LS_NOTE_PER_VERSE 14        // 절 하나에 음표 14개
#define LS_VERSE_COUNT     3         // 3절까지 있음
uint16_t LS_NOTE[(LS_NOTE_PER_VERSE+1) * LS_VERSE_COUNT] = {
    0, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
    0, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    0, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
};
int LS_XPOS[(LS_NOTE_PER_VERSE+1) * LS_VERSE_COUNT] = { // 각각음표 x좌표
    /* player */  20,  /* 1st verse */  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,  20,  20,
    /* player */  20,  /* 2nd verse */  20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,
    /* player */  70,  /* 3rd verse */  20,  20,  20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170,
	};
	int LS_YPOS[(LS_NOTE_PER_VERSE+1) * LS_VERSE_COUNT] = { // y좌표
    /* player */  45,  /* 1st verse */  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165, 165, 125,
    /* player */ 125,  /* 2nd verse */  85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165,
    /* player */ 165,  /* 3rd verse */ 165, 125,  85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165,
};
// 박자표는 TODO...

// 사과같은 내 얼굴(apple)
// 도레 미미 파미레 레미파파 솔파미
// 미파솔솔 도라솔솔 도레미미레도

#define APPLE_NOTE_PER_VERSE 14        // 절 하나에 음표 14개
#define APPLE_VERSE_COUNT 2         // 2절까지 있음 
uint16_t APPLE_NOTE[(APPLE_NOTE_PER_VERSE+1) * APPLE_VERSE_COUNT] = {
    0, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
    0, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4
};
int APPLE_XPOS[(APPLE_NOTE_PER_VERSE+1) * APPLE_VERSE_COUNT] = { // 각각음표 x좌표
     20,       70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,  20,  20,
     20,       20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,
};
int APPLE_YPOS[(APPLE_NOTE_PER_VERSE+1) * APPLE_VERSE_COUNT] = { // y좌표
     45,       45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165, 165, 125,
     125,      85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165,
};

//학교종이 땡땡땡(BELL)
//솔솔라라 솔솔미 솔솔미미레
//솔솔라랄 솔솔미 솔미레미도
#define BELL_NOTE_PER_VERSE 12        // 절 하나에 음표 12개
#define BELL_VERSE_COUNT 2         // 2절까지 있음 
uint16_t BELL_NOTE[(BELL_NOTE_PER_VERSE+1) * BELL_VERSE_COUNT] = {
    0, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4,
    0, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4,  NOTE_C4,
};
int BELL_XPOS[(BELL_NOTE_PER_VERSE+1) * BELL_VERSE_COUNT] = { // 각각음표 x좌표
    20,     70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120, 70,
	  70,     20,  20,  20,  20,  70, 120, 170, 220, 270, 270, 270, 270,  
};
int BELL_YPOS[(BELL_NOTE_PER_VERSE+1) * BELL_VERSE_COUNT] = { // y좌표
    45,      45,  45, 45, 45, 45, 85, 125, 165, 165, 165, 165, 165,
    165,    165, 125, 85, 45, 45, 45,  45,  45,  45,  85, 125, 165, 
};



int gameLevel=1, gameScore, time;
bool succes[4] = {false};
void startGame(uint16_t* note, int* xpos, int* ypos, int notePerVerse, int verseCount);
void Keypad_Test(void);


int main(void) {
    SystemInit();
    LED_Init();
    Keypad_Init(KEYPAD_TYPE_C);
    Tone_Init(50); // volume
    GLCD_Init();
    Timer0_Init(1000);

    GLCD_Clear(Black);
    GLCD_SetBackColor(Black);
    GLCD_SetTextColor(White);
    GLCD_DisplayStringLn(Line3, " < MicroProcessor > ");
    GLCD_DisplayStringLn(Line4, "    Music TokTok    ");
    GLCD_DisplayStringLn(Line5, "    - by Team 2 -   ");
    // Keypad_Test();
    // Tone_Test(100);
    DelayMs(500);

		
		startGame((uint16_t*)LS_NOTE, (int*)LS_XPOS, (int*)LS_YPOS, LS_NOTE_PER_VERSE, LS_VERSE_COUNT ,gameLevel);
	
		if(success[0]){
			gameLevel=2;
			startGame((uint16_t*)APPLE_NOTE, (int*)APPLE_XPOS, (int*)APPLE_YPOS, APPLE_NOTE_PER_VERSE, APPLE_VERSE_COUNT,gameLevel);
			success[0]=false;
		}
		else if(success[1]){
			gameLevel=3;
			startGame((uint16_t*)BELL_NOTE, (int*)BELL_XPOS, (int*)BELL_YPOS, BELL_NOTE_PER_VERSE, BEEL_VERSE_COUNT,gameLevel);
			success[1]=false;
		}
		else if(succes[2]){ //level4
			gameLevel=4;
			//startGame((uint16_t*)APPLE_NOTE, (int*)APPLE_XPOS, (int*)APPLE_YPOS, APPLE_NOTE_PER_VERSE, APPLE_VERSE_COUNT,gameLevel); 
			success[2]=false;
		}
}

void startGame(uint16_t* note, int* xpos, int* ypos, int notePerVerse, int verseCount, int level) {
    int i, j, currVerse = 0, keyState, playerX, playerY;
		int gLevel = level;
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
            GLCD_Printf(Line0, "LEVEL:%d / SCORE:%-4d", gLevel, gameScore);
            GLCD_DisplayStringLn(Line9, "TIME: ");
						
						if(i==1){ //게임이 시작되면 timer 시작.
							Timer0_Start();
							switch(gLevel){
								case 1 :
									time = 40;
									GLCD_DisplayStringLn(Line9, "       %d", time);
									break;
								case 2 :
									time = 30;
									GLCD_DisplayStringLn(Line9, "       %d", time);
									break;
								case 3 :
									time = 25;
									GLCD_DisplayStringLn(Line9, "       %d", time);
									break;
								case 4 :
									time = 20;
									GLCD_DisplayStringLn(Line9, "       %d", time);
									break;
							}
						}

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
						
						if(i==notePerVerse && (j+1)==verseCount){
							if(time >= 0){
								success[gLevel-1] = true;
								GLCD_Clear(Black);
								GLCD_DisplayStringLn(Line5, "     GAME CLEAR    ");
								Delay(2000);
							}
							else{
								success[gLevel-1] = false;
								GLCD_Clear(Black);
								GLCD_DisplayStringLn(Line5, "     GAME  OVER    ");
								Delay(2000);
							}
						}
        }
        currVerse ++;
    }
}

// 타이머는 1초간격 -> 위쪽에 남은시간 표시 TODO
void TIMER0_IRQHandler(void) { // 100ms
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
		time--;
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
