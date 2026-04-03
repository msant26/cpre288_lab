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
#include "functions.h"





int main(void) {

    int targetAngle = 45;
    float targetDist = 1000;
    double distMM = 200;

    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()

    oi_setWheels(0,0);
    while(distMM > 75){
       scanForThinnest(&targetAngle, &targetDist);

       distMM = (double) targetDist * 10.0;
       if(targetAngle > 90){
            turn_left(sensor_data, targetAngle - 90);
        }
        else if(targetAngle < 90){
            turn_right(sensor_data, 90 - targetAngle);
        }
        while(!sensor_data -> bumpLeft && !sensor_data -> bumpRight && distMM > 75){
            oi_setWheels(50,50);
            oi_update(sensor_data);
            distMM -= sensor_data->distance;
            lcd_printf("Distance Left: %.2f", distMM);
            continue;
        }
        collision_detector(sensor_data);
    }
    oi_free(sensor_data); // do this once at end of main()
    return 0;
}
