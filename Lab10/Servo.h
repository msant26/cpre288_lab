/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */
#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

extern volatile uint32_t pulse_width;
extern volatile uint8_t done;
extern volatile uint8_t overflow;
extern volatile uint32_t interrupt_cnt;

/**
 * Initialize ping sensor. Uses PB3 and Timer 3B
 */
void ping_init (void);

/**
 * @brief Trigger the ping sensor
 */
void ping_trigger (void);

/**
 * @brief Timer3B ping ISR
 */
void TIMER3B_Handler(void);

/**
 * @brief Calculate the distance in cm
 *
 * @return Distance in cm
 */
float ping_getDistance (void);

#endif /* SERVO_H_ */
