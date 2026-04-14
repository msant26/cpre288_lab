/**
 * Driver for ping sensor
 * @file ping.c
 * @author
*/

#include <Servo.h>
#include "Timer.h"

// Global shared variables
// Use extern declarations in the header file

uint32_t initPos90;

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

    // **CHECK: configure periodic, and PWM
    TIMER1_TBMR_R = 0x0A;

    // 8bit prescaler for 24bit timer *
    TIMER1_TBPR_R = 0x04;
    TIMER1_TBILR_R = 0xE200;

    initPos90 = 320000 - 24000;

    // Loads match register
    TIMER1_TBMATCHR_R |= (initPos90 & 0xFFFF);
    TIMER1_TBPMR_R |= (initPos90 >> 16);

    // turn on timer
    TIMER1_CTL_R |= 0x100;
}

void servo_move(uint16_t degrees){

    float pulse_width = 0.0;

    // Map angle to pulse width
    pulse_width = 1.1 + (degrees * (0.8 / 180.0));

    // convert ms to clock cycles
    int match_value = (int)(320000 - (pulse_width * 16000));

    TIMER1_TBMATCHR_R = match_value; 
}
