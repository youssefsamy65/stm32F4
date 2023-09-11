#include "../../MCAL/gpio/gpio.h"
#include "../../song_project/pablo.h"
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/sys_tick/sys_tick.h"



volatile  u32 i;
void song();

void song(){

	MGPIO_SetPinsValue(GPIO_PORTA,pablo_raw[i]);
	i++;
	if(i==0){
	i=0;
}

}


int main()
{
	RCC_Enable_periClk(peri_AHB1_GPIOA,AHB1);
	MGPIO_SetPinMode(GPIO_PORTA,PIN0,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA,PIN1,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA,PIN2,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA,PIN3,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA,PIN4,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA,PIN5,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA,PIN6,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA,PIN7,Mode_OUTPUT);




//	sys_tick_load(125);
	sys_tick_load_micro(125);
	cll_bck(&song);   //Will Be Improved Later
	sys_tick_init();
	sys_tick_en_dis(1);
	return 0;
}
// ----------------------------------------------------------------------------
