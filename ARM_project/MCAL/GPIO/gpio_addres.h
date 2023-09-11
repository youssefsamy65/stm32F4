/*
 * gpio_addres.h
 *
 *  Created on: Aug 10, 2023
 *      Author: Dell
 */

#ifndef GPIO_GPIO_ADDRES_H_
#define GPIO_GPIO_ADDRES_H_
#include "../../common/std_types.h"
#include "../../common/bit_math.h"


 u32 MODERA;    /*!< GPIO port mode register,               Address offset: 0x00      */
 u32 OTYPERA;   /*!< GPIO port output type register,        Address offset: 0x04      */
 u32 OSPEEDRA;  /*!< GPIO port output speed register,       Address offset: 0x08      */
 u32 PUPDRA;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
 u32 IDRA;      /*!< GPIO port input data register,         Address offset: 0x10      */
 u32 ODRA;      /*!< GPIO port output data register,        Address offset: 0x14      */
 u32 BSRRA;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
 u32 LCKRA;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
 u32 AFRA_high;   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
 u32 AFRA_low;   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */




#endif /* GPIO_GPIO_ADDRES_H_ */
