#include "Resource.h"

// 나비야 (Butterfly)
// 솔미미미 파레레 도레미파 솔솔솔
// 솔미미미 파레레 도미솔솔 미미미
// 레레레레 레미파 미미미미 미파솔
// 솔미미미 파레레 도미솔솔 미미미
// c d e f g a b
#define BUTTER_NPV 14   // 절 하나당 14개 
#define BUTTER_VC   4   // 총 4절 
uint16_t BUTTER_NOTE[(BUTTER_NPV+1) * BUTTER_VC] = {
    0, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
    0, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4,
	0, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
    0, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4,
};
int BUTTER_XPOS[(BUTTER_NPV+1) * BUTTER_VC] = {
    /* player */ 20,  /* 1st verse */   70, 120, 170, 220, 270, 270, 270, 220, 170, 120,  70,  20,  20,  70,
    /* player */ 70,  /* 2nd verse */  120, 170, 220, 270, 270, 270, 270, 220, 170, 170, 120,  70,  20,  20,
    /* player */ 20,  /* 3rd verse */   20,  70, 120, 120, 120, 120, 170, 220, 270, 270, 270, 220, 220, 170,
    /* player */ 170,  /* 3rd verse */ 120,  70,  20,  20,  20,  20,  70, 120, 170, 170, 220, 270, 270, 270,
};
int BUTTER_YPOS[(BUTTER_NPV+1) * BUTTER_VC] = { // y축
    /* player */  45,  /* 1st verse */  45,  45,  45, 45, 45, 85, 125, 125, 125, 125, 125, 165, 165,
    /* player */ 165,  /* 2nd verse */ 165, 165, 165, 165, 125, 85, 45, 45, 45, 85,  85,  85,  85, 125,
    /* player */ 125,  /* 3rd verse */ 165, 165, 165, 125,  85, 45, 45, 45, 45, 85, 125, 125, 165, 165,
    /* player */ 165,  /* 3rd verse */ 165, 165, 165, 125,  85, 45, 45, 45, 45, 85,  85,  85, 125, 165,
};

// 작은별(Star)
// 도도솔솔 라라 솔 파파미미 레레도
// 솔솔 파파미미레 솔솔 파파미미레
// 도도솔솔 라라 솔 파파미미 레레도
#define STAR_NPV 14     // 절 하나에 음표 14개
#define STAR_VC   3     // 3절까지 있음
uint16_t STAR_NOTE[(STAR_NPV+1) * STAR_VC] = {
    0, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
    0, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    0, NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
};
int STAR_XPOS[(STAR_NPV+1) * STAR_VC] = {
    /* player */  20,  /* 1st verse */  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,  20,  20,
    /* player */  20,  /* 2nd verse */  20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,
    /* player */  70,  /* 3rd verse */  20,  20,  20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170,
    };
int STAR_YPOS[(STAR_NPV+1) * STAR_VC] = {
    /* player */  45,  /* 1st verse */  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165, 165, 125,
    /* player */ 125,  /* 2nd verse */  85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165,
    /* player */ 165,  /* 3rd verse */ 165, 125,  85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165,
};


// 사과같은 내 얼굴 (apple)
// 도레 미미 파미레 레미파파 솔파미
// 미파솔솔 도라솔솔 도레미미레도
#define APPLE_NPV 14     // 절 하나에 음표 14개
#define APPLE_VC   2     // 2절까지 있음 
uint16_t APPLE_NOTE[(APPLE_NPV+1) * APPLE_VC] = {
    0, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
    0, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4
};
int APPLE_XPOS[(APPLE_NPV+1) * APPLE_VC] = {
     20,       70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,  20,  20,
     20,       20,  20,  70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120,  70,
};
int APPLE_YPOS[(APPLE_NPV+1) * APPLE_VC] = {
     45,       45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165, 165, 125,
     125,      85,  45,  45,  45,  45,  45,  45,  85, 125, 165, 165, 165, 165, 165,
};

// 학교종이 땡땡땡(BELL)
// 솔솔라라 솔솔미 솔솔미미레
// 솔솔라랄 솔솔미 솔미레미도
#define BELL_NPV 12     // 절 하나에 음표 12개
#define BELL_VC   2     // 2절까지 있음 
uint16_t BELL_NOTE[(BELL_NPV+1) * BELL_VC] = {
    0, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4,
    0, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4,  NOTE_C4,
};
int BELL_XPOS[(BELL_NPV+1) * BELL_VC] = {
    20,     70, 120, 170, 220, 270, 270, 270, 270, 220, 170, 120, 70,
    70,     20,  20,  20,  20,  70, 120, 170, 220, 270, 270, 270, 270,  
};
int BELL_YPOS[(BELL_NPV+1) * BELL_VC] = {
    45,      45,  45, 45, 45, 45, 85, 125, 165, 165, 165, 165, 165,
    165,    165, 125, 85, 45, 45, 45,  45,  45,  45,  85, 125, 165, 
};


const GameLevel gameLevels[] = {
    // { "Butterfly",   500, BUTTER_NPV, BUTTER_VC, BUTTER_NOTE, BUTTER_XPOS, BUTTER_YPOS },
    { "Little Star", 200, STAR_NPV,   STAR_VC,   STAR_NOTE,   STAR_XPOS,   STAR_YPOS   },
    { "Apple Face",  150, APPLE_NPV,  APPLE_VC,  APPLE_NOTE,  APPLE_XPOS,  APPLE_YPOS  },
    { "School Bell", 150, BELL_NPV,   BELL_VC,   BELL_NOTE,   BELL_XPOS,   BELL_YPOS   },
};
