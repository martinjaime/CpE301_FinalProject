#TITLE: Compass Read and Publish


###GOAL:

- Read HMC5883L compass sensor with Atmega328P over I2C. 
	+ read x axis magnitude in gauss
	+ read y axis magnitude in gauss
	+ read z axis magnitude in gauss
	+ calculate total magnitude using pythagoean theorem in R3. 
- Send data to ESP8266 over UART. 
- Publish data 	on a webserver

###DELIVERABLES: 

The final deliverable is a device that will capture magnetic 
field data and publish it to a webserver for viewing on a website. 

###LITERATURE SURVEY:

Mobile devices, and vehicles such as robots often need to be aware of their orientation. One way to measure it, is by measuring the magnetic field acting on the robot. The HMC5883L is one sensor that can accomplish this task. It is often also necessary to gather data of such sensors and publish it for other other services or entities to read and process. For this task, the ESP8266 Wi-Fi module will be used. 

All devices will be running at 3.3 V with the Wi-Fi module consuming the most power drawing up to 250 mA. This means the system can be powered by a small 3.7 V battery like [this one](https://www.adafruit.com/product/328).

###COMPONENTS:

Hardware:
- Atmega328P
- HMC5883L
- ESP8266 
- Jumper wires
- Resistors
- Breadboard
- Usb micro cables
- FTDI adapter

Protocols:
- I2C
- UART

###SCHEMATICS: (exception - include image)

![Schematic](/Schematics/schematic.png)

###INITIAL PCB*: (exception - include image)
All layers:
![All layers of PCB](/Schematics/PCB.png)

###IMPLEMENTATION:

* Atmega328P connected over I2C to the compass
* Atmega328P connected over UART to the Wi-Fi module. 
* The compass continuously refreshes the data stored on its registers. 
* The MCU will read the data and pass it on to the Wi-Fi module.
* The Wi-Fi module will then publish this data on a web server.
* The data will consist of the magnitude of the magnetic fileld acting on the sensor on three axis. 

I am still unsure about the web service I will be using. 

###SNAPSHOTS/SCREENSHOTS*: (only links - do not embed images or videos in the document)
Show snapshots/video of component implementation.
Show snapshots/video of demo (IOT/BLE/VISUALIZATION).

###CODE: (with comments) [*final code]
Only [main.c](PublishCompass/PublishCompass/main.c) :
```C

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
```

###REFERENCE:
Ho-Duck Kim, Sang-Wook Seo, In-hun Jang and Kwee-Bo Sim, "SLAM of mobile robot in the indoor environment with Digital Magnetic Compass and Ultrasonic Sensors," Control, Automation and Systems, 2007. ICCAS '07. International Conference on, Seoul, 2007, pp. 87-90.
doi: 10.1109/ICCAS.2007.4406885

**PS: * - can be omitted in the Pre-Final Report.**
