#ifndef ESP8266_H
#define ESP8266_H

// Common responses
#define OK "OK"
#define GOT_IP	"WIFI GOT IP"
// Common commands
#define AT		"AT\n"
#define RESET	"AT+RST\n"

#include "uart.h"

int8_t ESP8266_receive(char *response/*, char *badResponse*/)
// check if response string is received and return 1. Otherwise, return 0.
// https://github.com/mattcallow/esp8266/blob/master/esp8266.ino
{
	uint16_t maxTry = 0 - 1;	// get max value of uint16_t;
	char ch;
	uint16_t i = 0;
// 	uint16_t j = 0; // index for bad response. 
	uint32_t ok_length = strlen(response);
// 	uint32_t nok_length = strlen(badResponse);
	while(--maxTry > 0)
	{
		
		ch = USART0_ReceiveChar(NULL);
		if (ch == response[i])
		{
			if (++i == ok_length)
			{
				return 1; // matched response
			}
		}
// 		else if (ch == badResponse[j])
// 		{
// 			if (++j == nok_length)
// 				return 0;	// matched badResponse.
// 		}
	}
	return 0;
}

int8_t ESP8266_command(char *command, char *response)
{
	printf(command);
	if (ESP8266_receive(response))
		return 1;
	else
		return 0;
}

void ESP8266_init()
{
	ESP8266_command(RESET, OK);
	_delay_ms(100);
	ESP8266_command("AT+CWJAP=\"martinCpE301_spot\",\"S2016CpE\"\n", GOT_IP);
}

#endif