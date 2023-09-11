/*
 * Schd.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Adel
 */


//SELF LAYER INCLUDE
#include "Sched.h"
volatile u8 index;
//OTHER LAYERS INCLUDE

#include "../MCAL/STK/STK_Driver.h"
#include "../../MCAL/sys_tick/sys_tick.h"

static struct{
	u32 size;
	Task_t * Runnable_Task[Max_Task];
}Tasks;



u32 SchedIsReady;

///////////////////////////////////////FUN////////////////////

//Static Function prototypes
static void SchedReady();
static void Scheduler(void);


//Function
void RTOS_SchedInit(void)
{
	//sys_tick_init();
	//STK_PeriodMS(SysTickMs);
	sys_tick_load(SysTickMs);
	cll_bck(&SchedReady);   //Will Be Improved Later
//	STK_CallBack(SchedReady);
}
void RTOS_SCHED_init(void){

	//sys_tick_init();

	//sys_tick_load(1000);
//	STK_PeriodMS(1000);
	//cll_bck(&SchedReady);

}
void RTOS_SchedStart(void)
{
	//STK_StartInit();
//	sys_tick_en_dis(1);
//	sys_tick_init();
	//sys_tick_mode(1);
	sys_tick_init();
	sys_tick_en_dis(1);
	while(1)
	{
		if(SchedIsReady)
		{
			SchedIsReady=0;
			Scheduler();
		}
	}
}

void RTOS_AddTask(const Task_t* Task)
{
	if((Task!=NULL)&&(Tasks.size<=Max_Task))
	{
		Tasks.Runnable_Task[Task->Priority]=Task;
		Tasks.size++;
	}
}
Std_ReturnType sched_addRUNBLE(const Task_t *userTask){
	u8 ret=E_OK;
	if(NULL != userTask && Tasks.size<=10 ){
		Tasks.Runnable_Task[userTask->Priority]=userTask;
		Tasks.size++;
	}
	else{
		ret=E_NOT_OK;
	}
return ret;
}

//static functions Implementation


static void SchedReady()
{
	SchedIsReady=1;
}

static void Scheduler(void)
{

	static u32 Time;
	u32 index;
	if(Time)
	{
	for(index=0;index<Max_Task;index++)
	{
		if((Tasks.Runnable_Task[index]!=NULL) && (Time % (Tasks.Runnable_Task[index]->Pericity))==0)
		{
			if( (Tasks.Runnable_Task[index]->FunPtr) !=NULL){
			Tasks.Runnable_Task[index]->FunPtr();}

		}
	}
	}
	Time += SysTickMs;

}

