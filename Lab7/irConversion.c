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

#include <lab7main.h>
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "movement.h"
#include "cyBot_Scan.h"
#include <math.h>
#include "uart.h"





int nain(void) {

    // oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    // oi_init(sensor_data); // do this only once at start of main()

    int irData;
    float pingData;

    cyBOT_Scan_t *scan_data = calloc(1, sizeof(cyBOT_Scan_t));

    timer_init();
    lcd_init();
    cyBOT_init_Scan(0b0111);
    uart_init();

    // cyBOT_SERVO_cal();

    right_calibration_value = 290500;
    left_calibration_value = 1298500;

    while(1){
        cyBOT_Scan(90, scan_data);
        pingData = scan_data->sound_dist;
        lcd_printf("%f", pingData);
    }


    // oi_free(sensor_data); // do this once at end of main()
    return 0;
}




