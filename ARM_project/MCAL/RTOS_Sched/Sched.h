/*
 * Sched.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Adel
 */

#ifndef SCHED_H_
#define SCHED_H_


#include "../../Common/std_types.h"
#include "../../common/bit_math.h"


/*CONFIG*/
//####################################################
#define SysTickMs    10
#define Max_Task	 10
//####################################################



typedef struct{
	void (*FunPtr)(void);
	u32 Pericity;
	u32 Priority;
	char * Name;
}Task_t;


void RTOS_SCHED_init(void);

void RTOS_SchedInit(void);

void RTOS_SchedStart(void);

void RTOS_AddTask(const Task_t* Task);
Std_ReturnType sched_addRUNBLE (const Task_t *userTask);

#endif /* SCHED_H_ */
