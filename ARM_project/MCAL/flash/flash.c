/*
 * flash.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Dell
 */
#include "flash.h"

#define flash_base_address 0x40023C00
#define busy_bit 16
#define  keys_unlock1       0x45670123
#define  keys_unlock2       0xCDEF89AB

typedef struct{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;
}FLASH_t;
static volatile FLASH_t * const flash_ptr = (volatile FLASH_t * const) flash_base_address;
static void flash_unlock(void);

void flash_sectorErase(u8 sector){
	u8 temp=0;

	/* check any opertaion on going */
    while(((flash_ptr->SR>>busy_bit)&1));


	/* unlock sequance */
    flash_unlock();

	/*  choose the sector   */
    temp= flash_ptr->CR;
	temp &=~(0xF<<3);
	temp|=(sector<<3);
	flash_ptr->CR=temp;

	/* select SET BIT ACTIVATE */
	flash_ptr->CR|=(1<<1);

	/* start */
	flash_ptr->CR|=(1<<16);
	/* wait until finish */
	while(((flash_ptr->SR>>busy_bit)&1));

	/* deactivate */
	flash_ptr->CR&=~(1<<1);
}
void flash_sectorWrite(u32  Address,u16 *Data, u8 length){
u8 i=0;
u8 temp=0;
	/* check any opertaion on going */
    while(((flash_ptr->SR>>busy_bit)&1));


	/* unlock sequance */
        flash_unlock();

        temp=flash_ptr->CR;
        temp&=~(0x3<<8);
        temp|=(1<<8);
        flash_ptr->CR=temp;

        for(i=0;i<length;i++){

    	flash_ptr->CR|=(1<<0);

    	*((volatile u16*)Address)=Data[i];

    	Address+=2;

        while(((flash_ptr->SR>>busy_bit)&1));

        flash_ptr->CR &=~(1<<0);
    }
}
void flash_AreaErase(u8 start_sector , u8 end_sector){
	u8 i=0;
	for(i=start_sector;i<end_sector;i++){
		flash_sectorErase(i);
	}
}
void flash_unlock(void){
	if( ((flash_ptr->CR>>31)&1)  ){
		flash_ptr->KEYR =keys_unlock1;
		flash_ptr->KEYR =keys_unlock2;
	}
}
