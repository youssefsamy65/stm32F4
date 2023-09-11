/*
 * S2P.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Dell
 */

#include "S2P.h"
#include "../../MCAL/gpio/gpio.h"

void send_bit_asynch(sp_info*sp,u16 user_byte){
	u8 MSB ;
	s8 i=0;
	for(i=15;i>=0;i--){

		MSB=(user_byte>>i)&1 ;

		MGPIO_SetPinValue(sp->D_port,sp->D_pin,MSB);
	MGPIO_SetPinValue(sp->S_port,sp->S_pin,VALUE_HIGH);

	MGPIO_SetPinValue(sp->S_port,sp->S_pin,VALUE_LOW);

}
	MGPIO_SetPinValue(sp->ST_port,sp->ST_pin,VALUE_HIGH);

	MGPIO_SetPinValue(sp->ST_port,sp->ST_pin,VALUE_LOW);

}

