/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

    done = 0;

    char lcd_buffer[32];  // buffer for LCD output

    while (1)
    {
        // Trigger ultrasonic pulse
        ping_trigger();

        while (!done) {}

        // Prepare display string: pulse width and overflow
        // Format: "Pulse: <ticks> Ovf: YES/NO"
        sprintf(lcd_buffer, "Pulse:%lu Ovf:%s", pulse_width, overflow ? "YES" : "NO");

        // Print to LCD (assumes lcd_print handles full string with line wrap)
        lcd_printf(lcd_buffer);

        // Reset done for next measurement
        done = 0;

        // Optional: delay before next measurement
        timer_waitMicros(60000);  // 60 ms
    }

}
