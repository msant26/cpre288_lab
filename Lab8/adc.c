/*
 * movement.c
 *
 *  Created on: March 24, 2026
 *      Author: msant & owenf718
 */
#include <adc.h>

void adc_init(){
    // Sets up GPIO
    SYSCTL_RCGCGPIO_R |= 0x02;

    while((SYSCTL_PRGPIO_R & 0x02) == 0){};

    // Enable GPIO functions and analog
    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_DEN_R &= ~0x10;
    GPIO_PORT_B_AMSEL_R |= 0x10;

    // Enables ADC clock
    SYSCTL_RCGCADC_R |= 0x01;

    // Enable status busy wait loop
    while((SYSCTL_PRADC_R & 0x01) == 0){};

    // Disables SS3
    ADC0_ACTSS_R &= ~0x08;

    // Continously samples SS3
    ADC0_EMUX_R |= 0xF000;

    // Selects AIN10
    ADC0_SSMUX3_R = 10;

    ADC0_SSCTL3_R |= 0x06;

    // Enables SS3
    ADC0_ACTSS_R |= 0x08;
}

uint16_t adc_read(){

    uint16_t result;

    ADC0_PSSI_R = 0x08;

    while((ADC0_RIS_R & 0x08) == 0);

    adc_value = ADC0_SSFIFO3_R & 0xFFF;

    ADC0_ISC_R = 0x08;

    return result;

}

