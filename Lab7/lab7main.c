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
#include "uart.h"





int mainaa(void) {

    int  irData, avgIRData, prevAvgIRData, degree, start, end, i, degreeFound, degreeLost, objStart, objEnd, objMid, radWidth;

        int startOBJIRData, length, arrSize;
        double distMM;

        int objNum, onObj, thinnest, targetAngle, targetDist;
        float initialData, data, linWidth, radians;

        char buffer[10];
        char charDegree[10];

        int degreeFoundArr [180];
        int degreeLostArr [180];



        oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
        oi_init(sensor_data); // do this only once at start of main()

        cyBOT_Scan_t *scan_data = calloc(1, sizeof(cyBOT_Scan_t));

        timer_init();
        lcd_init();
        cyBot_uart_init();
        cyBOT_init_Scan(0b0111);
        uart_init();

        // cyBOT_SERVO_cal();

        right_calibration_value = 290500;
        left_calibration_value = 1272250;

        cyBOT_Scan(0, scan_data);

        for(i = 0; i < 4; i++){
            cyBOT_Scan(0, scan_data);
            initialData += scan_data->sound_dist;
            prevAvgIRData += scan_data->IR_raw_val;
        }

        prevAvgIRData = prevAvgIRData / 4;


        if(prevAvgIRData > 5000 || prevAvgIRData < 0){
            prevAvgIRData = 700;
        }


        start = 0;
        end = 180;
        degree = start;
        i = 0;
        objNum = -1;
        onObj = 0;
        irData = 0;

        while(degree < end){

            for(i = 0; i < 4; i++){
                cyBOT_Scan(degree, scan_data);
                irData += scan_data->IR_raw_val;
            }

            avgIRData = irData / 4;

            if(avgIRData > 5000 || avgIRData < 0){
                avgIRData = prevAvgIRData;
            }

            lcd_printf("%d", avgIRData);

            sprintf(buffer, "%d", avgIRData);
            sprintf(charDegree, "%d", degree);

            uart_sendStr("Degree: ");
            uart_sendStr(charDegree);
            uart_sendStr("       IR Value: ");
            uart_sendStr(buffer);
            uart_sendChar('\r');
            uart_sendChar('\n');
            irData = 0;

            if(!onObj && (avgIRData >= prevAvgIRData + 150)){
                onObj = 1;
                objNum++;
                degreeFound = degree;
                degreeFoundArr[objNum] = degreeFound;
                lcd_printf("Found Object %d", objNum);
                uart_sendStr("Start of Obj");
                uart_sendChar('\r');
                uart_sendChar('\n');
                startOBJIRData = avgIRData;
            }

            if(onObj && (avgIRData <= startOBJIRData - 150)){
                onObj = 0;
                degreeLost = degree;
                degreeLostArr[objNum] = degreeLost;
                lcd_printf("Lost Object %d", objNum);
                uart_sendStr("End of Obj");
                uart_sendChar('\r');
                uart_sendChar('\n');
            }

            degree+=2;
        }

        thinnest = 100;
        for(i = 0; i <= objNum; i++){
            objStart = degreeFoundArr[i];
            objEnd = degreeLostArr[i];
            objMid = (objEnd + objStart) / 2;

            radWidth = objEnd - objStart;

            cyBOT_Scan(objMid, scan_data);
            timer_waitMillis(1000);
            cyBOT_Scan(objMid, scan_data);
            data = scan_data->sound_dist;

            radians = radWidth * (M_PI / 180.0f);
            linWidth = 2.0f * data * tanf(radians / 2.0f);

            if(linWidth < thinnest){
                thinnest = linWidth;
                targetAngle = objMid;
                targetDist = data;
            }

            lcd_printf("Object %d \nDistance: %.2fcm\nWidth: %.2fcm", i, data, linWidth);
            timer_waitMillis(2000);
        }

        distMM = (double) targetDist * 10.0;
        if(targetAngle > 90){
            turn_left(sensor_data, targetAngle - 90);
        }
        else if(targetAngle < 90){
            turn_right(sensor_data, 90 - targetAngle);
        }

        move_forward(sensor_data, distMM - 100.0);

    oi_free(sensor_data); // do this once at end of main()
    return 0;
}




