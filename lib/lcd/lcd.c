#include "lcd.h"

void lcd_init(void)
{
  delay_ms(50);  // As per datasheet, for VCC to rise to 4.5 V, >=40ms delay is needed. (Power Up Delay)

  /*As per the datasheet, delay sequence is required for Busy Flag (BF) to be checked.
    After power-up, the LCD controller's internal clock and state machine are
    not fully stable, so the first commands need delays to make
    sure they are actually recognized. As the controller “wakes up” and its
    clock becomes reliable, the required wait time drops from milliseconds
    to microseconds. These repeated writes with different delay are not
    random but they are a safe synchronization method recommended by the
    datasheet to guarantee the LCD always starts in a
    known state, even with slow power rise or noisy conditions. if all delays are
    kept short, the LCD may not be ready to accept commands yet, so some
    initialization commands are missed, which leads to unpredictable
    display behavior. */

    /*After power up, the LCD does not know about 4-bit mode directly . SO first 8 bit 
      mode should be assumed initially*/


  lcd_write4(0x03, 0);
  delay_ms(5);
  lcd_write4(0x03, 0);
  delay_ms(5);
  lcd_write4(0x03, 0);
  delay_ms(1);

  //Now switch to 4-bit mode
  lcd_write4(0x02, 0);  

  //Before sending this command the mode should be switched to 4-bit. Else Only the command would be corrupted

  lcd_command(0x28);    // 4-bit, 2-line, 5x8
  delay_micro(40);      //Execution time is 39us
  lcd_command(0x0C);    // Display ON
  delay_micro(40);      //Execution time is 39us
  lcd_command(0x01);    // Clear display
  delay_ms(2);          //Execution time is 1.53ms
  lcd_command(0x06);    // Entry mode
  delay_micro(40);      //Execution time is 39us
}

void lcd_command(uint8_t cmd)
{
    lcd_send(cmd, 0);   // RS = 0
}

void lcd_data(uint8_t data)
{
    lcd_send(data, 1);  // RS = 1
}

void lcd_send(uint8_t value, uint8_t rs)
{
    lcd_write4(value >> 4, rs);    // HIGH nibble
    lcd_write4(value & 0x0F, rs);  // LOW nibble
}
void lcd_write4(uint8_t nibble, uint8_t rs)
{
    uint8_t data = 0;

    if (rs) data |= LCD_RS;      // data
    data |= LCD_BL;              // Backlight ON
    data |= (nibble & 0x0F) << 4; // Put nibble on D4–D7 pins

    write_byte_pcf8574(data);
    lcd_pulse_enable(data);
}

void lcd_pulse_enable(uint8_t data)
{
  
    delay_micro(TSU1_US);                //RS/RW setup before Enable High

    write_byte_pcf8574(data | LCD_EN);   // E = 1
    delay_micro(TW_US);                  // Enable pulse width


    write_byte_pcf8574(data & ~LCD_EN);  // E = 0 → LATCH
    delay_micro(TH2_US);                 //Data hold time delay after Enable low

}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_command(addr);
    delay_micro(40);      //Execution time is 39us

}
void lcd_print(char *str)
{
    while (*str)
        lcd_data(*str++);
}

void lcd_print_num(uint8_t d)
{
    
    if (d >= 100) {
        lcd_data((d / 100) + '0');
        d %= 100;
        lcd_data((d / 10) + '0');
        lcd_data((d % 10) + '0');
    }
    else if (d >= 10) {
        lcd_data((d / 10) + '0');
        lcd_data((d % 10) + '0');
    }
    else {
        lcd_data(d + '0');
    }
}
