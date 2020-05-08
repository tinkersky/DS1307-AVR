/*
 * uart.c
 *
 * Created: 28-03-2020 09:20:30
 *  Author: Chaitali
 */ 

#include <avr/io.h>
#include "uart.h"


void UART_Init(){
	UBRR0L = 103;
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

void UART_TxChar(char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

char UART_RxChar(){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void UART_TxString(char text[]){
	int i=0;
	
	while(i<255){
		if (text[i] == '\0') break;
		UART_TxChar(text[i]);
		i++;
	}
}