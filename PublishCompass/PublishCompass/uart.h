/*
 * USART header file for Publish compass project
 */

#ifndef UART0_H
#define UART0_H 

#ifndef F_CPU
#define  F_CPU 8000000UL
#endif

#ifndef BAUDRATE
#define BAUDRATE	115200
#endif
#define ASYNCH_NORM_PRESCALER (F_CPU/16/BAUDRATE - 1)

int USART0_sendChar(char data, FILE *stream)
/*
 * Procedure to send a single character over USART0. If character is linefeed, reset 
 * line. 
 * Assumes ASCII code. 
 */ 
{
	if(data == '\n')
	{
		while(! (UCSR0A & (1<<UDRE0)) ); // Wait until data is ready to send
		UDR0 = '\r'; // send return char.
	}
	while(! (UCSR0A & (1<<UDRE0)) ); // Wait until data is ready to send. 
	UDR0 = data; // send data char. 
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
	UBRR0 = ASYNCH_NORM_PRESCALER;		// To set 9600 baud rate with 8MHz clock
}

int USART0_ReceiveChar(FILE *stream)
{
	uint8_t u8Data;
	// Wait for byte to be received
	while(!(UCSR0A&(1<<RXC0))){};
	u8Data=UDR0;
	// echo input data
	//USART0SendByte(u8Data,stream);
    return u8Data; // Return received data

}

// reset stream pointer
// Uncomment or place in main. Replace NULL argument with a
// procedure to receive a character if expecting input such as USART0_ReceiveChar. 
//FILE USART0_stream = FDEV_SETUP_STREAM(USART0_sendChar, NULL, _FDEV_SETUP_WRITE);
#endif // UART0_H
