#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t timer_done;  //Variable to indicate whether the counter has completed the counting process

//Bare-metal definition of registers of timers, Here Timer 1 is being used
#define tccr1a (*(volatile uint16_t*)0x80)
#define tccr1b (*(volatile uint16_t*)0x81)
#define timsk1 (*(volatile uint16_t*)0x6f)
#define tcnt1  (*(volatile uint16_t*)0x84)
#define tifr1  (*(volatile uint16_t*)0x36)


#define tov1    0  //Timer 1 Overflow flag
#define toie1   0  //Timer 1 interrupt enable
#define cs10    0  //clock select bit 0

#define CPU_HZ 16000000UL  //Clock frequency
#define divider (CPU_HZ / 1000000UL) 


void timer1_init(void) {
    tccr1a = 0;      //To make compare output mode as normal port operation
    tccr1b = 0;      //COunter is fully disabled and the waveform generation mode is normal
    timsk1 = 0;      //No interrupt enabled to avoid race conditions
    timer_done = 0;

}

ISR(TIMER1_OVF_vect) {
    timer_done = 1;
}

void delay_micro(uint16_t micro) {
    uint16_t ticks = micro * divider;

    // Load the counter with the desired ticks value to generate delay
    tcnt1 = 65536 - ticks;

    timer_done = 0;

    tifr1 |= (1 << tov1);      // clear overflow flag
    timsk1 |= (1 << toie1);    // enable overflow interrupt

    sei();           // enable global interrupts

    tccr1b |= (1 << cs10);     // Start the timer

    while (!timer_done);      // wait till counter counts

    tccr1b = 0;               // stop timer
    timsk1 &= ~(1 << toie1);  // disable overflow interrupt
}

void delay_ms(uint16_t ms)
{
    while (ms--) {
        delay_micro(1000);
    }
}

