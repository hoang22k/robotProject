#include "pwm.h"


void pwm_init(void)
{
		TIM1->CR1 |= TIM_CR1_CEN; // Enable Timer1 
		TIM1->CR2 |= TIM_CR2_OIS1; // Output Idle State for Channel 1 OC1=1 when MOE=0 • 
		TIM1->EGR |= TIM_EGR_UG; // Reinitialize the counter  
		TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;       //PWM mode 1, Preload Enable, Fast Enable 
		
		//TIM1->CCMR2 not used for this application  
		TIM1->CCER |= TIM_CCER_CC1E; //Enable CH1 output on PA8 
		TIM1->PSC = 0x095F; //Divide 24 MHz by 2400 , PSC_CLK = 10000 Hz, 1 count = 0.1 ms 
		TIM1->ARR = 100; //  100 counts = 10 ms 
		TIM1->CCR1 = 25; // 10 counts = 1 ms= 10% duty cycle  
		TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI; //Main Output Enable, Force Idle Level First 
		TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable Timer

	
		TIM2->CCR1 |= TIM_CR1_CEN;	
}



void change_pwm (uint16_t a)
{	
	TIM1->CCR1 = a;	
	TIM1->EGR |= TIM_EGR_UG; // Reinitialize the counter  
}

uint16_t read_pot (void)
{
	ADC1->SQR3 = 0x00000002;
	ADC1->CR2 = 0x00000001;
	
	ADC1->SR = ADC1->SR & 0x2;
	
	
	while (ADC1->SR==0x0)
	{
	}
	return ADC1->DR;
	
}