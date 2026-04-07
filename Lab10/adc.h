/*
 * movement.h
 *
 *  Created on: Feb 3, 2026
 *      Author: msant
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

void adc_init();

uint16_t adc_read();

#endif /* ADC_H_ */
