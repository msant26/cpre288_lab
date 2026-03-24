/*
 * movement.c
 *
 *  Created on: March 24, 2026
 *      Author: msant & owenf718
 */
#include <adc.h>

void adc_init(){


}

uint16_t adc_read(){

    uint16_t result;

    ADC0_PSSI_R = 0x08;

    while((ADC0_RIS_R & 0x08) == 0);

    adc_value = ADC0_SSFIFO3_R & 0xFFF;

    ADC0_ISC_R = 0x08;

    return result;

}

}

