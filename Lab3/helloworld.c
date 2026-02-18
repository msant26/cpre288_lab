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
float data;
float initialData;
int start;
int end;
int degree;
int length;

int main(void) {
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

    start = 45;
    end = 135;
    degree = start;


    while(byte != 'm'){
        byte = cyBot_getByte();
    }
    if (byte == 'm') {
        cyBOT_Scan(degree, scan_data);
        initialData = scan_data->sound_dist;
        while(degree < end){
            cyBOT_Scan(degree, scan_data);
            data = scan_data->sound_dist;
            /*
            if (degree % 5 == 0){
                char buffer[30];
                sprintf(buffer, "Angle: %d Ping: %.2f\r\n", degree, data);

                length = strlen(buffer);

                for (i=0;i<length;i++){
                    cyBot_sendByte(buffer[i]);
                }

            }
            */
            if (data ){

            }



            cyBOT_Scan(degree, &scan_data);
            degree++;

        }
    }

    cyBOT_Scan(180, scan_data);
    // cyBOT_SERVO_cal();

    //oi_free(sensor_data); // do this once at end of main()
    return 0;
}



struct Object (int botNumber, int angleFound, int angleLost, float ping){
    int number = botNumber;
    int angleF = angleFound;
    int angleL = angleLost;
    float data = ping;
    int radial = angleLost - angleFound;




}
