/// Prints text as a rotating banner
/**
 * This program prints "Microcontrollers are lots of fun!" to the LCD screen
 * in a rotating banner manner
 * @author Michael Santiago
 * @date 01/27/2026
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"

int byte;

int main(void) {
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()

    lcd_init();

    cyBot_uart_init();
    byte = cyBot_getByte();

    lcd_printf("%c", byte);

    char buffer[50];

    sprintf(buffer, "Got an %c", byte);

    for (int i=0;i<buffer.length;i++){
        cyBot_sendByte(buffer.length[i]);
    }

    


    oi_free(sensor_data); // do this once at end of main()
    return 0;
}
