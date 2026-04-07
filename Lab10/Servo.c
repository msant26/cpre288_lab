/**
 * Driver for ping sensor
 * @file ping.c
 * @author
*/

#include <Servo.h>
#include "Timer.h"

// Global shared variables
// Use extern declarations in the header file

void servo_init(void){

    // enable clock
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x02;

    // clock wait loop
    while((SYSCTL_PRGPIO_R & 0x02) == 0){};
    while((SYSCTL_PRTIMER_R & 0x02) == 0){};

    // ensures timer is disabled
    TIMER1_CTL_R &= ~0x100;

    // enable alternate functions
    GPIO_PORTB_AFSEL_R |= 0x20;

    // enable digital functions
    GPIO_PORTB_DEN_R |= 0x20;

    // select alternate function
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xF00000) | 0x700000;

    // configure 16 Bit mode
    TIMER1_CFG_R = 0x04;

    // **CHECK: configure input edge-time, periodic, and PWM
    TIMER1_TBMR_R = 0x0C;

    // 8bit prescaler for 24bit timer *
    TIMER1_TBPR_R = 0xFF;
    TIMER1_TBILR_R = 0xFFFF;

    // capture both rising and falling
    TIMER1_CTL_R |= 0xC00;

    // turn on timer
    TIMER1_CTL_R |= 0x100;
}

void servo_move(uint16_t degrees){

    float pulse_width = 0.0;

    // Map angle to pulse width
    pulse_width = 1.0 + (degrees/180.0);

    // convert ms to clock cycles
    int match_value = 320000 - (pulse_width * 16000);

    TIMER1_TBMATCHR_R = match_value; 
}
