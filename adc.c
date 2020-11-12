#include "adc.h"
#include "lcd.h"
#include "gpio.h"

void adc_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
	GPIOA-> CRL = 0x44444004;
	ADC1->CR2 = 0x00000001;
}

void adc_read (void)
{
	ADC1->SQR3 = 0x00000002;
	ADC1->CR2 = 0x00000001;
	
	ADC1->SR = ADC1->SR & 0x2;
	
	
	while (ADC1->SR==0x0)
	{
	}
	translate(ADC1->DR,1);


	
}



void adc_read_temp (void)
{
	ADC1->SQR3 = 0x00000001;
	ADC1->CR2 = 0x00000001;
	
	ADC1->SR = ADC1->SR & 0x2;
	
	while (ADC1->SR==0x0)
	{
	}
	translate(ADC1->DR,2);
	
//	if (ADC1->SR == 0x2)
//	{		
//	translate(ADC1->DR, 2);
//	//reg_out(ADC1->DR);
//	}
	
}



int translate (uint32_t data, int x)
{
	
	uint16_t b = (data & 0x0f00)>>8;
	uint16_t c = (data & 0x00f0)>>4;
	uint16_t d = (data & 0x000f);
	
	b = b*(16*16);
	c = c* 16;
	
	float result =  (b + c + d)*0.7;
	char array [4];
	
	sprintf(array, "POT: %.2f V", result);
	stringInput(array);	
	delay_lcd(999999);
	commandToLCD(LCD_CLR);
	
	return result;
}

void reg_out( uint32_t reg_data)
	{

	int i;
	uint32_t shifted_val;
	uint8_t print_val;
	dataToLCD (0x30);
	dataToLCD (0x78);
	for ( i=28; i >= 0 ; i = (i-4))
	{
	shifted_val = (reg_data >> i) & 0xf;
	print_val = ( to_ascii(shifted_val));
	dataToLCD(print_val);
	//function(shifted_val);
	}
	dataToLCD(0x20);
	delay_lcd(999999);
	
	commandToLCD(LCD_CLR);
}
	
int to_ascii (uint32_t a)
{
	if (a == 0x1)
		return 0x31;
	else if (a==0x2)
		return 0x32;
	else if(a==0x3)
		return 0x33;
	else if(a==0x4)
		return 0x34;
	else if(a==0x5)
		return 0x35;
	else if(a==0x6)
		return 0x36;
	else if(a==0x7)
		return 0x37;
	else if(a==0x8)
		return 0x38;
	else if(a==0x9)
		return 0x39;

	else if(a==0xa)
		return 0x41;
	else if(a==0xb)
		return 0x42;
	else if(a==0xc)
		return 0x43;
	else if(a==0xd)
		return 0x44;
	else if(a==0xe)
		return 0x45;
	else if(a==0xf)
		return 0x46;
	
	else 
		return 0x30;
}



void print(float data){
	char array [10];
	sprintf(array, "%.0f", data);
	stringInput(array);
	delay(2000000);
}