#include <stdint.h>
#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>
#include "adc.h"

#define TURN_LEFT 0x334444343
#define TURN_RIGHT 0x33444334
#define GO_STRAIGHT 0x33444344
#define STOP 0x33444333

int readLine (void); 
int readLine_2 (void);
int readLine_3 (void);
void navigate();
int countLine();
void checkLine (float);
int readLine_4 (void);		//PA 7
void countTarget();
void checkRoom();
void target();
int readWall();