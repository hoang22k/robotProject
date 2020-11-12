#include <stdint.h>
#include "clocks.h"
#include "gpio.h"
#include "LCD.h"
#include "adc.h"
#include "pwm.h"
#include "ultrasonic_sensor.h"
#include "line_follower.h"
#include "heat_sensor.h"



int main()
{
		clockInit();
		subsystemInit();
		LCD_Init();
		pwm_init();
		adc_init();
		LineFollowerInit();


while(1)
{
		LED_off();
		navigate();

}
return 0;
}