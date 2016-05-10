/*
 * PublishCompass.c
 *
 * Created: 4/24/2016 18:19:25
 * Author : Martin
 */ 

#define F_CPU		8000000UL
#define BAUDRATE	9600

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "i2c.h"
#include "HMC5883L.h"
#include "uart.h"

double calcDirection(double, double);
double map(double x, double in_min, double in_max, double out_min, double out_max);

//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART0_sendChar, USART0_ReceiveChar, _FDEV_SETUP_RW);

int main(void)
{
	int16_t values[3];
	double  direction;
// 	char buffer[100];
// 	uint32_t magnitude;
	
	stdin = stdout = &usart0_str;
	
	USART0_init();
	i2c_init();
	HMC5883L_init();

	printf("Hello world!\n");
    while (1)
    {
		readCompass(values);
		//magnitude = (uint32_t)sqrt(values[0]*values[0] + values[1]*values[1] + values[2]*values[2]);
		// Get direction on the xz-plane
		direction = atan2(values[2], values[0]) * 180 / M_PI;
		printf("%d\t%d\t%d\t%d\n", values[0], values[1], values[2], (int)direction);
		_delay_ms(900);
    }
}
