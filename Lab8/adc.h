/*
 * movement.h
 *
 *  Created on: Feb 3, 2026
 *      Author: msant
 */

#ifndef ADC_H_
#define ADC_H_

double move_forward(oi_t *sensor_data, double distance_mm);

double move_backwards(oi_t *sensor_data, double distance_mm);

double turn_right(oi_t *sensor_data, double target_d);

double turn_left(oi_t *sensor_data, double target_d);

void collision_detector(oi_t *sensor_data, double* target);


#endif /* ADC_H_ */
