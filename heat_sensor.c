#include "heat_sensor.h"
#include "lcd.h"
#include "gpio.h"

void heatInit()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
}

int readHeat()			
{
	uint16_t data;
	data = ((GPIOA->IDR & GPIO_IDR_IDR15 )>>15);		// Take a digital input from PA15
	return data;	
}

