#include "Resource.h"

// 작은별(LittleStar=LS)
// 도도솔솔 라라 솔 파파미미 레레도
// 솔솔 파파미미레 솔솔 파파미미레
// 도도솔솔 라라 솔 파파미미 레레도

#define STAR_NPV 14        // 절 하나에 음표 14개
#define STAR_VC   3         // 3절까지 있음
uint16_t STAR_NOTE[(STAR_NPV+1) * STAR_VC] = {
    0, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
    0, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    0, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
};
int STAR_XPOS[(STAR_NPV+1) * STAR_VC] = { // 각각음표 x좌표
    /* player */  20,  /* 1st verse */  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,  20,  20,
    /* player */  20,  /* 2nd verse */  20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,
    /* player */  70,  /* 3rd verse */  20,  20,  20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170,
    };
int STAR_YPOS[(STAR_NPV+1) * STAR_VC] = { // y좌표
    /* player */  45,  /* 1st verse */  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165, 165, 125,
    /* player */ 125,  /* 2nd verse */  85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165,
    /* player */ 165,  /* 3rd verse */ 165, 125,  85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165,
};


// 사과같은 내 얼굴(apple)
// 도레 미미 파미레 레미파파 솔파미
// 미파솔솔 도라솔솔 도레미미레도
#define APPLE_NPV 14        // 절 하나에 음표 14개
#define APPLE_VC   2         // 2절까지 있음 
uint16_t APPLE_NOTE[(APPLE_NPV+1) * APPLE_VC] = {
    0, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
    0, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4
};
int APPLE_XPOS[(APPLE_NPV+1) * APPLE_VC] = { // 각각음표 x좌표
     20,       70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,  20,  20,
     20,       20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,
};
int APPLE_YPOS[(APPLE_NPV+1) * APPLE_VC] = { // y좌표
     45,       45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165, 165, 125,
     125,      85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165,
};

//학교종이 땡땡땡(BELL)
//솔솔라라 솔솔미 솔솔미미레
//솔솔라랄 솔솔미 솔미레미도
#define BELL_NPV 12        // 절 하나에 음표 12개
#define BELL_VC   2         // 2절까지 있음 
uint16_t BELL_NOTE[(BELL_NPV+1) * BELL_VC] = {
    0, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4,
    0, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4,  NOTE_C4,
};
int BELL_XPOS[(BELL_NPV+1) * BELL_VC] = { // 각각음표 x좌표
    20,     70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120, 70,
    70,     20,  20,  20,  20,  70, 120, 170, 220, 270, 270, 270, 270,  
};
int BELL_YPOS[(BELL_NPV+1) * BELL_VC] = { // y좌표
    45,      45,  45, 45, 45, 45, 85, 125, 165, 165, 165, 165, 165,
    165,    165, 125, 85, 45, 45, 45,  45,  45,  45,  85, 125, 165, 
};


const GameLevel gameLevels[] = {
    { "Little Star", 200, STAR_NPV,  STAR_VC,  STAR_NOTE,  STAR_XPOS,  STAR_YPOS  },
    { "Apple Face",  150, APPLE_NPV, APPLE_VC, APPLE_NOTE, APPLE_XPOS, APPLE_YPOS },
    { "School Bell", 150, BELL_NPV,  BELL_VC,  BELL_NOTE,  BELL_XPOS,  BELL_YPOS  },
};
