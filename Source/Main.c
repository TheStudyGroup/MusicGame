#include "GLCD.h"
#include "Tone.h"
#include "Timer.h"
#include "Keypad.h"
#include "Utility.h"
#include "../Resource/Resource.h"

uint8_t led = 0;

int gameLevel, gameScore, gameTime = 0;

void startGame(void);
bool startLevel(const GameLevel* level);
void Keypad_Test(void);


int main(void) {
    SystemInit();
    LED_Init();
    Keypad_Init(KEYPAD_TYPE_C);
    Tone_Init(70); // volume
    GLCD_Init();
    Timer0_Init(100);
    Timer0_Start();

    GLCD_Clear(Black);
    GLCD_SetBackColor(Black);
    GLCD_SetTextColor(White);
    GLCD_DisplayStringLn(Line2, " < MicroProcessor > ");
    GLCD_DisplayStringLn(Line4, "    Music TokTok    ");
    GLCD_DisplayStringLn(Line6, "    - by Team 2 -   ");
    // Keypad_Test();
    Tone_Test(100);
    DelayMs(1000);

    while (1) {
        startGame();
    }
}

void startGame(void) {
    int i, totalScore = 0;
    gameLevel = 1;

    for (i = 0; i < 4; i++) {
        gameScore = 10;
        bool result = startLevel(&gameLevels[i]);

        if (result) {
            gameTime = 0;
            GLCD_Printf(Line5, "   GAME CLEAR !!!   ");
            DelayMs(300);
            Tone_Play(NOTE_C5); DelayMs(120);
            Tone_Stop();        DelayMs(30);
            Tone_Play(NOTE_E5); DelayMs(120);
            Tone_Stop();        DelayMs(30);
            Tone_Play(NOTE_G5); DelayMs(120);
            Tone_Stop();        DelayMs(30);
            Tone_Play(NOTE_C5); DelayMs(120);
            Tone_Stop();        DelayMs(30);
            DelayMs(1000);
        } else {
            break;
        }

        gameLevel++;
        totalScore += gameScore;
    }

    if (i == 4) {
        GLCD_ClearLine(Line5);
        GLCD_Printf(Line3, "   ALL CLEAR !!!   ");
        GLCD_Printf(Line4, " Total Score: %d", totalScore);
    } else {
        if (gameTime > 0) {
            GLCD_Printf(Line4, "   GAME OVER ...   ");
        } else {
            GLCD_Printf(Line4, "   TIME OVER ...   ");
        }
        gameTime = 0;
        Tone_Play(NOTE_F6); DelayMs(100);
        Tone_Stop();        DelayMs(50);
        Tone_Play(NOTE_F6); DelayMs(100);
        Tone_Stop();        DelayMs(50);
    }
    GLCD_Printf(Line6, " Press key to replay");
    while(Keypad_Scan() != KEYPAD_NOKEY);
    while(Keypad_Scan() == KEYPAD_NOKEY);
    while(Keypad_Scan() != KEYPAD_NOKEY);
}

bool startLevel(const GameLevel* level) {
    int i, j, currVerse = 0, keyState, playerX, playerY;

    GLCD_Clear(Black);
    GLCD_Printf(Line2, "  < Music TokTok >  ");
    GLCD_Printf(Line4, "  >> LEVEL %d", gameLevel);
    GLCD_Printf(Line6, "  >> %s", level->name);
    DelayMs(1000);
    GLCD_Clear(Black);
    gameTime = level->time;

    while (currVerse != level->verseCount) {
        // Draw player
        j = currVerse * (level->notePerVerse + 1);
        playerX = level->xpos[j];
        playerY = level->ypos[j];
        GLCD_DrawBitmap(playerX, playerY, IMAGE_HEIGHT, IMAGE_WIDTH, Res_GetPlayerImage());

        for (i = 1; i <= level->notePerVerse; i++) { // Draw notes
            j = currVerse * (level->notePerVerse + 1) + i;
            GLCD_DrawBitmap(level->xpos[j], level->ypos[j], IMAGE_HEIGHT, IMAGE_WIDTH, Res_GetNoteImage(level->notes[j]));
        }

        for (i = 1; i <= level->notePerVerse; i++) {
            GLCD_Printf(Line0, "LEVEL:%d / SCORE:%-4d", gameLevel, gameScore);
            GLCD_Printf(Line9, "TIME:%-3d", gameTime / 10);

            j = currVerse * (level->notePerVerse + 1) + i;
            keyState = KEYPAD_NOKEY;
            while (keyState == KEYPAD_NOKEY) {
                keyState = Keypad_Scan();
                if (gameTime % 10 == 0) GLCD_Printf(Line9, "TIME:%-3d", gameTime / 10);
                if (gameTime == 0) return false;
            }
            while (Keypad_Scan() != KEYPAD_NOKEY) {
                if (gameTime % 10 == 0) GLCD_Printf(Line9, "TIME:%-3d", gameTime / 10);
                if (gameTime == 0) return false;
            }

            GLCD_ClearRect(playerX, playerY, IMAGE_HEIGHT, IMAGE_WIDTH, Black);
            playerX = level->xpos[j];
            playerY = level->ypos[j];
            GLCD_DrawBitmap(playerX, playerY, IMAGE_HEIGHT, IMAGE_WIDTH, Res_GetPlayerImage());
                
            if (keyState == Res_NoteToKeypad(level->notes[j])) { // OK
                gameScore += 1;
                Tone_Play(level->notes[j]);
                DelayMs(100);
            } else { // FAIL
                gameScore -= 10;
                Tone_Play(NOTE_F6);
                DelayMs(100);
                if (gameScore <= 0) {
                    gameScore = 0;
                    GLCD_Printf(Line0, "LEVEL:%d / SCORE:%-4d", gameLevel, gameScore);
                    GLCD_Printf(Line9, "TIME:%-3d", gameTime / 10);
                    return false;
                }
            }
            Tone_Stop();

        }
        GLCD_ClearRect(playerX, playerY, IMAGE_HEIGHT, IMAGE_WIDTH, Black);
        currVerse ++;
    }

    return true;
}


void TIMER0_IRQHandler(void) { // 100ms
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
    if (gameTime > 0) {
        gameTime--;
    }
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
