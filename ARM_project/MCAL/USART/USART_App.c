/*
 * USART.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Dell
 */
#include "USART_Config.h"
#include "USART_Driver.h"

/////////////////////////////////////////////////////////////////////////////////Macros

/************************************************** ENABLE-DISABLE ********************************************************************/
#define ENABLE				    	1
#define DISABLE				    	0
/************************************************** YES-NO ****************************************************************************/
#define YES							1
#define NO							0
/************************************************** PARITY TYPE **********************************************************************/
#define EVEN						0
#define ODD							1
/************************************************** OVERSAMPLING *********************************************************************/
#define OVER_SAMPLE_8				1
#define OVER_SAMPLE_16				0
/************************************************** DATA LENGHT **********************************************************************/
#define WORD_LENGHT_D8				0
#define WORD_LENGHT_D9				1
/************************************************** STOP BITS ************************************************************************/
#define STOP0_5						1
#define STOP1						0
#define STOP2						2
#define STOP1_5						3
/************************************************** CLK POLARITY ****************************************************************/
#define CLK_LOW_VALUE				0
#define CLK_HIGH_VALUE				1
/************************************************** CLK PHASE ****************************************************************/
#define FirstCLK_FirstCapture		0
#define SecondCLK_FirstCapture		1

/////////////////////////////////////////////////////////////////////////////////Registers
#define USART1_BASEADDRESS			0x40011000
#define USART2_BASEADDRESS			0x40004400
#define USART6_BASEADDRESS			0x40011400

typedef struct{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}USARTx_t;

#define USART1		((volatile USARTx_t *)USART1_BASEADDRESS)
#define USART2		((volatile USARTx_t *)USART2_BASEADDRESS)
#define USART6		((volatile USARTx_t *)USART6_BASEADDRESS)

///////////////////////////////////////////////////////////////////////////////////functions

ret_t MUSART_Init(u32 USART)
{
	if(USART==USART_1){

		USART1->CR1 = (T_EN<<3 | R_EN<<2 | PARITY_EN<<10 | PEINT_EN<<8 | TX_INT_EN<<7 | RX_INT_EN<<5 | TCINT_EN <<6
				| IDLE_INT_EN <<4 | PARITY_SELECTION<<9 | OVER_SAMPLE<<15 | WORD_LENGHT<<12);

		USART1->CR2 = (CLK_EN<<11 |STOP_BIT<<12 |CLK_POLARITY<<10 |CLK_PHASE<<9);

		//baude rate
		USART1->BRR=BAUDE_RATE ;

		USART1->SR =0x0;

		//enable USART
		USART1->CR1 |= (USART_EN<<13);

		return ret_OK;
	}
	else if(USART==USART_2){

		USART2->CR1 = (T_EN<<3 | R_EN<<2 | PARITY_EN<<10 | PEINT_EN<<8 | TX_INT_EN<<7 | RX_INT_EN<<5 | TCINT_EN <<6
				| IDLE_INT_EN <<4 | PARITY_SELECTION<<9 | OVER_SAMPLE<<15 | WORD_LENGHT<<12);

		USART2->CR2 = (CLK_EN<<11 |STOP_BIT<<12 |CLK_POLARITY<<10 |CLK_PHASE<<9);

		//baude rate
		USART2->BRR=BAUDE_RATE ;

		USART2->SR =0x0;

		//enable USART
		USART2->CR1 |= (USART_EN<<13);

		return ret_OK;
	}
	else if(USART==USART_6){

		USART6->CR1 = (T_EN<<3 | R_EN<<2 | PARITY_EN<<10 | PEINT_EN<<8 | TX_INT_EN<<7 | RX_INT_EN<<5 | TCINT_EN <<6
				| IDLE_INT_EN <<4 | PARITY_SELECTION<<9 | OVER_SAMPLE<<15 | WORD_LENGHT<<12);

		USART6->CR2 = (CLK_EN<<11 |STOP_BIT<<12 |CLK_POLARITY<<10 |CLK_PHASE<<9);

		//baude rate
		USART6->BRR=BAUDE_RATE ;

		USART6->SR =0x0;

		//enable USART
		USART6->CR1 |= (USART_EN<<13);

		return ret_OK;
	}
	else
	{
		return ret_Error;
	}
}

ret_t MUSART_SendByteSynch(u32 USART,u8 DataSend)
{
	switch(USART)
	{
	case USART_1:
		//wait until data register is empty then last transmission is done
		while(((USART1->SR >>7) &1)==0);
		USART1->DR = DataSend;
		//wait until transmission is completed
		while(((USART1->SR >>6) &1)==0);
		USART1->SR &= ~(1<<6);
		break;
	case USART_2:
		//wait until data register is empty then last transmission is done
		while(((USART2->SR >>7) &1)==0);
		USART1->DR = DataSend;
		//wait until transmission is completed
		while(((USART2->SR >>6) &1)==0);
		USART1->SR &= ~(1<<6);
		break;
	case USART_6:
		//wait until data register is empty then last transmission is done
		while(((USART6->SR >>7) &1)==0);
		USART1->DR = DataSend;
		//wait until transmission is completed
		while(((USART6->SR >>6) &1)==0);
		USART1->SR &= ~(1<<6);
		break;
	default:
		return ret_Error;
	}
	return ret_OK;
}

u8 MUSART_ReciveByteSynch(u32 USART)
{   u8 RecivedByte=0;
	if(USART==USART_1)
	{
	while(((USART1->SR >>5) &1)==0);
	RecivedByte = USART1->DR & 0xFF;
	}
	else if(USART==USART_2)
	{
	while(((USART2->SR >>5) &1)==0);
	RecivedByte = USART2->DR & 0xFF;
	}
	else if(USART==USART_6)
	{
	while(((USART6->SR >>5) &1)==0);
	RecivedByte = USART6->DR & 0xFF; //anding with 0xff(1111 1111) to make sure that we return only one byte
	}
	else{
		/*do nothing*/
	}
	return RecivedByte;
}

ret_t MUSART_SendStringSynch(u32 USART,char * SendString)
{
	while( (*SendString) !='\0')
	{
		MUSART_SendByteSynch(USART,*SendString);
		SendString++;
	}
	return ret_OK;
}

void MUSART_ReciveStringSynch(u32 USART,u8 RecivedStg[])
{
	u32 i=0;
	while(1)
	{
		RecivedStg[i]=MUSART_ReciveByteSynch(USART);
		if(RecivedStg[i]=='\r') break;
		i++;
	}
}

u8 error_detection(){
	u8 ret=0;
	u8 x=((USART1->SR >>1)&1);
	ret=x;
	u8 y=((USART1->SR >>2)&1);
	ret=(x | y);
	return ret;
}
