#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"

#define LCD_I2C_ADDR   0x27
#define LCD_ADDR_W     (LCD_I2C_ADDR << 1)

#define LCD_RS   (1 << 0)   // P0
#define LCD_EN   (1 << 2)   // P2
#define LCD_BL   (1 << 3)   // P3

#define TSU1_US   1   // RS/RW setup before Enable high
#define TH1_US    1   // RS/RW hold after Enable low
#define TSU2_US   1   // Data setup before Enable low
#define TH2_US    1   // Data hold after Enable high
#define TW_US     1   // Enable pulse width


void lcd_pulse_enable(uint8_t data);
void lcd_write4(uint8_t nibble, uint8_t rs);
void lcd_send(uint8_t value, uint8_t rs);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_init(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(char *str);
void lcd_print_num(uint8_t d);

#ifdef __cplusplus
}
#endif