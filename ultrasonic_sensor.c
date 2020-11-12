#include "ultrasonic_sensor.h"
#include "line_follower.h"

//-----------------Ultrasonic Sensor----------------


// stop when counter is 950 - 1100
// when counter is more than 3200, a room is detetcted
uint16_t getEcho_front ()	// PB 10 as trigger for echo front 
{
	GPIOB->ODR |= GPIO_ODR_ODR10;
	delay (60);																	// triger pulse
	GPIOB->ODR &= ~GPIO_ODR_ODR10;
	int i = 200000;	
	uint16_t ultra, counter = 0;
	while (i>0)
	{
		ultra = ((GPIOB->IDR & ( GPIO_IDR_IDR11)) >>11)& 0xf ;
		if(ultra==0x01)
		{
		counter++;
		}		
		i--;			
	}
	if(counter < 10)
		counter = 6000;
	return counter;	
}


uint16_t getEcho_left ()	// PB 14 as trigger for echo left 
{
	GPIOB->ODR |= GPIO_ODR_ODR14;
	delay (60);
	GPIOB->ODR &= ~GPIO_ODR_ODR14;
	int i = 200000;

	uint16_t ultra, counter = 0;
	while (i>0)
	{	
		ultra = ((GPIOB->IDR & ( GPIO_IDR_IDR12)) >>12)& 0xf ;
		if(ultra==0x01)
		{
		counter++;
		}
		i--;	
	}
	if(counter < 10)
		counter = 6000;
	
	return counter;	
}

uint16_t getEcho_right ()	// PB 15 right trigger
{
	GPIOB->ODR |= GPIO_ODR_ODR15;
	delay (60);
	GPIOB->ODR &= ~GPIO_ODR_ODR15;
	int i = 200000;

	uint16_t ultra, counter = 0;
	while (i>0)
	{	
		ultra = ((GPIOB->IDR & ( GPIO_IDR_IDR13)) >>13)& 0xf ;
		if(ultra==0x01)
		{
		counter++;
		}		
		i--;	
	}
	return counter;	
}


/* 	This is our original plan to get the robot to run along the walls.
		However, the sensors stoped working before we started filming.
		So we decided not to use it. This is only for referrence.
*/
void getDirection ()
{

	while (1)
	{	
		int F = getEcho_front();
		int L = getEcho_left();
		int R = getEcho_right();

		print(F);
		commandToLCD(LCD_LN2);
		print (L);
		stringInput("   ");
		print(R);
		commandToLCD(LCD_CLR);
		
	if ((F > 500) && (L < 600) && (L > 200) )	// GO STRAIGHT
	{
		while ((getEcho_front() > 500) && (getEcho_left() < 600) && (getEcho_left() > 200) )
		{
		GPIOB->CRH = GO_STRAIGHT;
		delay(1500000);	
		GPIOB->CRH = STOP;
		delay(500000);
		target();
		}		
	}	
	else if ((F > 800) && (L > 600) ) // ADJUST LEFT & EXIT ROOM
	{	 
		
		if ((L > 600) && (L < 2000))    // ADJUST LEFT 
		{
			while (getEcho_left() > 600) 		
			{
				GPIOB->CRH = TURN_LEFT;
				delay(1000000);	
				GPIOB->CRH = STOP;
			}
		}
		
		else if (L > 3000)							//EXIT ROOM
		{
			GPIOB->CRH = TURN_RIGHT;
			delay(2000000);
			GPIOB->CRH = STOP;
			delay(1000000);
			GPIOB->CRH = TURN_LEFT;
			delay(2000000);
			GPIOB->CRH = STOP;
			delay(500000);			
			GPIOB->CRH = GO_STRAIGHT;
			delay(2500000);	
			GPIOB->CRH = STOP;
			GPIOB->CRH = TURN_LEFT;
			delay(3500000);	
			
			
			GPIOB->CRH = GO_STRAIGHT;
			delay(3000000);
						
			while ((readLine() < 0xF00) && (readLine_2() < 0xf00) & (readLine_3() < 0xF00))
				{
					GPIOB->CRH = GO_STRAIGHT;					
				}	
				GPIOB->CRH = STOP;
				delay(2000000);
				navigate();
			}
			
		}
	
	else if (( F < 800 ) && (F>6) && (L < 800))	// TURN RIGHT 
	{		
		GPIOB->CRH = TURN_RIGHT;
		delay(5000000);	
		GPIOB->CRH = STOP;
	}
	
	else if (L < 300)		// ADJUST RIGHT 
	{
		while (getEcho_left() < 400)
		{
		GPIOB->CRH = TURN_RIGHT;
		delay (1000000);
		GPIOB->CRH = STOP;
		target();

		}
	}

	else 
	{
		int a = getEcho_front();
		int b = getEcho_left();
		int c = getEcho_right();
		print(a);
		commandToLCD(LCD_LN2);
		print (b);
		stringInput("   ");
		print(c);
		commandToLCD(LCD_CLR);
	}
}
}





