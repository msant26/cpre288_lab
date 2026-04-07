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
        lcd_printf("Triggering");
        timer_waitMillis(10);
        ping_trigger();
        lcd_printf("Waiting for ISR");

        int timeout = 0;
        int angle;
        int i;

        while (!done) {}

        for (i=0; i<3; i++){
            if (i == 0){
                angle = 90;
                servo_move(angle);
                sprintf(lcd_buffer, "Angle: %d", angle);
                timer_waitMicros(1000000);  // 1 second
            }else if (i == 1){
                angle = 30;
                servo_move(angle);
                sprintf(lcd_buffer, "Angle: %d", angle);
                timer_waitMicros(1000000);  // 1 second
            }else if (i == 2){
                angle = 150;
                servo_move(angle);
                sprintf(lcd_buffer, "Angle: %d", angle);
                timer_waitMicros(1000000);  // 1 second
            }else{
                angle = 90;
                servo_move(angle);
                sprintf(lcd_buffer, "Angle: %d", angle);
                timer_waitMicros(1000000);  // 1 second
            }

            lcd_printf(lcd_buffer);
        }
        

        

        done = 0;

        // Optional: delay before next measurement
        timer_waitMicros(60000);  // 60 ms
    }
}
