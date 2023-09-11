/*
 * car.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Dell
 */

#include "../../MCAL/gpio/gpio.h"
#include "../car/car.h"

Std_ReturnType motor_init(motor_t *motor)
{
	u8 ret=E_OK;
	if(motor != NULL){
MGPIO_SetPinMode(motor->gpio,motor->pin[0],Mode_OUTPUT);
MGPIO_SetPinMode(motor->gpio,motor->pin[1],Mode_OUTPUT);
MGPIO_SetPinMode(motor->gpio,motor->pin[2],Mode_OUTPUT);
MGPIO_SetPinMode(motor->gpio,motor->pin[3],Mode_OUTPUT);
	}
	else{
		ret=E_NOT_OK;
	}
return ret;
}
Std_ReturnType motor_forward(motor_t *motor)
	{
		u8 ret=E_OK;
		if(motor != NULL){

			MGPIO_SetPinValue(motor->gpio,motor->pin[0],VALUE_LOW);
			MGPIO_SetPinValue(motor->gpio,motor->pin[1],VALUE_HIGH);
			MGPIO_SetPinValue(motor->gpio,motor->pin[2],VALUE_LOW);
			MGPIO_SetPinValue(motor->gpio,motor->pin[3],VALUE_HIGH);
		}
		else{
			ret=E_NOT_OK;
		}
	return ret;
	}

Std_ReturnType motor_backword(motor_t *motor)
	{
		u8 ret=E_OK;
		if(motor != NULL){
			MGPIO_SetPinValue(motor->gpio,motor->pin[0],VALUE_HIGH);
			MGPIO_SetPinValue(motor->gpio,motor->pin[1],VALUE_LOW);
			MGPIO_SetPinValue(motor->gpio,motor->pin[2],VALUE_HIGH);
			MGPIO_SetPinValue(motor->gpio,motor->pin[3],VALUE_LOW);
		}
		else{
			ret=E_NOT_OK;
		}
	return ret;
	}

Std_ReturnType motor_left(motor_t *motor)
	{
		u8 ret=E_OK;
		if(motor != NULL){
			MGPIO_SetPinValue(motor->gpio,motor->pin[0],VALUE_LOW);
			MGPIO_SetPinValue(motor->gpio,motor->pin[1],VALUE_LOW);
			MGPIO_SetPinValue(motor->gpio,motor->pin[2],VALUE_HIGH);
			MGPIO_SetPinValue(motor->gpio,motor->pin[3],VALUE_LOW);
		}
		else{
			ret=E_NOT_OK;
		}
	return ret;
	}

Std_ReturnType motor_right(motor_t *motor)
	{
		u8 ret=E_OK;
		if(motor != NULL){
			MGPIO_SetPinValue(motor->gpio,motor->pin[0],VALUE_LOW);
			MGPIO_SetPinValue(motor->gpio,motor->pin[1],VALUE_HIGH);
			MGPIO_SetPinValue(motor->gpio,motor->pin[2],VALUE_LOW);
			MGPIO_SetPinValue(motor->gpio,motor->pin[3],VALUE_LOW);
		}
		else{
			ret=E_NOT_OK;
		}
	return ret;
	}

Std_ReturnType motor_stop(motor_t *motor){
	u8 ret=E_OK;
	if(motor != NULL){
		MGPIO_SetPinValue(motor->gpio,motor->pin[0],VALUE_LOW);
		MGPIO_SetPinValue(motor->gpio,motor->pin[1],VALUE_LOW);
		MGPIO_SetPinValue(motor->gpio,motor->pin[2],VALUE_LOW);
		MGPIO_SetPinValue(motor->gpio,motor->pin[3],VALUE_LOW);
	}
	else{
		ret=E_NOT_OK;
	}
return ret;

}
