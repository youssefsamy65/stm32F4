/*
 * NVIC.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Dell
 */

#ifndef NVIC_NVIC_H_
#define NVIC_NVIC_H_

#include "../../common/std_types.h"
#include "../../common/bit_math.h"

#define NVIC_WWD   0
#define NVIC_EXTI16 1
#define NVIC_EXTI21 2
#define NVIC_EXTI22 3
#define NVIC_FLASH  4
#define NVIC_RCC    5
#define NVIC_EXTIO  6
#define NVIC_EXT    7
#define NVIC_EXTI2  8
#define NVIC_EXTI3  9
#define NVIC_EXTI4  10
#define NVIC_DMA1_Stream0  11
#define NVIC_DMA1_Stream1  12
#define NVIC_DMA1_Stream2  13
#define NVIC_DMA1_Stream3  14
// Define constants for NVIC interrupt sources
#define NVIC_DMA1_Stream4  15
#define NVIC_DMA1_Streams  16
#define NVIC_DMA1_Stream5  17
#define NVIC_ADC1         18
#define NVIC_EXTI9_5      23
#define NVIC_TIM1_BRK_TIM9 24
#define NVIC_TIM1_UP_TIM10 25
#define NVIC_TIM1_TRG_COM_TIM11 26
#define NVIC_TIM1_CC      27
#define NVIC_TIM2         28
#define NVIC_TIM3         29
#define NVIC_TIM4         30
#define NVIC_I2C1_EV      31
#define NVIC_I2C1_ER      32
#define NVIC_I2C2_EV      33
#define NVIC_I2C2_ER      34
#define NVIC_SPI1         35
#define NVIC_SPI2         36
#define NVIC_USART1       37
// Define constants for NVIC interrupt sources
#define NVIC_USART2        38
#define NVIC_EXTI15_10     40
#define NVIC_EXTI17_RTC_Alarm 41
#define NVIC_EXTI18_OTG_FS_WKUP 42
#define NVIC_DMA1_Stream7  47
#define NVIC_SDIO          49
#define NVIC_TIM5          50
#define NVIC_SPI3          51
#define NVIC_DMA2_Stream0  56
#define NVIC_DMA2_Stream1  57
#define NVIC_DMA2_Stream2  58
#define NVIC_DMA2_Stream3  59
#define NVIC_DMA2_Stream4  60
#define NVIC_OTG_FS        67
#define NVIC_DMA2_Stream5  68
#define NVIC_DMA2_Stream6  69
#define NVIC_DMA2_Stream7  70
#define NVIC_USART6        71
#define NVIC_I2C3_EV       72
#define NVIC_I2C3_ER       73
#define NVIC_FPU           81
#define NVIC_SPI4          84

/*************************************pioroity_oprions**************************/

#define groub16_sub0  0xFA050000
#define groub8_sub2   0xFA0500400
#define groub4_sub4   0xFA0500500
#define groub2_sub8   0xFA0500600
#define groub0_sub16  0xFA0500700

#define set_priolity groub4_sub4
void piority_config(void);

Std_ReturnType enable_nvicID(u32 NVIC_ID);
Std_ReturnType disable_NVIC_ID(u32 NVIC_ID);
Std_ReturnType set_pending(u32 NVIC_ID);
Std_ReturnType clear_pending_NVIC(u32 NVIC_ID);
Std_ReturnType software_triggar(u32 NVIC_ID);
Std_ReturnType set_piroirty(u32 NVIC_ID , u32 group , u32 sub_group);

#endif /* NVIC_NVIC_H_ */
