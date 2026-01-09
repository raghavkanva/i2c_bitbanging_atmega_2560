#include "pcf8574.h"

void write_byte_pcf8574(uint8_t data)
{
    start();                  //Start the I2C bus
    write_byte(LCD_ADDR_W);   //Send the address of the slave
    write_byte(data);         //Send the data
    stop();                   //Stop  the I2C bus
}