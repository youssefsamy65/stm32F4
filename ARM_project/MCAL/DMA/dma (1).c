/*
 * dma.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Dell
 */


#include "../Mcal/Rcc.h"
#include "../Mcal/Gpio.h"
#include "../Mcal/dma.h"
#include "../Mcal/SPI.h"
#include "../Mcal/NVIC.h"

void func(void);
int main()
{
	u32 arr[100]={1,2,3};
	u32 arr_Temp[100]={0};

	MRCC_EnablePeripheralCLK(peri_AHB1_GPIOA,peri_busAPB1);
	MRCC_EnablePeripheralCLK(peri_AHB1_DMA2, peri_busAHB1);

	MGPIO_SetPinMode(GPIO_PORTA, PIN0,Mode_OUTPUT);
	MGPIO_SetPinMode(GPIO_PORTA, PIN1,Mode_OUTPUT);

	MNVIC_EnableINT_ID(NVIC_ID_DMA2_Stream0);



	MDMA_Init(DMA_2,Stream0);
	MDMA_CallBack(&func);
	MDMA_SetStream(DMA_2,Stream0,arr,arr_Temp,0,100,0,0,0,0);
	MDMA_EnableStream(DMA_2,Stream0);

	 u32 i;
	for(i=0;i<100;i++)
	{
		arr_Temp[i]=arr[i];
	}
	MGPIO_SetPinValue(GPIO_PORTA,PIN1,VALUE_HIGH);
    while(1);

	return 0;
}

void func(void)
{
	 u32 i;
	MGPIO_SetPinValue(GPIO_PORTA,PIN0,VALUE_HIGH);
	for(i=0;i<1000000;i++);
}
