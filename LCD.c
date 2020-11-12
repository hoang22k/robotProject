#include "LCD.h"
#include "gpio.h"
#include "stm32f10x.h"
#include <string.h>

#define LCD_8B2L 0x38 // ; Enable 8 bit data, 2 display lines
#define LCD_DCB 0x0F // ; Enable Display, Cursor, Blink
#define LCD_MCR 0x06 // ; Set Move Cursor Right
#define LCD_CLR 0x01 // ; Home and clear LCD
#define LCD_LN1 0x80 // ;Set DDRAM to start of line 1
#define LCD_LN2 0xC0 // ; Set DDRAM to start of line 2

#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //

void stringInput(char c[])
{
	int i=0;
	while (c[i] != NULL)
	{
		dataToLCD(c[i]);
		i++;
	}	
}

void LCD_Init()
{
	commandToLCD(0x38);
	commandToLCD(0x38);
	commandToLCD(0x38);
	commandToLCD(0x38);
	commandToLCD(0x0f);
	commandToLCD(0x01);
	commandToLCD(0x06);
}
 
void commandToLCD(uint8_t data)
{
	GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
// GPIOC->ODR = data; //BAD: may affect upper bits on port C
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay_lcd (8000);
	GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
	delay_lcd (80000);
}


void dataToLCD (uint8_t data)
{
	GPIOB->BSRR = LCD_DM_ENA; //RS low, E high
	GPIOC->ODR &= 0xFF00; 
	GPIOC->ODR |= data; 	
	delay_lcd (8000);
	GPIOB->BSRR = LCD_DM_DIS; 
	delay_lcd (8000);	
}


void delay_lcd(uint32_t a)
{	
	while (a>0)
	a--;
}

void getOutput(uint16_t x)
{			
	if (x == 0xf3)		// If blue and green 
		displayName();
	else	if (x==0xef)
		dataToLCD('1');
	else displayWait();	
}

void displayName(void)
{
		stringInput("Danny");
		commandToLCD(LCD_LN2);
		stringInput("200 354 230");
		commandToLCD(LCD_LN1);
}

void displayWait(void)
{
		stringInput("Waiting");
		delay(120000);
		commandToLCD(LCD_CLR);
}
