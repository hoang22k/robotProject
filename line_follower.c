#include "line_follower.h"
#include "ultrasonic_sensor.h"
#include "lcd.h"
#include "pwm.h"
#include "gpio.h"
#include "heat_sensor.h"

  void LineFollowerInit()						// using ADC Alternative funtion to take analog inputs
 {
	RCC->APB2ENR|= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRL = 0x40400444;

	ADC1->CR2 = 0x00000001;
 }

int readLine (void)		// PA 3
{
	ADC1->SQR3 = 0x00000003;
	ADC1->CR2 = 0x00000001;
	
	ADC1->SR = ADC1->SR & 0x2;
	
	while (ADC1->SR==0x0)
	{
	}
	int result = ADC1->DR;
	return result;
}

int readLine_2 (void)	// PA4
{
	ADC1->SQR3 = 0x00000004;
	ADC1->CR2 = 0x00000001;
	
	ADC1->SR = ADC1->SR & 0x2;
	
	while (ADC1->SR==0x0)
	{
	}
	int result = ADC1->DR;
	return result;
}


int readLine_3 (void)		//PA 6
{
	ADC1->SQR3 = 0x00000006;
	ADC1->CR2 = 0x00000001;
	
	ADC1->SR = ADC1->SR & 0x2;
	
	while (ADC1->SR==0x0)
	{
	}
	int result = ADC1->DR;
	return result;
}

int readLine_4 (void)		//PA 7
{
	ADC1->SQR3 = 0x00000007;
	ADC1->CR2 = 0x00000001;
	
	ADC1->SR = ADC1->SR & 0x2;
	
	while (ADC1->SR==0x0)
	{
	}
	int result = ADC1->DR;
	return result;
}





void navigate ()
{
	while ((readHeat() == 0))																//  using a heat sensor to start the robot
	{
		int L1 = readLine();																	// L1 - mid left
		int L2 = readLine_2();																// L2 - mid right
		int L3 = readLine_3();																// L3 - left
		int L4 = readLine_4();																// L4 - right
																													// L1, L2, L3 are different sensors from L4, hence the values indicate black and white are different
		
		if ( (L1 > 0xF00) && (L2 > 0xF00) && (L3 < 0xF00) && (getEcho_front() > 600))		// conditions to go straight
		{																																								// mid sensors in black line and not left seonsor, while front has space
			GPIOB->CRH = GO_STRAIGHT;
			delay(600000);
			GPIOB->CRH =  STOP;
			delay(400000);			
		}
		
		 else if ((L1 < 0xF00) && (L2 < 0xF00) && (L3 < 0xF00) && (L4 > 4000))		//  conditions to turn left 
		{
			while((L1 < 0xf00) && (L2 < 0xf00))																			// only turn when the mid-sensors detect white
			{																																				// stop when black line is found
				GPIOB->CRH = TURN_LEFT;
				delay (3000000);																											// time needed for the robot to turn 90 degree
				GPIOB->CRH = STOP;
			}		
		}
		
		else if ((L1 < 0xF00) || (L2 < 0xF00) )								// Adjust left - when the robot is out of line
		{
			if((L1 > 0xf00) &&( L2 < 0xF00) )	
			{
			GPIOB->CRH = TURN_LEFT; 
			delay(300000);
			GPIOB->CRH =  STOP;	
			}
			else if((L1 < 0xF00) && (L2 > 0xF00))
			{
			GPIOB->CRH = TURN_RIGHT;
			delay(300000);
			GPIOB->CRH =  STOP;
			}
			else if ((L3 > 0xF00) && (L1 < 0xF00) && (L2 < 0xF00) )
			{
					GPIOB->CRH = TURN_LEFT; 
					delay(300000);
					GPIOB->CRH =  STOP;
			}
			else if ((L4 < 0XF00 ) && (L1 < 0xF00) && (L2 < 0xF00))
				{
				GPIOB->CRH = TURN_RIGHT; 
				delay(300000);
				GPIOB->CRH =  STOP;
				}		
		}																														 // end adjust left

		else if((L1 > 0xF00) && (L2 > 0xF00) && (L3 < 0xF00) && (L4 < 4000)) 	// 3 way 
		{	
			if (getEcho_front() < 2000) 
			{
				GPIOB->CRH = TURN_RIGHT;
				delay (400000);
				GPIOB->CRH = STOP;
			}
		}
		
		else if ((L1 > 0xF00) && (L2 > 0xF00) && (L3 > 0xF00))  
		{

			if((readLine_4() < 4000))															// all four sensors found black - 3 way or room number lines detected
			{
				int F = getEcho_front();
				if (F < 2000)
				{
					GPIOB->CRH = TURN_LEFT;
					delay (3000000);
					GPIOB->CRH = STOP;
				}
				else if (F > 2000) 
					countLine();
			}
			
			else if(readLine_4() > 4000)													// right sensor found white - 3 way
			{
				GPIOB->CRH = TURN_LEFT;
				delay (3000000);
				GPIOB->CRH = STOP;
			}
		}

		else																										// robot is in non-mentioned positions
		{
			stringInput("Out of Range!!");
			commandToLCD(LCD_CLR);
		}
	}
}	




int countLine ()												// if all 4 sensors detect black, then start counting (PA6)
{
	int counter = 1;
	int time = 14, temp = 1;
	int a = 0;
	int b = 0 ;
	
	while (time > 0)
	{
		int L = readLine();
		int R = readLine_2();
		if ((L > 0xF00) && (R > 0xF00))			// go straight when 2 mid-sensors detect balck
		{
			GPIOB->CRH = GO_STRAIGHT;
			delay(700000);
			GPIOB->CRH =  STOP;
			delay(400000);
		}
		else if ((L>0xF00)&&(R<0xF00))			// adjust if 2 mid-sensors are not in line
		{
			GPIOB->CRH = TURN_LEFT;
			delay(250000);
			GPIOB->CRH =  STOP;
		}
		else 
		{
			GPIOB->CRH = TURN_RIGHT;
			delay(250000);
			GPIOB->CRH =  STOP;
		}
		
		a = readLine_3();									// using left sensor to count lines

		if(a < 0xF00)											// assign numbers to black and white			
			a = 1;													// 1 - white, 2 - black
		else 
			a = 2;

		if(a != temp)											// if old and new vlaue are different, this indicates a new color is found
			counter++;
		temp = a;													// update the old value
				
		time--;
}
	
	if (counter != 0)										// print if counter is not zero
		{
			commandToLCD(LCD_LN1);
			stringInput("ROOM: ");
			print(counter/2);
			stringInput("     ");
		}
	else 
	{
			commandToLCD(LCD_LN1);
			stringInput("Not Found");
	}
	
	GPIOB->CRH = STOP ;
	LED_flash();												// LEDs flash to catch attention
	delay(10000000);
	LED_off();
	navigate();													// back to navigate
	return (counter/2);

}

