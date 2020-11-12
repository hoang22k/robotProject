#include "stm32f10x.h"
#include "clocks.h"
#include "gpio.h"
#include "LCD.h"
#define LCD_LN2 0xC0 // ; Set DDRAM to start of line 2
#define LCD_CLR 0x01 // ; Home and clear LCD
#define LCD_LN1 0x80 // ;Set DDRAM to start of line 1


uint16_t getInput(void)
{
	uint16_t sw1_val;

	sw1_val = (((( GPIOA->IDR & ( GPIO_IDR_IDR6 )) << 1) \ 
						| (( GPIOA->IDR & ( GPIO_IDR_IDR7 )) >> 1) \
						| (( GPIOC->IDR & ( GPIO_IDR_IDR10 )) >> 5) \
						| (( GPIOC->IDR & ( GPIO_IDR_IDR11 )) >> 7)) \
						 

	
						| ((( GPIOB->IDR & ( GPIO_IDR_IDR8 )) >> 8 ) \
						| (( GPIOB->IDR & ( GPIO_IDR_IDR9 )) >> 8 ) \
						| (( GPIOC->IDR & ( GPIO_IDR_IDR12 )) >> 10 ) \
						| (( GPIOA->IDR & ( GPIO_IDR_IDR5 )) >> 2 ))) \
						& 0xFF;
	
	return (sw1_val);
}	




/////////////////////////////////////////////////
void update_LEDS(uint16_t LED_val)
{
//	uint16_t temp_ODR;
//	temp_ODR = GPIOA->ODR&0xE1FF;
//	temp_ODR=temp_ODR|(LED_val<<9 & 0x1E00);
//	GPIOA->ODR=temp_ODR;
	
	if (LED_val==0xF3)			// Blue AND Green button 
		LED_right();
		else if (LED_val==0xFC)	// Red AND Black Buttons
			LED_left();
			else if (LED_val==0x0F)	// All 4 switches
				LED_flash();
				else
					LED_off();
}

void LED_off()
{
		GPIOA->ODR=0x1E00;
}

void LED_flash ()
{
	GPIOA->ODR=0x0000;
	delay (1200000);
	GPIOA->ODR=0x1E00;
	delay (1200000);
}	

void LED_right() 
{
	GPIOA->ODR=0x1C00;
	delay (1200000);
	GPIOA->ODR=0x1A00;
	delay (1200000);
	GPIOA->ODR=0x1700;
	delay (1200000);
	GPIOA->ODR=0x0C00;
	delay (1200000);
}

void LED_left()
{
	GPIOA->ODR=0x0C00;
	delay (1200000);
	GPIOA->ODR=0x1700;
	delay (1200000);
	GPIOA->ODR=0x1A00;
	delay (1200000);
	GPIOA->ODR=0x1C00;
	delay (1200000);
}


void delay(int i )
{	
	while (i>0)
	i--;
}









