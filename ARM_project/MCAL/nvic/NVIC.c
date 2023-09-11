/*
 * NVIC.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Dell
 */
#include "NVIC.h"
#include "../MCAL/GPIO/gpio.h"


#define NVIC_base_addres 0xE000E100
#define AIRCR 0xE000ED00
#define bits_number 32
#define maximam_IRQn 84
#define mmin_IRQn 0
typedef struct {
u32 ISER[8];
u32 reserved_0[24];
u32 ICER[8];
u32 reserved_3[24];
u32 ISPR[8];
u32 reserved_4[24];
u32 ICPR[8];
u32 reserved_5[24];
u32 IABR[8];
u32 reserved_6[57];
u8 IPR[240];
u32 reserved_7[581];
u32 STIR ;
}NVIC_t;
static volatile NVIC_t *const ptr= (volatile NVIC_t *const)NVIC_base_addres;
static volatile u32 *const ptr_ctr= (volatile u32 *const)AIRCR;

void piority_config(void){
	*ptr_ctr=set_priolity;
}
Std_ReturnType enable_nvicID(u32 NVIC_ID){
u8 ret= E_OK;
if(NVIC_ID>=0 && NVIC_ID<=maximam_IRQn){

	ptr->ISER[NVIC_ID/bits_number] |= (1<<(NVIC_ID%bits_number));

}
else {
	ret= E_NOT_OK;
}MGPIO_SetPinValue(GPIO_PORTA,PIN3,VALUE_HIGH);
return ret;
}
Std_ReturnType disable_nvicID(u32 NVIC_ID){
u8 ret= E_OK;
if(NVIC_ID>=mmin_IRQn && NVIC_ID<=maximam_IRQn){
	u32 temp=ptr->ICER[NVIC_ID/bits_number];
	temp &=~(1<<(NVIC_ID%bits_number));
	temp |= (1<<(NVIC_ID%bits_number));
	ptr->ICER[NVIC_ID/bits_number]=temp;
}
else {
	ret= E_NOT_OK;
}
return ret;
}



Std_ReturnType enable_pending(u32 NVIC_ID){
u8 ret= E_OK;
if(NVIC_ID>=mmin_IRQn && NVIC_ID<=maximam_IRQn){
	u32 temp=ptr->IPR[NVIC_ID/bits_number];
	temp &=~(1<<(NVIC_ID%bits_number));
	temp |= (1<<(NVIC_ID%bits_number));
	ptr->IPR[NVIC_ID/bits_number]=temp;
}
else {
	ret= E_NOT_OK;
}
return ret;
}
Std_ReturnType clear_pending_NVIC(u32 NVIC_ID){
u8 ret= E_OK;
  if(NVIC_ID>=mmin_IRQn && NVIC_ID<=maximam_IRQn){
	u32 temp=ptr->ICPR[NVIC_ID/bits_number];
	temp &=~(1<<(NVIC_ID%bits_number));
	temp |= (1<<(NVIC_ID%bits_number));
	ptr->ICPR[NVIC_ID/bits_number]=temp;
}
else {
	ret= E_NOT_OK;
}
return ret;
}
Std_ReturnType software_triggar(u32 NVIC_ID){
u8 ret= E_OK;
  if(NVIC_ID>=mmin_IRQn && NVIC_ID<=maximam_IRQn){
ptr->STIR= (u8)NVIC_ID;
}
else {
	ret= E_NOT_OK;
}
return ret;
}

Std_ReturnType set_piroirty(u32 NVIC_ID , u32 Groub , u32 Sub_Groub){
#if SW_Priority==Groub16_SubGroub0
if(Groub>=0 && Groub<=15 && Sub_Groub==0)
{
	ptr->IPR[NVIC_ID] = (Groub<<4);
return ret_OK;
}
else
{
	return ret_Error;
}

#elif SW_Priority==Groub8_SubGroub2

ptr->IPR[NVIC_ID] = ((Groub<<5) | (Sub_Groub<<4));


#elif SW_Priority==Groub4_SubGroub4

if(Groub>=0 && Groub<=4 && Sub_Groub>=0 && Sub_Groub<=4)
{
	ptr->IPR[NVIC_ID] = ((Groub<<6) | (Sub_Groub<<4));
return ret_OK;
}
else
{
	return ret_Error;
}
#elif(SW_Priority==Groub2_SubGroub8)

ptr->IPR[NVIC_ID] = ((Groub<<7) | (Sub_Groub<<4));

#elif (SW_Priority==Groub0_SubGroub16)

ptr->IPR[NVIC_ID] = (Sub_Groub<<4);

#endif
}
