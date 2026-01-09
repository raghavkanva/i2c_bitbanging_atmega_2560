
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

void timer1_init(void);                 // initialize the timer
void delay_micro(uint16_t micro);       // delay in microseconds
void delay_ms(uint16_t ms);             //delay in milliseconds

#ifdef __cplusplus
}
#endif