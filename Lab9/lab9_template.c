/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

    char lcd_buffer[32];

    while (1)
    {
        lcd_printf("Triggering");
        timer_waitMillis(10);
        ping_trigger();
        lcd_printf("Waiting for ISR");

        int timeout = 0;

        while (!done) {}

        sprintf(lcd_buffer, "Pulse:%lu Ovf:%s", pulse_width, overflow ? "YES" : "NO");

        lcd_printf(lcd_buffer);

        done = 0;

        // Optional: delay before next measurement
        timer_waitMicros(60000);  // 60 ms
    }
}
