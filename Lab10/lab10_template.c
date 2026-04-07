/**
 * @file lab9_template.c
 * @Author: Michael Santiago
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include <Servo.h>
#include "driverlib/interrupt.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	servo_init();

    char lcd_buffer[32];

    while (1)
    {
        int timeout = 0;
        uint16_t angles[] = {90, 30, 150, 90};
        int i;

        while (!done) {}

        for (i=0; i<4; i++){

            servo_move(angles[i]);
            sprintf(lcd_buffer, "Angle: %d", angles[i]);
            lcd_printf(lcd_buffer);
            timer_waitMicros(1000000);  // 1 second
        }
        
    }
}
