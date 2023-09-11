/*
 * external_int.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Dell
 */

#include "extenal_int.h"
#include "../MCAL/GPIO/gpio.h"

/************************ Section: Macro Definitions*///////////////////////////////////////
#define step 4
#define bits 0xF
#define bits_regiser 4

#define EXTI_INT_BASE_ADDRESE 0x40013C00
#define SYS_BASE_ADDRESE 0x40013800
/* ************************* Define a function pointer array for ISR***************/
static void (*  ptr_ISR[21])(void);


/* ************************* REGISTERS********************************************/

typedef struct{
	u32 IMR;
	u32 EMR;
	u32 RTSR ;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}EXTI_INT;
typedef struct{
	u32 MEMRMP;
	u32 PMC ;
	u32 EXTICR[4];
	u32 CMPCR;
}SYSCFG;

static volatile EXTI_INT *const ptr= (volatile EXTI_INT *const)EXTI_INT_BASE_ADDRESE;
static volatile SYSCFG *const ptr_ctr= (volatile SYSCFG *const)SYS_BASE_ADDRESE;

Std_ReturnType port_selection_configure(external_interupt *ext_int){
	u8 ret= E_OK;
	if((NULL != ext_int) && (ext_int->line >=0 && ext_int->line <15) && ( ((ext_int->port)>=0) && ((ext_int->port)<=6) ) ){
		u32 temp=ptr_ctr->EXTICR[(ext_int->line)/bits_regiser];
		temp &=~(bits<<((ext_int->line)%bits_regiser)*step);
		temp |= ((ext_int->port)<<((ext_int->line)%bits_regiser)*step);
		ptr_ctr->EXTICR[(ext_int->line)/bits_regiser]=temp;

	}
	else {
		 ret= E_NOT_OK;
	}
	  MGPIO_SetPinValue(GPIO_PORTA,PIN3,VALUE_HIGH);
	return ret;
}
/** @brief Configure port selection for external interrupt
 *  @param ext_int Pointer to external_interrupt struct
 *  @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType enable_external_int(external_interupt *ext_int){
	u8 ret= E_OK;
	if(ext_int->line==19 ||ext_int->line==20)
	{
		 ret= E_NOT_OK;
	}
	else if((NULL != ext_int) && (ext_int->line >=0 && ext_int->line <=22))
	{

		ptr->IMR |= (1<<(ext_int->line));

	}
	else {
		 ret= E_NOT_OK;
	}
	MGPIO_SetPinValue(GPIO_PORTA,PIN3,VALUE_HIGH);

	return ret;
}
Std_ReturnType disable_external_int(external_interupt *ext_int){
	u8 ret= E_OK;
	if(ext_int->line==19 ||ext_int->line==20)
	{
		 ret= E_NOT_OK;
	}
	else if((NULL != ext_int) && (ext_int->line >=0 && ext_int->line <=22))
	{
		ptr->IMR &=~(1<<(ext_int->line));
	}
	else {
		 ret= E_NOT_OK;
	}
	  MGPIO_SetPinValue(GPIO_PORTA,PIN3,VALUE_HIGH);
	return ret;
}
/* @brief Configure port selection for externalevent
 *  @param ext_int Pointer to external_interrupt struct
 *  @return Status of the function
 *          (E_OK) : The function executed successfully
 *          (E_NOT_OK) : The function encountered an issue
 */
Std_ReturnType enable_external_event(external_interupt *ext_int){
	u8 ret= E_OK;
	if(ext_int->line==19 ||ext_int->line==20)
	{
		 ret= E_NOT_OK;
	}
	else if((NULL != ext_int) && (ext_int->line >=0 && ext_int->line <=22))
	{


		ptr->EMR |= (1<<(ext_int->line));



	}
	else {
		u8 ret= E_NOT_OK;
	}
	return ret;
}
Std_ReturnType disable_external_event(external_interupt *ext_int){
	u8 ret= E_OK;
	if(ext_int->line==19 ||ext_int->line==20)
	{
		 ret= E_NOT_OK;
	}
	else if((NULL != ext_int) && (ext_int->line >=0 && ext_int->line <=22))
	{
		ptr->EMR &=~(1<<(ext_int->line));

	}
	else {
		 ret= E_NOT_OK;
	}
	return ret;
}
Std_ReturnType clear_pending(EXTI_Line line){
	u8 ret= E_OK;
	if(line==19 ||line==20)
	{
		 ret= E_NOT_OK;
	}
	else if( (line >=0 && line <=22))
	{
		ptr->PR |= (1<<(line));
	}
	else {
		 ret= E_NOT_OK;
	}
	return ret;
}

Std_ReturnType configure_triger(external_interupt *ext_int){
	u8 ret= E_OK;
	if((NULL != ext_int) &&( (ext_int->triger == Rising) ||(ext_int->triger == falling) || (ext_int->triger == change) ))
	{
		switch(ext_int->triger){
		case Rising:
	    ptr->RTSR |=(1<<(ext_int->line));
		ptr->FTSR &=~(1<<(ext_int->line));
		break;
		case falling:
		ptr->FTSR |=(1<<(ext_int->line));
		ptr->RTSR &=~(1<<(ext_int->line));
		break;
		case change:
		ptr->RTSR |=(1<<(ext_int->line));
		ptr->FTSR |=(1<<(ext_int->line));
		break;
		}
	}
	else {
		 ret= E_NOT_OK;
	}
	  MGPIO_SetPinValue(GPIO_PORTA,PIN3,VALUE_HIGH);

	return ret;
}
Std_ReturnType ISR_function(external_interupt *ext_int){
	u8 ret= E_OK;
	if(NULL != ext_int){
    switch(ext_int->line){
    case EXTERNAL_LINE_PORT0:  ptr_ISR[0] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT1:  ptr_ISR[1] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT2:  ptr_ISR[2] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT3:  ptr_ISR[3] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT4:  ptr_ISR[4] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT5:  ptr_ISR[5] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT6:  ptr_ISR[6] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT7:  ptr_ISR[7] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT8:  ptr_ISR[8] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT9:  ptr_ISR[9] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT10: ptr_ISR[10] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT11: ptr_ISR[11] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT12: ptr_ISR[12] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT13: ptr_ISR[13] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT14: ptr_ISR[14] = ext_int->pt; break;
    case EXTERNAL_LINE_PORT15: ptr_ISR[15] = ext_int->pt; break;
    case EXTI_LINE_PVD_OUTPUT: ptr_ISR[16] = ext_int->pt; break;
    case EXTI_LINE_RTC_ALARM:  ptr_ISR[17] = ext_int->pt; break;
    case EXTI_LINE_USB_WAKEUP: ptr_ISR[18] = ext_int->pt; break;
    case EXTI_LINE_RTC_TAMPER_TIMESTAMP: ptr_ISR[19] = ext_int->pt; break;
    case EXTI_LINE_RTC_WAKEUP: ptr_ISR[20] = ext_int->pt; break;
    default:ret= E_NOT_OK;break;
    }
	}
	else {
		 ret= E_NOT_OK;
	}
	return ret;
}
/*
void EXTI0_IRQHandler(void)
{
    (ptr_ISR[0])();
	clear_pending(EXTERNAL_LINE_PORT0);

}

void EXTI1_IRQHandler(void)
{
	 (ptr_ISR[1])();
	clear_pending(EXTERNAL_LINE_PORT1);
}

void EXTI2_IRQHandler(void)
{
	 (ptr_ISR[2])();
	clear_pending(EXTERNAL_LINE_PORT2);
}

void EXTI3_IRQHandler(void)
{
	 (ptr_ISR[3])();
	clear_pending(EXTERNAL_LINE_PORT3);
}
*/
void EXTI4_IRQHandler(void)
{
    ptr_ISR[4]();
	clear_pending(EXTERNAL_LINE_PORT4);

}

/*
void EXTI9_5_IRQHandler(void)
{
	if(ptr_ISR[5]!=NULL)
	{
		ptr_ISR[5]();
		clear_pending(EXTERNAL_LINE_PORT5);
	}
	if(ptr_ISR[6]!=NULL)
	{
		ptr_ISR[6]();
		clear_pending(EXTERNAL_LINE_PORT6);
	}
	else if(ptr_ISR[7]!=NULL)
	{
		ptr_ISR[7]();
		clear_pending(EXTERNAL_LINE_PORT7);
	}
	else if(ptr_ISR[8]!=NULL)
	{
		ptr_ISR[8]();
		clear_pending(EXTERNAL_LINE_PORT8);
	}
	else if(ptr_ISR[9]!=NULL)
	{
		ptr_ISR[9]();
		clear_pending(EXTERNAL_LINE_PORT9);
	}
	else
	{
		/*do nothing*/
	/*}

}
void EXTI15_10_IRQHandler(void)
{
	if(ptr_ISR[10]!=NULL)
	{
		ptr_ISR[10]();
		clear_pending(EXTERNAL_LINE_PORT10);
	}
	else if(ptr_ISR[11]!=NULL)
	{
		ptr_ISR[11]();
		clear_pending(EXTERNAL_LINE_PORT11);
	}
	else if(ptr_ISR[12]!=NULL)
	{
		ptr_ISR[12]();
		clear_pending(EXTERNAL_LINE_PORT12);
	}
	else if(ptr_ISR[13]!=NULL)
	{
		ptr_ISR[13]();
		clear_pending(EXTERNAL_LINE_PORT13);
	}
	else if(ptr_ISR[14]!=NULL)
	{
		ptr_ISR[14]();
		clear_pending(EXTERNAL_LINE_PORT14);
	}
	else if(ptr_ISR[15]!=NULL)
	{
		ptr_ISR[15]();
		clear_pending(EXTERNAL_LINE_PORT15);
	}
	else
	{

	//}

//}

void PVD_IRQHandler(void)
{
    (ptr_ISR[16])();
}

void RTC_Alarm_IRQHandler(void)
{
    (ptr_ISR[17])();
}

void OTG_FS_WKUP_IRQHandler(void)
{
    (ptr_ISR[18])();
}

void TAMP_STAMP_IRQHandler(void)
{
    (ptr_ISR[19])();
}

void RTC_WKUP_IRQHandler(void)
{
    (ptr_ISR[20])();
}


*/
