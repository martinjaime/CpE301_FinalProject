/*
 * USART header file for Publish compass project
 */

#ifndef UART0_H
#define UART0_H 

#ifndef F_CPU
#define  F_CPU 8000000UL
#endif

#define BAUDRATE	9600
#define ASYNCH_NORM_PRESCALER (F_CPU/16/BAUDRATE - 1)
// 
// int USART0_sendChar(char, FILE*);	// Send character on USART0
// void usart0_init (void);			// Initialize USART0

int USART0_sendChar(char data, FILE *stream)
/*
 * Procedure to send a single character over USART0. If character is linefeed, reset 
 * line. 
 * Assumes ASCII code. 
 */ 
{
	if(data == '\n')
	{
		while(! (UCSR0A & (1<<UDRE0)) );
		UDR0 = '\r';
	}
	while(! (UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
	return 0;
}

void USART0_init (void)
/*
 * Procedure to initialize USART0 asynchronous with enabled RX/TX, 8 bit data,
 * no parity, and 1 stop bit. 
*/
{
	UCSR0B = (1<<TXEN0)  | (1<<RXEN0);	// enable transmit/receive
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);	// asynchronous, 8N1
	UBRR0L = ASYNCH_NORM_PRESCALER;		// To set 9600 baud rate with 8MHz clock
}

// reset stream pointer
//FILE USART0_stream = FDEV_SETUP_STREAM(USART0_sendChar, NULL, _FDEV_SETUP_WRITE);
#endif // UART0_H