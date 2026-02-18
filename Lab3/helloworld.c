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
int i;

int main(void) {
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()

    cyBOT_Scan_t *scan_data = calloc(1, sizeof(cyBOT_Scan_t));

    lcd_init();

    cyBot_uart_init();
    /*
    byte = cyBot_getByte();

    lcd_printf("%c", byte);

    char buffer[8];
    sprintf(buffer, "Got an %c", byte);

    int length = sizeof(buffer) / sizeof(buffer[0]);

    for (i=0;i<length;i++){
        cyBot_sendByte(buffer[i]);
    }
    */

    cyBOT_init_Scan(0b0111);

    right_calibration_value = 274750;
    left_calibration_value = 1225000;

    int start = 45;
    int end = 135;
    int degree = start;
    double data = getScan->sound_dist
    byte = cyBot_getByte();
    if (byte == 'm') {
        while(degree < end){
            if (degree % 5){
                char buffer[8];
                sprintf(buffer, "%lf", data);

                int length = sizeof(buffer) / sizeof(buffer[0]);

                for (i=0;i<length;i++){
                    cyBot_sendByte(buffer[i]);
                }

            }
            cyBOT_Scan(degree, &scan_data);
            degree++;

        }
    }

    cyBOT_Scan(180, &scan_data);
    // cyBOT_SERVO_cal();

    oi_free(sensor_data); // do this once at end of main()
    return 0;
}
