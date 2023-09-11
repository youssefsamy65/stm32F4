/*
 * SPI_Driver.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Dell
 */

#ifndef SPI_SPI_DRIVER_H_
#define SPI_SPI_DRIVER_H_


#include "../../Common/STD_TYPE.h"
#include "../../Common/Util.h"


#define SPI_1			1
#define SPI_2			2
#define SPI_3			3

#define SS_PIN0			0
#define SS_PIN1			1
#define SS_PIN2			2
#define SS_PIN3			3
#define SS_PIN4			4
#define SS_PIN5			5
#define SS_PIN6			6
#define SS_PIN7			7
#define SS_PIN8			8
#define SS_PIN9			9
#define SS_PIN10		10
#define SS_PIN11		11
#define SS_PIN12		12
#define SS_PIN13		13
#define SS_PIN14		14
#define SS_PIN15		15

#define SS_PORTA		0
#define SS_PORTB		1
#define SS_PORTC		2


ret_t MSPI_MasterSlaveInit(u8 SPI);

ret_t MSPI_SendReciveSynch(u8 SPI, u8 SendData, u8 * ReciveData, u8 SS_PIN, u8 SS_PORT);

//ret_t MSPI_SendReciveAsynch(u8 SPI, u8 SendData, void (*SPI_CallBack)(u8));


#endif /* SPI_SPI_DRIVER_H_ */
