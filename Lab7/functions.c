

#include "functions.h"

// Make a scan from 0 – 180 (or 360) degrees. Take multiple measurements at each angle in the scan.



void scanForThinnest(int *tA, int* tD){

    int  irData, avgIRData, prevAvgIRData, degree, start, end, i, degreeFound, degreeLost, objStart, objEnd, objMid, radWidth;

        int startOBJIRData, length, arrSize;

        int objNum, onObj, thinnest;
        float initialData, data, linWidth, radians;

        char buffer[10];
        char charDegree[10];

        int degreeFoundArr [180];
        int degreeLostArr [180];





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
                    *tA = objMid;
                    *tD = data;
                }

                lcd_printf("Object %d \nDistance: %.2fcm\nWidth: %.2fcm", i, data, linWidth);
                timer_waitMillis(2000);
            }

}

// Use the IR values to detect the edges of each object, i.e., the angles for the starting and ending edges
int findObjs() {

    return 0;
}

/*
    Make a second scan that points the PING sensor at the midpoint between the edges of an object (i.e.,
    halfway between the angles of the starting edge and ending edge). Then measure the distance to that
    object using the PING sensor. Do this for each object detected in the initial scan.
*/
double findDistance(){

    return 0;
}
