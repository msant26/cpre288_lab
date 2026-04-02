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


int targetAngle;
int targetDist = 1000;
double distMM;


int main(void) {

    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()

    while(targetDist > 15){
        scanForThinnest(&targetAngle, &targetDist);

    while(targetDist != 10){
        distMM = (double) targetDist * 10.0;
        if(targetAngle > 90){
            turn_left(sensor_data, targetAngle - 90);
        }
        else if(targetAngle < 90){
            turn_right(sensor_data, 90 - targetAngle);
        }

        if (!sensor_data -> bumpLeft && !sensor_data -> bumpRight && distance < target){
            move_forward(sensor_data, distMM - 100.0);
            continue;
        }
        collision_detector(sensor_data, distMM);
    }
    oi_free(sensor_data); // do this once at end of main()
    return 0;
}




