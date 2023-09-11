/*
 * dma.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Dell
 */


#include "dma.h"
#include "../common/BIT_MATH.h"

static void (*Global_ptr)(void);


#define DMA1_BaseAddress			0x40026000
#define DMA2_BaseAddress			0x40026400

typedef struct{
	u32 CR;
	u32 NDTR;
	u32 PAR;
	u32 M0AR;
	u32 M1AR;
	u32 FCR;
}Stream_t;

typedef struct{
	u32 LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;
	Stream_t S[8];
}DMAx_t;

#define DMA1				((volatile DMAx_t*)DMA1_BaseAddress)
#define DMA2				((volatile DMAx_t*)DMA2_BaseAddress)


/******************************APIs**************************************/
void MDMA_Init(u8 DMA, u8 Stream)
{
	if(DMA == DMA_1)
	{

	}
	else if(DMA == DMA_2)
	{
		DMA2->S[Stream].CR &= ~(1<<0);
		DMA2->S[Stream].CR |= (1<<14) | (1<<12) | (1<<10) | (1<<9) | (1<<7) | (1<<4);
	}
}

void MDMA_SetStream(u8 DMA, u8 Stream, u32 * SRC_Add, u32 * DIST_Add, u8 Element, u8 Block_Size, u8 Channel, u8 MINC, u8 PINC, u8 DIR)
{
	if(DMA == DMA_1)
	{

	}
	else if(DMA == DMA_2)
	{
		DMA2->S[Stream].PAR = SRC_Add;
		DMA2->S[Stream].M0AR = DIST_Add;
		DMA2->S[Stream].NDTR = Block_Size;
	}
}

void MDMA_EnableStream(u8 DMA, u8 Stream)
{
	if(DMA == DMA_1)
	{

	}
	else if(DMA == DMA_2)
	{
		DMA2->LIFCR |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5);
		DMA2->S[Stream].CR |= (1<<0);
	}
}

void MDMA_CallBack(void (*ptr)(void))
{
	if(ptr!=NULL)
	{
		Global_ptr=ptr;
	}
}

void MDMA_Clrflags(u8 Stream)
{
	DMA2->LIFCR |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5);
}

DMA2_Stream0_IRQHandler(void)
{
	if(Global_ptr!=NULL)
	{
		Global_ptr();
	}
}



