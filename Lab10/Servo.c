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

}

void servo_move(uint16_t degrees){

    float pulse_width = 0.0;

    // Map angle to pulse width
    pulse_width = 1.0 + (degrees/180.0);

    // convert ms to clock cycles
    int match_value = 320000 - (pulse_width * 16000);

    TIMER1_TBMATCHR_R = match_value; 
}
