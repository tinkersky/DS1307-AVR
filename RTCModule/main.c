#define  F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

#include "uart.h"
#include "rtc.h"

int main(void)
{
	UART_Init();
	rtc_init();
	
	uint8_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t second = 0;

	rtc_setdate(20, 04, 28, 05, 59, 55);
	
	while (1)
	{
		//get date
		rtc_getdate(&year, &month, &day, &hour, &minute, &second);

		char buf[50];
		sprintf(buf, "%d/%d/%d %d:%d:%d", year, month, day, hour, minute, second);
		UART_TxString(buf);
		UART_TxString("\r\n");
		_delay_ms(1000);
	}
}

