#include <stdint.h>
#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>



void adc_init(void);
void adc_read (void);
void reg_out( uint32_t );
int to_ascii (uint32_t );
int translate (uint32_t, int );
void adc_read_temp (void);

void function(uint32_t);

void print(float);


