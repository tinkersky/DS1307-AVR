#ifndef RTC_H_
#define RTC_H_

#define RTC_ADDRESS (0x68<<1) //device address

void rtc_init();
uint8_t rtc_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void rtc_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);

#endif /* RTC_H_ */