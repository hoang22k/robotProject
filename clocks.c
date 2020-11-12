#include "stm32f10x.h"
#include "clocks.h"
 
 void clockInit()
 {
	 RCC->CFGR= 0x00050002;
	 RCC->CR=0x01010081;
 }
 
 void subsystemInit()
 {
	
	 RCC->APB2ENR|= 0x0000001C \
									|RCC_APB2ENR_AFIOEN \
									|RCC_APB2ENR_IOPAEN \
									|RCC_APB2ENR_TIM1EN \
									|RCC_APB2ENR_IOPCEN
									|RCC_APB2ENR_USART1EN
									|RCC_APB2ENR_IOPBEN; // port a - bit 2; b-bit3; c-bit4
	
	GPIOA->CRH=0x4443333A;	// PWM - PA 8; LED, PA 9-12
	GPIOB->CRL=0x44344433;	// RS - PB0; RW - PB 5; E - PB1 // Changing motor pin to PB6&7
	GPIOC->CRL=0x33333333;	// DB 0 to 7
	GPIOB->CRH=0x33444333;	//  Ultrasonic: PIN 10-13
													// 	Modifying PIN 14 and 15 to output as trigger
													// 	Motors: Pin 8 - 9
 }
 

 
 
 
 
