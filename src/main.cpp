#include "project.h"


int main(void)
{
  timer1_init();
  i2c_init();
  lcd_init();
  lcd_set_cursor(0, 0);
  lcd_print("I2C LCD");
  lcd_set_cursor(1, 0);
  lcd_print("ATMEGA2560");
}


