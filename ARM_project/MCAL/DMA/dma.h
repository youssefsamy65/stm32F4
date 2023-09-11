/*
 * dma.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Dell
 */

#ifndef DMA_H_
#define DMA_H_

#include"../common/STD_TYPE.h"

#define DMA_1          0
#define DMA_2          1

#define Stream0        0
#define Stream1        1
#define Stream2        2
#define Stream3        3
#define Stream4        4
#define Stream5        5
#define Stream6        6
#define Stream7        7

#define Element_Size_8_Bit         0
#define Element_Size_16_Bit         1
#define Element_Size_32_Bit          2




void MDMA_Init(u8 DMA, u8 Stream);

//void MDMA_SetStream(u8 DMA, u8 Stream, u32 * SRC_Add, u32 * DIST_Add, u8 Element, u8 Block_Size, u8 Channel, u8 MINC, u8 PINC, u8 DIR);
void MDMA_SetStream(u8 DMA, u8 Stream, u32 * SRC_Add, u32 * DIST_Add, u8 Element, u8 Block_Size, u8 Channel, u8 MINC, u8 PINC, u8 DIR);

void MDMA_EnableStream(u8 DMA, u8 Stream);

void MDMA_CallBack(void (*ptr)(void));

void MDMA_Clrflags(u8 Stream);







#endif /* DMA_H_ */
