#include "i2c.h"

void sda_low(void){
  // MAKE THE DIRECTION OF THE PAD IN PORT C AS OUTPUT
  DC |= (1 << SDA);
  
  //DRIVE LOW FOR THE SDA PIN
  OUTC &= ~(1 << SDA);
}

void sda_high(void){
  // MAKE THE DIRECTION OF THE PAD IN PORT C AS INPUT (HIGH - Z)
  DC &= ~(1 << SDA);
}

void scl_low(void){
  // MAKE THE DIRECTION OF THE PAD IN PORT C AS OUTPUT
  DC |= (1 << SCL);
  
  //DRIVE LOW FOR THE SCL PIN
  OUTC &= ~(1 << SCL);
}

void scl_high(void){
  // MAKE THE DIRECTION OF THE PAD IN PORT C AS INPUT (HIGH - Z)
  DC &= ~(1 << SCL);
  
}

void wait_scl_high(void){
  while((INC & (1 << SCL)) == 0);
}

void write_bit(bool input){
  scl_low();
  delay_micro(5);
  //Check if the input is high
  if(input){
    sda_high();
  }

  //Check if the input is low
  else{
    sda_low();
  }

  /* Wait for next half Cycle (~5us in I2C Standard Mode)
    This is the setup time - the time in which the SDA makes the data stable*/
  delay_micro(5); //Setup time

  //Make the SCL high 
  scl_high();

  //Wait till SCL is high  (Clock Stretching Concept)
  wait_scl_high();   

  /* Wait for next half Cycle (~5us in I2C Standard Mode)
    This is the hold time - the time in which the SDA makes the data stable*/
  delay_micro(5); //Hold time
  
  //Drive the SCL low
  scl_low();

}
bool read_bit(void){
  /* First ensure the I²C bus is in the IDLE (released) state.
     In I²C, IDLE means both SCL and SDA are released by all devices
     and therefore can be pulled HIGH by the external pull-up resistors.
     
     Releasing a line means the device drives it to Hi-Z,
     allowing the pull-up to bring it HIGH. */

  // Release SCL so it goes HIGH (start of clock HIGH phase)
  scl_high();

  //Wait till SCL is high in the slave (Clock Stretching Concept)
  wait_scl_high();   
  
/* Wait during SCL HIGH to ensure Minimum clock HIGH time and SDA is fully settled and stable
   before sampling */
  delay_micro(5);

  // Release SDA so the slave can drive the data bit
  sda_high();

  /* Data setup time : Allows SDA to stabilize while SCL is HIGH before sampling. */
  delay_micro(5);

  /* Sample the SDA line while SCL is HIGH.
     According to I²C rules, data is valid only when SCL is HIGH. */
  bool data = ((INC & (1 << SDA)) != 0);

  /* Data hold time:
     SDA must remain stable briefly after sampling while SCL is HIGH. */
  delay_micro(5);

  /* Pull SCL LOW to complete the clock pulse and
     indicate the bit has been sampled. */
  scl_low();

  // Return the sampled data bit
  return data;
}


void start(void){
  /*First ensure the I²C bus is in the IDLE (released) state.
     In I²C, IDLE means both SCL and SDA are released by all devices
     and therefore pulled HIGH by the external pull-up resistors.
     
     Releasing a line means the device drives it to Hi-Z,
     allowing the pull-up to bring it HIGH. */

  //Therefore, release both SDA and SCl pins
  scl_high();

  //Wait till SCL is high  (Clock Stretching Concept)
  wait_scl_high()
  
  //Wait for next half cycle 
  delay_micro(5);

  sda_high();

  //Delay
  delay_micro(5);

  /*Now drive both SDA and SCL pins to low state to actually Start the I2C
    communication process. Because in I2C , Only SDA transitioning from HIGH
     to LOW while SCL is HIGH represents START*/
  
  sda_low();
  
  //Wait for next half cycle 
  delay_micro(5);

  //Prepare for next phase
  scl_low();

  //Delay
  delay_micro(5);
}

void stop(void){
  /* To generate an I²C STOP condition, the master must
     transition the bus from an active state to the IDLE state.

     SDA must transition from LOW to HIGH while SCL is HIGH for a STOP Condition
     
     In I²C, IDLE means both SCL and SDA are released (Hi-Z)
     and pulled HIGH by the external pull-up resistors. */

  /* A STOP condition is defined as:
     SDA transitioning from LOW to HIGH while SCL is HIGH.
     This signals the end of the current I²C transaction
     and releases the bus for other masters or transactions. */

  // Release SCL so it goes HIGH
  scl_high();
  
  /* Wait for SCL to be HIGH and stable.
     This ensures the STOP condition is detected correctly. */
  delay_micro(5);

  // Release SDA to create the LOW → HIGH transition while SCL is HIGH
  sda_high();

  /* Hold time after STOP condition.
     Ensures the bus remains in IDLE state before next operation. */
  delay_micro(5);
}

bool write_byte(uint8_t data){

  //Send the data bit by bit (MSB First)
  for(int index = 7; index >= 0; index--){
    write_bit((data >> index) & 1);
  }

  //Check for the acknowledgement bit
  bool ack = !(read_bit());

  //return
  return ack;
}

uint8_t read_byte(bool ack){
  /* The input is the acknowledgement bit
    It tells the transmitter whether the receiver wants to
    receive the data next (ACK = 0) or
    stop the data transmission (ACK = 1, NACK)*/

  uint8_t data = 0;

  for(int index = 7; index >= 0; index--){
    if(read_bit()){
      data |= (1 << index);
    }
  }
  write_bit(!ack);
  return data;
}

void i2c_init(void){
  /*This is the function to initialise the I2C bus
    We have to make the SDA and SCL pins to Hi-Z state*/

  scl_high();
  sda_high();
}

