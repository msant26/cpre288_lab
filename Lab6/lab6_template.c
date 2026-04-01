/**
 * lab6_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
*/

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart.h"

// Uncomment or add any include directives that are needed
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"


#warning "Possible unimplemented functions"
#define REPLACEME 0


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	cyBot_uart_init_clean();
	uart_init();
	// cyBOT_init_Scan();

	// YOUR CODE HERE

	char buffer[25];
    int count = 0;
    char c = 'a';

    uart_sendStr("Enter g to begin");
    uart_sendChar('\r');
    uart_sendChar('\n');
    c = uart_receive();
    if(c == 'g'){
        while(1){
            c = uart_receive_nonblocking();
            if(c == 's'){
                break;
            }

            uart_sendStr("Program Running (Press s to stop)");
            uart_sendChar('\r');
            uart_sendChar('\n');
        }
        uart_sendStr("Program Terminated");
    }
}

