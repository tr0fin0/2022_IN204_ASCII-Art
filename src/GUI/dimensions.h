#include <string>


int imageW = 1000;
int imageH = 380;


int windowW = 1*imageW;
int windowH = 1*imageH;
int windowB = 10;


int boxImgX = (windowW - imageW)/2;
int boxImgY = (windowH - imageH)/2;


int alignReturnW = 0;       // 0
int alignReturnH = 0;       // 0
int alignReturnB = 0;       // 0
int buttonIPW  = 80;    // 10
int buttonIPH  = 10;    // 10
int buttonIPB  = 10;    // 10
int boxReturnX = boxImgX;
int boxReturnY = boxImgY;


int alignButtonsW = 0;
int alignButtonsH = 0;
int alignButtonsB = 0;  // 0
int buttonsW = 160;      // 1
int buttonsH = 10;      // 1
int buttonsB = 1;       // 1
int boxButtonsX = windowW/2-buttonsW/2;
int boxButtonsY = windowH;