/*
 * flash.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Dell
 */

#ifndef FLASH_FLASH_H_
#define FLASH_FLASH_H_
#include "../../common/bit_math.h"
#include "../../common/std_types.h"

#define sector0            0
#define sector1            1
#define sector2            2
#define sector3            3
#define sector4            4
#define sector5            5
#define sector6            6
#define sector7            7





void flash_sectorErase(u8 sector);
void flash_sectorWrite(u32  Address,u16 *Data, u8 length);
void flash_AreaErase(u8 start_sector , u8 end_sector);

#endif /* FLASH_FLASH_H_ */
