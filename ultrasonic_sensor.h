#include "clocks.h"
#include "gpio.h"
#include "LCD.h"
#include "adc.h"
#include "pwm.h"
#include <stdint.h>

uint16_t getEcho_front (void );
void sonic (void);
uint16_t getEcho_left (void );
uint16_t getEcho_right (void );
void getDirection();

void readLaser();
