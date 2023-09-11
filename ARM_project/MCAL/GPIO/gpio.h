

/*
 * GPIO_Driver.h
 *
 *  Created on: Aug 10, 2023
 *      Author: Adel
 */

#ifndef GPIO_GPIO__H_
#define GPIO_GPIO__H_

#include "../../Common/std_types.h"
#include "../../common/bit_math.h"

/*PORT OPTIONS*/
#define GPIO_PORTA		0
#define GPIO_PORTB		1
#define GPIO_PORTC		2

#define onet      0b0000000000000001 // Bit 0
#define twot      0b0000000000000011 // Bit 1
#define threet    0b0000000000000111 // Bit 2
#define fourt     0b0000000000001111 // Bit 3
#define fivet     0b0000000000011111 // Bit 4
#define sixt      0b0000000000111111 // Bit 5
#define sevent    0b0000000001111111 // Bit 6
#define eightt    0b0000000011111111 // Bit 7
#define ninet     0b0000000111111111 // Bit 8
#define tent      0b0000001111111111 // Bit 9
#define elevent   0b0000011111111111 // Bit 10
#define twelvet   0b0000111111111111 // Bit 11
#define thirteent 0b0001111111111111 // Bit 12
#define fourteent 0b0011111111111111 // Bit 13
#define fifteent  0b0111111111111111 // Bit 14
#define sixteent  0b1111111111111111 // Bit 15


/************************************************GPIOx_PINS************************************************************************/
#define 		PIN0 					 0
#define 		PIN1 					 1
#define 		PIN2 					 2
#define 		PIN3 					 3
#define 		PIN4 					 4
#define 		PIN5 					 5
#define 		PIN6 					 6
#define 		PIN7 					 7
#define 		PIN8 					 8
#define 		PIN9 					 9
#define 		PIN10 					 10
#define 		PIN11 					 11
#define 		PIN12 					 12
#define 		PIN13 					 13
#define 		PIN14 					 14
#define 		PIN15 					 15

/* alternate function*/
#define AF0 0
#define AF1 1
#define AF2 2
#define AF3 3
#define AF4 4
#define AF5 5
#define AF6 6
#define AF7 7
#define AF8 8
#define AF9 9
#define AF10 10
#define AF11 11
#define AF12 12
#define AF13 13
#define AF14 14
#define AF15 15
/*MODE OPTIONS*/
#define Mode_INPUT               0
#define Mode_OUTPUT              1
#define Mode_AF               	 2
#define Mode_ANALOG              3

/*Type Options*/
#define push_pull    0
#define open_drain   1

/*Speed Options*/
#define LOW_SPEED		0
#define MEDIUM_SPEED	1
#define HIGH_SPEED		2
#define VERYHIGH_SPEED	3

/*PUPDR*/
#define PUPDR_NOPUPD 	 0
#define PUPDR_PULL_UP	 1
#define PUPDR_PULL_DOUWN 2

/*PIN VALUES*/
#define VALUE_LOW     0
#define VALUE_HIGH    1

ret_t MGPIO_SetPinMode(u32 GPIO_PORT,u32 PIN,u32 Mode);

ret_t MGPIO_SetPinType(u32 GPIO_PORT,u32 PIN,u32 Type);

ret_t MGPIO_SetPinValue(u32 GPIO_PORT,u32 PIN,u32 VALUE);

ret_t MGPIO_SetPinSpeed(u32 GPIO_PORT,u32 PIN,u32 Speed);

ret_t MGPIO_SetPinPUPDR(u32 GPIO_PORT,u32 PIN,u32 PUPDR);

ret_t MGPIO_SetPinAtomicValue(u32 GPIO_PORT,u32 PIN,u32 VALUE);

ret_t MGPIO_SetPinsAtomicValue(u32 GPIO_PORT,u32 PIN,u32 VALUE);
ret_t MGPIO_SetPinsValue(u32 GPIO_PORT,u32 PIN);
ret_t MGPIO_Setalternate_function(u32 GPIO_PORT,u32 GPIO_PIN,u32 GPIO_AF);
#endif /* GPIO_GPIO_DRIVER_H_ */
