/*
 * car.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Dell
 */

#ifndef CAR_CAR_H_
#define CAR_CAR_H_

#include "../../Common/std_types.h"
#include "../../common/bit_math.h"

typedef struct{
	u8 gpio;
	u8 pin[4];

}motor_t;


Std_ReturnType motor_init(motor_t *motor);
Std_ReturnType motor_forward(motor_t *motor);
Std_ReturnType motor_backword(motor_t *motor);
Std_ReturnType motor_left(motor_t *motor);
Std_ReturnType motor_right(motor_t *motor);
Std_ReturnType motor_stop(motor_t *motor);


#endif /* CAR_CAR_H_ */
