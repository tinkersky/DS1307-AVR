#include "avr/io.h"
#include "avr/pgmspace.h"
#include "util/delay.h"

#include "rtc.h"
#include "i2c.h"

uint8_t dayofweek;

// initialize DS1307
void rtc_init() {
	i2c_init();
	_delay_us(10);
}

// transform decimal value to bcd
uint8_t dec2bcd(uint8_t val) {
	return val + 6 * (val / 10);
}

// transform bcd value to deciaml
static uint8_t bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}

// set date
uint8_t rtc_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
	i2c_start_wait(RTC_ADDRESS | I2C_WRITE);
	i2c_write(0x00);//stop oscillator
	i2c_write(dec2bcd(second));
	i2c_write(dec2bcd(minute));
	i2c_write(dec2bcd(hour));
	i2c_write(dec2bcd(dayofweek));
	i2c_write(dec2bcd(day));
	i2c_write(dec2bcd(month));
	i2c_write(dec2bcd(year));
	i2c_stop();
	return 1;
}

/*
 * get date
 */
void rtc_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second) {
	i2c_start_wait(RTC_ADDRESS | I2C_WRITE);
	i2c_write(0x00);//start from address 0x00
	i2c_stop();

	i2c_rep_start(RTC_ADDRESS | I2C_READ);
	*second = bcd2dec(i2c_readAck() & 0x7F);
	*minute = bcd2dec(i2c_readAck());
	*hour = bcd2dec(i2c_readAck());
	i2c_readAck();
	*day = bcd2dec(i2c_readAck());
	*month = bcd2dec(i2c_readAck());
	*year = bcd2dec(i2c_readNak());
	i2c_stop();
}
