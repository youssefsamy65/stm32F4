/*
 * shced.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Dell
 */
#include "sched.h"
#include "../../MCAL/sys_tick/sys_tick.h"
#include "../../MCAL/STK/STK_Driver.h"
#define system_tcks_ms 1000
volatile u8 sched_flage;
volatile u8 index;

static struct {
	u32 size;
	task_t * rummable_task[max_number_tax];

}task;

static void schedluar();

static void schedluar_fuc(void);

/*
void RTOS_SCHED_init(void){

	sys_tick_init();
	sys_tick_mode(interupt);
	sys_tick_en_dis(enable);
	//sys_tick_load(system_tcks_ms);
	STK_PeriodMS(1000);
	cll_bck(&schedluar);

}
*/

void RTOS_SCHED_start(void){
		for(;;){
		if(sched_flage){
			schedluar_fuc();
			sched_flage=0;
		}
	}
}

/*
Std_ReturnType sched_addRUNBLE(const task_t *userTask){
	u8 ret=E_OK;
	if(NULL != userTask && task.size<=max_number_tax ){
		task.rummable_task[userTask->pirioity]=userTask;
		task.size++;
	}
	else{
		ret=E_NOT_OK;
	}
return ret;
}


static void schedluar_fuc(void){
	static u32 time;
	if(time){
	for(index=0;index<task.size;index++){

		if((time%(task.rummable_task[index]->periodicty==0) ) && (task.rummable_task[index]!=NULL) )
		{
		task.rummable_task[index]->ptr();
		}

	}

}
	time+=system_tcks_ms;
}*/
void schedluar(){
	sched_flage=1;
}
