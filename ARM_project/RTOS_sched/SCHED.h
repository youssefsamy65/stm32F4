/*
 * SCHED.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Dell
 */

#ifndef SCHED_H_
#define SCHED_H_

#include "../../Common/std_types.h"
#include "../../common/bit_math.h"
#include "../../MCAL/sys_tick/sys_tick.h"

#define sys_ticks_ms 1000
#define max_number_tax 10

typedef struct {
	void (*ptr)();
	u32 periodicty ;
	u32 pirioity ;
	char *nam;

}task_t;


void RTOS_SCHED_init(void);
void RTOS_SCHED_start(void);
Std_ReturnType sched_addRUNBLE (const task_t *userTask);



#endif /* SCHED_H_ */
