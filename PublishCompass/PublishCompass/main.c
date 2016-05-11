/*
 * PublishCompass.c
 *
 * Created: 4/24/2016 18:19:25
 * Author : Martin
 */ 

#define F_CPU       8000000UL   // set CPU frequency
#define BAUDRATE    9600        // set baudrate

#include <avr/io.h>
#include <util/delay.h>     // delay subroutines
#include <stdio.h>          // standard input output
#include <stdlib.h>         // standard API
#include <math.h>           // for arctan2

#include "i2c.h"
#include "HMC5883L.h"       // For compass module
#include "uart.h"

double calcDirection(double, double);
double map(double, double, double, double, double);

//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART0_sendChar, USART0_ReceiveChar, _FDEV_SETUP_RW);

int main(void)
{
    int16_t values[3]; // array for holding axes values.
    double  direction; // direction of sum of vectors on a plane.

    // Reassign standard input/output
    stdin = stdout = &usart0_str;

    USART0_init();     // Initiate USART0.
    i2c_init();        // Initiate I2C.
    HMC5883L_init();   // Initiate compass.


    // Debugging print out.
    printf("Program start.\n");
    // Main program loop.
    while (1)
    {
        // call procedure to read compass values on all axis.
        readCompass(values);
        // Get direction on the xz-plane
        direction = atan2(values[2], values[0]) * 180 / M_PI;
        // Print compass values on USART0.
        printf("%d\t%d\t%d\t%d\n", values[0], values[1], values[2], (int)direction);
        // Delay since thingspeak will not accept data faster 4 times per minute. 
		// (every 15 seconds. 
        _delay_ms(1000);
    }
}

double map(double x, double in_min, double in_max, double out_min, double out_max)
// modified from source: http://www.avrfreaks.net/forum/mapping-numbers-avr
// by singelen
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}