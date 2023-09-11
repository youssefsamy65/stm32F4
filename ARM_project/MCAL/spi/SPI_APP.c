/*
 * SPI_APP.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Dell
 */

#include "SPI_Config.h"
#include "SPI_Driver.h"
#include "../MCAL/GPIO/GPIO_Driver.h"

#define SPI1_BASEADDRESS		0x40013000
#define SPI2_BASEADDRESS		0x40003800
#define SPI3_BASEADDRESS		0x40003C00


typedef struct{

	u32 CR1;
	u32 CR2;
	u32 SR;
	u32 DR;
	u32 CRCPR;
	u32 RXCRCR;
	u32 TXCRCR;
	u32 I2SCFGR;
	u32 I2SPR;
}SPIx_t;

#define  SPI1	((volatile SPIx_t*)SPI1_BASEADDRESS)
#define  SPI2	((volatile SPIx_t*)SPI2_BASEADDRESS)
#define  SPI3	((volatile SPIx_t*)SPI3_BASEADDRESS)


/******************************* Options Macrod *************************/
#define ENABLE		1
#define DISABLE		0

#define Read_Write	0
#define Write_Read	1

#define IDLE_1		1
#define IDLE_0		0

#define MASTER		1
#define SLAVE		0

#define Clk_Div_2	0
#define Clk_Div_4	1
#define Clk_Div_8	2
#define Clk_Div_16	3
#define Clk_Div_32	4
#define Clk_Div_64	5
#define Clk_Div_128	6
#define Clk_Div_256	7

#define MSB_First	0
#define LSB_First	1

#define FullDuplex	0
#define ReciveOnly	1

#define Data_8		0
#define Data_16		1


#define GPIO_PORTA		0
#define GPIO_PORTB		1
#define GPIO_PORTC		2

/************************************************SS_PIN************************************************************************/
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


ret_t MSPI_MasterSlaveInit(u8 SPI)
{
	u32 State =  ret_Error;
	if(SPI==SPI_1)
	{
		SPI1->CR1=( SPI_CPHA<<0 | SPI_CPOL<<1 | SPI_MSTR<<2 | SPI_BR<<3 | SPI_MSB_Sending<<7 | SPI_SSM<<9 | SPI_RXONLY<<10 | SPI_DFF<<11);
		SPI1->CR2=( SPI_TXEIE<<7 | SPI_RXEIE<<6 | SPI_ERRIE<<5 );
		SPI1->CR1 |= SPI_EN<<6;
		State =  ret_OK;
	}
	else if(SPI==SPI_2)
	{
		SPI2->CR1=( SPI_CPHA<<0 | SPI_CPOL<<1 | SPI_MSTR<<2 | SPI_BR<<3 | SPI_MSB_Sending<<7 | SPI_SSM<<9 | SPI_RXONLY<<10 | SPI_DFF<<11);
		SPI2->CR2=( SPI_TXEIE<<7 | SPI_RXEIE<<6 | SPI_ERRIE<<5 );
		SPI2->CR1 |= SPI_EN<<6;
		State =  ret_OK;
	}
	else if(SPI==SPI_3)
	{
		SPI3->CR1=( SPI_CPHA<<0 | SPI_CPOL<<1 | SPI_MSTR<<2 | SPI_BR<<3 | SPI_MSB_Sending<<7 | SPI_SSM<<9 | SPI_RXONLY<<10 | SPI_DFF<<11);
		SPI3->CR2=( SPI_TXEIE<<7 | SPI_RXEIE<<6 | SPI_ERRIE<<5 );
		SPI3->CR1 |= SPI_EN<<6;
		State =  ret_OK;
	}
	else
	{
		State =  ret_Error;
	}
	return State;
}

ret_t MSPI_SendReciveSynch(u8 SPI, u8 SendData, u8 * ReciveData, u8 SS_PIN, u8 SS_PORT)
{
	u32 State = ret_Error;
	if(SPI_MSTR==MASTER){
	MGPIO_SetPinMode(SS_PORT,SS_PIN,Mode_OUTPUT);
	MGPIO_SetPinValue(SS_PORT,SS_PIN,VALUE_LOW);}

	if(SPI==SPI_1)
	{
		SPI1->DR=SendData;
		while(( (SPI1->SR>>7) & 1)==1);
		*ReciveData=SPI1->DR;
		State =ret_OK;
	}
	else if(SPI==SPI_2)
	{
		SPI2->DR=SendData;
		while(( (SPI2->SR>>7) & 1)==1);
		*ReciveData=SPI2->DR;
		State =ret_OK;
	}
	else if(SPI==SPI_3)
	{
		SPI3->DR=SendData;
		while(( (SPI3->SR>>7) & 1)==1);
		*ReciveData=SPI3->DR;
		State =ret_OK;
	}
	else
	{
		State =ret_Error;
	}

	if(SPI_MSTR==MASTER) MGPIO_SetPinValue(SS_PORT,SS_PIN,VALUE_HIGH);

	return State;
}

//ret_t MSPI_SendReciveAsynch(u8 SPI, u8 SendData, void (*SPI_CallBack)(u8))
//{
//
//}


