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
#include "helloworld.h"





int main(void) {

    int byte, objNum, start, end, degree, onObj;
    float data, initialData;

    struct Object thinnest;
    struct Object curr;

    //oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    //oi_init(sensor_data); // do this only once at start of main()

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

    start = 0;
    end = 180;
    degree = start;
    onObj = 0;
    objNum = 0;

  // while(byte != 'm'){
  //      byte = cyBot_getByte();
   //}

    byte = cyBot_getByte();
    if (byte == 'm') {
        thinnest.radial = 180;
        thinnest.angleF = 0;
        thinnest.angleL = 0;
        thinnest.data = 0;
        curr.width = 180;

        curr.radial = 0;
        curr.angleF = 0;
        curr.angleL = 0;
        curr.data = 0;
        curr.radial = 0;
        curr.width = 180;

        cyBOT_Scan(degree, scan_data);
        initialData = scan_data->sound_dist;
        while(degree < end){
            cyBOT_Scan(degree, scan_data);
            data = scan_data->sound_dist;

            if (data < 50 && !onObj){
                onObj = 1;
                curr.number = objNum;
                curr.angleF = degree;
                curr.data = data;
                lcd_printf("Object Found");
            }

            //if(onObj && !((data < curr.data + 5) && (data > curr.data - 5))){
            if(onObj && data >= 50){
                onObj = 0;
                curr.angleL = degree;
                curr.radial = (curr.angleL + curr.angleF)/2;
                curr.width = curr.angleL - curr.angleF;
                if(curr.width <= thinnest.width){
                    thinnest = curr;
                    lcd_printf("New Thinnest Object");
                }
                lcd_printf("Object Lost");
                objNum++;
            }
            degree+=2;

        }
    }

    lcd_printf("Thinnest Object at: %d degrees", thinnest.radial);

    cyBOT_Scan(thinnest.radial, scan_data);
    // cyBOT_SERVO_cal();

    //oi_free(sensor_data); // do this once at end of main()
    return 0;
}




