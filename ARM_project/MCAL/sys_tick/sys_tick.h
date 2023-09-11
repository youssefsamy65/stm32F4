/*
 * sys_tick.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Dell
 */

#ifndef SYS_TICK_SYS_TICK_H_
#define SYS_TICK_SYS_TICK_H_
#include "../../common/std_types.h"
#include "../../common/bit_math.h"

#define AHB_divided_8   0
#define Processor_clock 1

#define system_clk  Processor_clock

#define interupt 1
#define polling  0

#define disable 0
#define enable  1

/*
typedef enum{
	AHB_diveded_8,
	Processor_clock
}CLKSOURCE;
typedef enum{
	interupt,
	polling
}control_t;
*/

Std_ReturnType sys_tick_en_dis(u8 state);
void sys_tick_init(void);
Std_ReturnType sys_tick_mode(u8 mode);
Std_ReturnType sys_tick_load(u32 time_t);
Std_ReturnType sys_tick_load_micro(u32 time_t);
Std_ReturnType get_value(u32 *value_remaining, u32 *value_passed);
Std_ReturnType cll_bck(void (*ptr_isr)(void));



#endif /* SYS_TICK_SYS_TICK_H_ */
