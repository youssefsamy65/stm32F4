/*
 * USART.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Dell
 */

#ifndef USART_USART_DRIVER_H_
#define USART_USART_DRIVER_H_
#include "../../common/std_types.h"
#include "../../common/bit_math.h"



#define USART_1			1
#define USART_2			2
#define USART_6			6




ret_t MUSART_Init(u32 USART);

ret_t MUSART_SendByteSynch(u32 USART,u8 DataSend);

u8 MUSART_ReciveByteSynch(u32 USART);

ret_t MUSART_SendStringSynch(u32 USART,char * SendString);

void MUSART_ReciveStringSynch(u32 USART,u8 RecivedStg[]);

u8 error_detection();

#endif /* USART_USART_DRIVER_H_ */
