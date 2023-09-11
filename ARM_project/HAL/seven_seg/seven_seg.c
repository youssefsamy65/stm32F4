/*
 * seven_seg.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Dell
 */
#include "seven_seg.h"
#include "../../MCAL/sys_tick/sys_tick.h"

#define stop  0b11111111
static u8 common_anode[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92,0x82,0xF8, 0x80, 0x90};
static u8 common_cathode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
Std_ReturnType seven_seg_init(sevent_seg * sevent_segment ){
	u8 ret= E_OK;
	if (NULL !=sevent_segment) {
		MGPIO_SetPinMode(sevent_segment->port,sevent_segment->pins[0],Mode_OUTPUT);
		MGPIO_SetPinMode(sevent_segment->port,sevent_segment->pins[1],Mode_OUTPUT);
		MGPIO_SetPinMode(sevent_segment->port,sevent_segment->pins[2],Mode_OUTPUT);
		MGPIO_SetPinMode(sevent_segment->port,sevent_segment->pins[3],Mode_OUTPUT);
		MGPIO_SetPinMode(sevent_segment->port,sevent_segment->pins[4],Mode_OUTPUT);
		MGPIO_SetPinMode(sevent_segment->port,sevent_segment->pins[5],Mode_OUTPUT);
		MGPIO_SetPinMode(sevent_segment->port,sevent_segment->pins[6],Mode_OUTPUT);
	    MGPIO_SetPinMode(GPIO_PORTA,PIN9,Mode_OUTPUT);
	    MGPIO_SetPinMode(GPIO_PORTA,PIN8,Mode_OUTPUT);


	}
	else{
	ret= E_NOT_OK;

	}
return ret;
}
Std_ReturnType seven_seg_write(sevent_seg * sevent_segment,u32 number){
	u8 ret= E_OK;

	if ((NULL !=sevent_segment) &&  (number>=0 && number<=9)) {
		switch(sevent_segment->type)
		{
		case SEGMENT_COMMON_ANODE:MGPIO_SetPinsValue(sevent_segment->port,common_anode[number]);break;
		case SEGMENT_COMMON_CATHODE:MGPIO_SetPinsValue(sevent_segment->port,common_cathode[number]);break;
		}
		}
	else{
	ret= E_NOT_OK;
}
return ret;
}

Std_ReturnType seven_seg_stop(sevent_seg * sevent_segment){
	u8 ret= E_OK;

	if (NULL !=sevent_segment) {
		MGPIO_SetPinsValue(sevent_segment->port,0);

	}
	else{
	ret= E_NOT_OK;

	}
return ret;
}
