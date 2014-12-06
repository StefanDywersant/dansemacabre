// (c) 2006 Karol Maciaszek <karol.maciaszek@gmail.com>

#include "struct.h"

void blinkLight0();
void blinkLight1();
void blinkLight2();
void blinkLight3();void moveJump();
void moveSkull();
void moveLCalf();
void moveLElbow();
void moveLFoot();
void moveLForearm();
void moveLHand();
void moveLThigh();
void moveRCalf();
void moveRElbow();
void moveRFoot();
void moveRForearm();
void moveRHand();
void moveRThigh();
void timerFunc(int a);
void keyEvent(unsigned char c,int x, int y);
void displayFrame(void);
void renderPart(TPart *p);
void renderTriangle(TTriangle *t);
void renderLines(TTriangle *t);
void renderPoints(TTriangle *t);
void renderLight();
int main(int argc, char* argv[]);
