/*
 * buttoon.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Dell
 */

#include"button.h"


Std_ReturnType button_init(button_t *button){
	u8 ret=E_OK;
	if(NULL != button){
	MGPIO_SetPinMode(button->button.port ,button->button.line ,Mode_INPUT);
	MGPIO_SetPinPUPDR(button->button.port,button->button.line,button->pupdr);
	port_selection_configure(&(button->button));
	ISR_function(&(button->button));
	configure_triger(&(button->button));
	}
	else{
		ret=E_NOT_OK;
	}
	return ret;
}
Std_ReturnType button_enable(button_t *button){
	u8 ret=E_OK;
	if(NULL != button){
	enable_external_int(&(button->button));
	enable_nvicID(10);
	}
	 else{
			ret=E_NOT_OK;
		}
		return ret;
}
Std_ReturnType button_disable(button_t *button){
	u8 ret=E_OK;
	if(NULL != button){
	disable_external_int(&(button->button));
	disable_nvicID(10);
	}
	 else{
			ret=E_NOT_OK;
		}
		return ret;
}

