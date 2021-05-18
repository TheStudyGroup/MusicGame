#include "Timer/Timer.h"
#include "Tone/Tone.h"

int main(void)
{

    Timer0_Init();
    Timer0_Start();

    Tone_Init();

    while (1) {    
        Tone_PlaySineWave(NOTE_C4);
        Delay(SEC_1);
        Tone_PlaySineWave(NOTE_D4);
        Delay(SEC_1);
        Tone_PlaySineWave(NOTE_E4);
        Delay(SEC_1);
        Tone_PlaySineWave(NOTE_F4);
        Delay(SEC_1);
        Tone_PlaySineWave(NOTE_G4);
        Delay(SEC_1);
        Tone_PlaySineWave(NOTE_A4);
        Delay(SEC_1);
        Tone_PlaySineWave(NOTE_B4);
        Delay(SEC_1);
        Tone_PlaySineWave(NOTE_C4);
        Delay(SEC_1);
    }
}
