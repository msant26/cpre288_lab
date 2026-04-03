///////////////////////////////////////////////////////////////////////
// Name: Simple-CyBot-echo.c                                         //
// Author: Phillip Jones (phjones@iastate.edu)                       //
// Date: 09/26/2023                                                  //
// Description: Simple Cybot program that is an Echo'ish program for //
//              communicating with the Starter Client Socket code.   //
///////////////////////////////////////////////////////////////////////

#include <lab7main.h>
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <math.h>
#include "uart.h"
#include "functions.h"

int main (void) {

    timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called
                  // and enables time functions (e.g. timer_waitMillis)
    lcd_init();   // Initialize the the LCD screen.  This also clears the screen.
    cyBot_uart_init();  // Initialize UART

    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()


    char my_data;       // Variable to get bytes from Client
    int run = 1;

    // Write to LCD so that we know the program is running
    lcd_printf("Running");

    while(run)
    {
        my_data = cyBot_getByte(); // Get first byte of the command from the Client

        if(my_data == '\n')
        {
            continue; // skip newline
        }

        switch(my_data) {
            case 'w':
                oi_setWheels(50, 50);
                break;
            case 's':
                oi_setWheels(-50, -50);
                break;
            case 'a':
                oi_setWheels(50, -50);
                break;
            case 'd':
                oi_setWheels(-50, 50);
                break;
            case 'e':
                oi_setWheels(0, 0);
                break;
            case 'q':
                oi_setWheels(0, 0);
                run = 0;
                lcd_printf("Terminating");
                break;
            default:
                // Optional: handle unexpected input
                break;
        }

        lcd_printf("Got: %c", my_data);  // Print received command to the LCD screen

        // Send a response to the Client (Starter Client expects the response to end with \n)
        // In this case I am just sending back the first byte of the command received and a '\n'
        cyBot_sendByte(my_data);

    }

    return 0;
    }
