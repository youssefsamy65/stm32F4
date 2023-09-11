/*
 * sys_tick.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Dell
 */

#include "sys_tick.h"
static void (*ptr_is)(void);
#define base_Addrese 0xE000E010
typedef struct{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}sys_tick_t;
static volatile sys_tick_t * const ptr = (volatile sys_tick_t* const)base_Addrese;

Std_ReturnType sys_tick_en_dis(u8 state)
{
		u8 ret= E_OK;

	 if(state==enable || state==disable){
		 switch(state){
		 case enable: ptr->CTRL|=(BIT0_MASK); ptr->CTRL|=(BIT1_MASK);break;
		 case disable: ptr->CTRL&=~(BIT0_MASK);break;
		 }
	 }
	 else {
		 ret= E_NOT_OK;
	 }
	 return ret;
 }


void sys_tick_init(void)
 {
   #if system_clk == AHB_divided_8
	 ptr->CTRL&=~(BIT2_MASK);
   #elif system_clk == Processor_clock
	 ptr->CTRL|=(BIT2_MASK);
  #endif
 }


 Std_ReturnType sys_tick_mode(u8 mode)
 {
		u8 ret= E_OK;

		 if(mode==interupt || mode==polling){
			 switch(mode){
			 case interupt: ptr->CTRL|=(BIT1_MASK);break;
			 case polling: ptr->CTRL&=~(BIT1_MASK);break;
			 }
		 }
		 else {
			 ret= E_NOT_OK;
		 }
		 return ret;
 }


Std_ReturnType sys_tick_load(u32 time_t){
u32 load=0;
u8 ret= E_OK;

    #if system_clk == AHB_divided_8
	 load=2000*time_t;
    #elif system_clk == Processor_clock
		load=1600*time_t;
    #endif
	if(load >=0x00000001 && load<= 0x00FFFFFF ){
	ptr->LOAD=load;
	}
	else{
			 ret= E_NOT_OK;
		}
		return ret;
 }
Std_ReturnType sys_tick_load_micro(u32 time_t){
u32 load=0;
u8 ret= E_OK;

    #if system_clk == AHB_divided_8
	 load=2*time_t;
    #elif system_clk == Processor_clock
		load=16*time_t;
    #endif

	ptr->LOAD=load;




 }

 Std_ReturnType get_value(u32 *value_reamining,u32*value_pased)
 {
		u8 ret= E_OK;
if(NULL != value_reamining && NULL != value_pased){

	 #if system_clk == AHB_divided_8
	 *value_reamining=ptr->VAL*(1/2000);
	u32 temp=  ptr->LOAD - ptr->VAL;
	*value_pased=temp*(1/2000);
    #elif system_clk == Processor_clock
	 *value_reamining=ptr->VAL*(1/1600);
	u32 temp=  ptr->LOAD - ptr->VAL;
	*value_pased=temp*(1/1600);
   #endif
	}

else{
		 ret= E_NOT_OK;
	}
	return ret;
}



 Std_ReturnType cll_bck(void (*ptr_isr)(void)){
		u8 ret= E_OK;
		if(NULL != ptr_isr){
			ptr_is=ptr_isr;
		}
		else {
			 ret= E_NOT_OK;
		}
		return ret;
 }

 void SysTick_Handler(void){
		if(ptr_is!=NULL)
		{
			ptr_is();

		}
 }

