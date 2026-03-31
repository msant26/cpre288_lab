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

#include <adc.h>
#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include <math.h>

int main(void) {

    lcd_init();
    timer_init();
    adc_init();

    cyBOT_Scan_t *scan_data = calloc(1, sizeof(cyBOT_Scan_t));
    cyBOT_init_Scan(0b0111);


    right_calibration_value = 285250;
    left_calibration_value = 1277500;


    int start = 90;
    int degree = start;

    double samples = 0;
    double result = 0;
    double dist = 0;
    int i=0;

    cyBOT_Scan(degree, scan_data);
    while(1){

        cyBOT_Scan(degree, scan_data);



        for (i=0; i<16; i++){
            uint16_t value = adc_read();
            dist = 1.56e7 * pow(value, -1.92);
            samples += dist;
        }
        result = samples / 16;
        samples = 0;

        lcd_printf("Distance: %.2lf", result);


    }


}
