#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define SCL_CLOCK  100000L

#define I2C_READ    1
#define I2C_WRITE   0

// Initialize the I2C master interface.
void i2c_init(void);

// Terminates the data transfer and releases the I2C bus
void i2c_stop(void);

//Issues a start condition and sends address and transfer direction
unsigned char i2c_start(unsigned char addr);

// Issues a repeated start condition and sends address and transfer direction
unsigned char i2c_rep_start(unsigned char addr);

//Issues a start condition and sends address and transfer direction
void i2c_start_wait(unsigned char addr);

// Send one byte to I2C device
unsigned char i2c_write(unsigned char data);

// read one byte from the I2C device, request more data from device
unsigned char i2c_readAck(void);

// read one byte from the I2C device, read is followed by a stop condition
unsigned char i2c_readNak(void);

#endif /* I2C_H_ */