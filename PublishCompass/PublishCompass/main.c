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
#include "i2c.h"
#include "HMC5883L.h"
#include "uart.h"

//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART0_sendChar, NULL, _FDEV_SETUP_RW);

int main(void)
{
	uint16_t values[3];
	int16_t count = 0;
	stdout = &usart0_str;
	USART0_init();
	i2c_init();
	
	HMC5883L_init();
	_delay_ms(100); // Wait for compass to initiate
	printf("hello world!\n");
	printf("F_CPU: %ul\n", F_CPU);
    while (1)
    {
 		//i2c_read_byte(0x3C, 0x03, &x_gaussLSB);
 		//i2c_read_byte(0x3C, 0x04, &x_gaussMSB);
 		//x = (x_gaussMSB<<8) | x_gaussLSB;
		readCompass(values);
		//printf("xMSB: %u | xLSB: %u\n", x_gaussMSB, x_gaussLSB);
		printf("X: %d\t|\tread #%u\n", values[0], count++);
		_delay_ms(500);
    }
}

