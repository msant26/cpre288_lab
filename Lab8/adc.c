/*
 * movement.c
 *
 *  Created on: March 24, 2026
 *      Author: msant & owenf718
 */
#include <adc.h>

void adc_init(){
    oi_setWheels(100,100);
    double sum = 0;
    while (sum < distance_mm){
        oi_update(sensor_data);
        sum += sensor_data->distance;
        lcd_printf("%.2lf", sum);

        if(sum >= distance_mm * 0.8){
            oi_setWheels(50,50);
        }
    }
    oi_setWheels(0,0);
    return sum;
}

uint16_t adc_read(){

    uint16_t result;

    ADC0_PSSI_R = 0x08;

    while((ADC0_RIS_R & 0x08) == 0);

    adc_value = ADC0_SSFIF03_R & 0xFFF;

    ADC0_ISC_R = 0x08;

    return result;

}

}

