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

    int pingData, irData, degree, start, end, i, index, irTotal, pingTotal;
    double irDataCM;

    int byte, objNum, length, onObj;
    float data, initialData;

    int irDataArr [180];
    int pingDataArr [180];

    struct Object curr;


    // oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    // oi_init(sensor_data); // do this only once at start of main()

    cyBOT_Scan_t *scan_data = calloc(1, sizeof(cyBOT_Scan_t));

    timer_init();
    lcd_init();
    cyBot_uart_init();
    cyBOT_init_Scan(0b0111);

    // cyBOT_SERVO_cal();

    right_calibration_value = 285250;
    left_calibration_value = 1277500;

    curr.angleF = 0;
    curr.angleL = 0;
    curr.data = 0;
    curr.radial = 0;
    curr.width = 180;

    cyBOT_Scan(degree, scan_data);
    initialData = scan_data->sound_dist;

    start = 0;
    end = 180;
    degree = start;
    i = 0;
    objNum = 0;
    onObj = 0;
    while(degree < end){
        cyBOT_Scan(degree, scan_data);

        pingData = scan_data->sound_dist;
        irData = scan_data->IR_raw_val;

        if (irData > 750 && !onObj){
            onObj = 1;
            curr.number = objNum;
            curr.angleF = degree;
            curr.data = irData;
            lcd_printf("Object Found");
        }

        //if(onObj && !((data < curr.data + 5) && (data > curr.data - 5))){
        if(onObj && data <= 750){
            onObj = 0;
            curr.angleL = degree;
            curr.radial = (curr.angleL + curr.angleF)/2;
            curr.width = curr.angleL - curr.angleF;

            char buffer[65];
            sprintf(buffer, "Object %d: Angle=%d deg, Dist=%.2f cm, Width=%d deg\r\n",
                    objNum, curr.radial, curr.data, curr.width);

            length = sizeof(buffer) / sizeof(buffer[0]);

            for (i=0;i<length;i++){
                cyBot_sendByte(buffer[i]);
            }

            lcd_printf("Object Lost");
            objNum++;
        }

        irDataCM = 1752 * exp(-0.00843 * irData);

        lcd_printf("IR Value %lf", irDataCM);

        pingDataArr[i] = pingData;
        irDataArr[i] = irData;

        i++;
        degree++;
    }


    // oi_free(sensor_data); // do this once at end of main()
    return 0;
}




