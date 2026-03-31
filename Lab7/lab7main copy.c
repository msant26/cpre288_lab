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
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <math.h>





int main(void) {

    int  irData, avgIRData, prevAvgIRData, degree, start, end, i, degreeFound, degreeLost;

    int startOBJIRData, length;

    int objNum, onObj;
    float initialData;

    int degreeFoundArr [180];
    int degreeLostArr [180];

    char buffer[10];




    // oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    // oi_init(sensor_data); // do this only once at start of main()

    cyBOT_Scan_t *scan_data = calloc(1, sizeof(cyBOT_Scan_t));

    timer_init();
    lcd_init();
    cyBot_uart_init();
    cyBOT_init_Scan(0b0111);
    // cyBOT_SERVO_cal();

    right_calibration_value = 217000;
    left_calibration_value = 1183000;

    for(i = 0; i < 3; i++){
        cyBOT_Scan(0, scan_data);
        initialData += scan_data->sound_dist;
        prevAvgIRData += scan_data->IR_raw_val;
    }
    
    prevAvgIRData = prevAvgIRData / 3;

    start = 0;
    end = 180;
    degree = start;
    i = 0;
    objNum = -1;
    onObj = 0;

    while(degree < end){

        for(i = 0; i < 3; i++){
            cyBOT_Scan(degree, scan_data);
            irData += scan_data->IR_raw_val;
        }

        avgIRData = irData / 3;

        if(avgIRData > 5000){
            avgIRData = prevAvgIRData;
        }

        lcd_printf("%d", avgIRData);
        sprintf(buffer, "%d", avgIRData);

        length = sizeof(buffer) / sizeof(buffer[0]);

        for(i = 0; i < length; i++){
            cyBot_sendByte(buffer[i]);
        }

        cyBot_sendByte('\r');
        cyBot_sendByte('\n');

        irData = 0;

        if(!onObj && (avgIRData >= prevAvgIRData + 175)){
            onObj = 1;
            objNum++;
            degreeFound = degree;
            degreeFoundArr[objNum] = degreeFound;
            lcd_printf("Found Object %d", objNum);
            startOBJIRData = avgIRData;
        }

        if(onObj && (avgIRData <= startOBJIRData - 175)){
            onObj = 0;
            degreeLost = degree;
            degreeLostArr[objNum] = degreeLost;
            lcd_printf("Lost Object %d", objNum);
        }

        prevAvgIRData = avgIRData;
        degree+=5;
    }


    // oi_free(sensor_data); // do this once at end of main()
    return 0;
}




