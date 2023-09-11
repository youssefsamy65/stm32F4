/*
 * button.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Dell
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/external_interupt/extenal_int.h"
#include "../../MCAL/nvic/NVIC.h"

#define B_GPIO_PORTA		0
#define B_GPIO_PORTB		1
#define B_GPIO_PORTC		2
#define B_GPIO_PORTD		3
typedef enum{
 NOPUPD,
 PULL_UP,
 PULL_DOUWN
}PUPDR;
typedef struct{
	external_interupt button;
	PUPDR pupdr;
}button_t;

Std_ReturnType button_init(button_t *button);
Std_ReturnType button_enable(button_t *button);
Std_ReturnType button_disable(button_t *button);




#endif /* BUTTON_BUTTON_H_ */
