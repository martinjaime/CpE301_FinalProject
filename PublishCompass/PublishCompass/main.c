/*
 * PublishCompass.c
 *
 * Created: 4/24/2016 18:19:25
 * Author : Martin
 */ 

#define F_CPU	8000000UL
#define BAUD	9600

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "i2c.h"
#include "HMC5883L.h"
#include "uart.h"

//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART0_sendChar, NULL, _FDEV_SETUP_RW);

int main(void)
{
	uint16_t values[3];
	float  direction;
	uint32_t magnitude;
	
	stdout = &usart0_str;
	
	USART0_init();
	i2c_init();
	HMC5883L_init();

	printf("Hello world!\n");
	_delay_ms(200); // Wait for compass to initiate
    while (1)
    {
		//printf("45 50 20 45\n");
		readCompass(values);
		magnitude = (uint32_t)sqrt(values[0]*values[0] + values[1]*values[1] + values[2]*values[2]);
		direction = (float)atan2(values[1], values[0]); // calculate direction in radians
		direction = direction * 180 / M_PI;
// 		printf("<x, y, z> = %5.d\t%5.d\t%5.d\n", values[0], values[1], values[2]);
		printf("%d %d %d %d\n", values[0], values[1], values[2], (int)direction);
		_delay_ms(200);
    }
}

