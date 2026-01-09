#ifdef __cplusplus
extern "C" {
#endif

#include<stdint.h>
#include<stdbool.h>
#include "timer.h"


//Definition of the port registers
#define OUTC (*(volatile uint8_t*)0x28) //PINC  – Port C Output Register
#define DC   (*(volatile uint8_t*)0x27) //DDRC  – Port C Data Direction Register
#define INC  (*(volatile uint8_t*)0x26) //PORTC – Port C Input Register

#define SDA 0  //Serial Data
#define SCL 1  //Serial Clock

//To drive the SDA pin low
void sda_low(void);

//To release the SDA pin
void sda_high(void);

//To drive the SCL pin low
void scl_low(void);

//To release the SCL pin
void scl_high(void);

//To wait till SCL pin is High
void wait_scl_high(void);

//To write bit in I2C
void write_bit(bool input);

//To read bit in I2C
bool read_bit(void);

//To start the I2C
void start(void);

//To stop the I2C
void stop(void);

//To Write the data in bytes
bool write_byte(uint8_t data);

//To read the data in bytes
uint8_t read_byte(bool ack);

//Initialise the I2C bus
void i2c_init(void);

#ifdef __cplusplus
}
#endif