/*
 * GPIO_APP.c
 *
 *  Created on: Aug 10, 2023
 *      Author: Adel
 */

#include "GPIO.h"

/****************************************REGISTERS***********************************************************/
/*
1-BSAE ADD
2-REGISTER STRUCT
3-POINTER
*/
#define GPIOA_BASEADDRESS	0x40020000
#define GPIOB_BASEADDRESS   0x40020400
#define GPIOC_BASEADDRESS   0x40020800


typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDER;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIO_t;

/*
static volatile GPIO_t * const GPIOA_ptr = (volatile GPIO_t * const) GPIOA_BASEADDRESS;
static volatile GPIO_t * const GPIOB_ptr = (volatile GPIO_t * const) GPIOB_BASEADDRESS;
static volatile GPIO_t * const GPIOC_ptr = (volatile GPIO_t * const) GPIOC_BASEADDRESS;
*/
#define  	   	GPIOA      ((volatile GPIO_t*)GPIOA_BASEADDRESS)
#define  	   	GPIOB      ((volatile GPIO_t*)GPIOB_BASEADDRESS)
#define  	   	GPIOC      ((volatile GPIO_t*)GPIOC_BASEADDRESS)




/***************************************FUNCTION************************************************************/



ret_t MGPIO_SetPinMode(u32 GPIO_PORT,u32 PIN,u32 Mode)
{
	if((PIN>=0)&&(PIN<=15)&&(Mode>=0)&&(Mode<=3))
	{
		switch(GPIO_PORT)
		{
		case GPIO_PORTA: GPIOA->MODER &= ~(3<<(PIN*2)); GPIOA->MODER |= (Mode<<(PIN*2)); break;
		case GPIO_PORTB: GPIOB->MODER &= ~(3<<(PIN*2)); GPIOB->MODER |= (Mode<<(PIN*2)); break;
		case GPIO_PORTC: GPIOC->MODER &= ~(3<<(PIN*2)); GPIOC->MODER |= (Mode<<(PIN*2)); break;
		default : return ret_Error;
		}
	}
	return ret_OK;
}

ret_t MGPIO_SetPinType(u32 GPIO_PORT,u32 PIN,u32 Type)
{
	if((PIN>=0)&&(PIN<=15)&&(Type>=0)&&(Type<=1))
	{
		switch(GPIO_PORT)
		{
		case GPIO_PORTA: GPIOA->OTYPER &= ~(1<<(PIN)); GPIOA->OTYPER |= (Type<<(PIN)); break;
		case GPIO_PORTB: GPIOB->OTYPER &= ~(1<<(PIN)); GPIOB->OTYPER |= (Type<<(PIN)); break;
		case GPIO_PORTC: GPIOC->OTYPER &= ~(1<<(PIN)); GPIOC->OTYPER |= (Type<<(PIN)); break;

		}
	return ret_OK;
	}
	else{
		return ret_Error;
	}
}
ret_t MGPIO_SetPinValue(u32 GPIO_PORT,u32 PIN,u32 VALUE)
{
	if((PIN>=0)&&(PIN<=15)&&(VALUE>=0)&&(VALUE<=1))
	{
		switch(GPIO_PORT)
		{
		case GPIO_PORTA: GPIOA->ODR &= ~(1<<(PIN)); GPIOA->ODR |= (VALUE<<(PIN)); break;
		case GPIO_PORTB: GPIOB->ODR &= ~(1<<(PIN)); GPIOB->ODR |= (VALUE<<(PIN)); break;
		case GPIO_PORTC: GPIOC->ODR &= ~(1<<(PIN)); GPIOC->ODR |= (VALUE<<(PIN)); break;
	}
	return ret_OK;
	}
	else{
		return ret_Error;
	}
}
ret_t MGPIO_SetPinSpeed(u32 GPIO_PORT,u32 PIN,u32 Speed)
{
	if((PIN>=0)&&(PIN<=15)&&(Speed>=0)&&(Speed<=3))
	{
		switch(GPIO_PORT)
		{
		case GPIO_PORTA: GPIOA->OSPEEDER &= ~(3<<(PIN*2)); GPIOA->OSPEEDER |= (Speed<<(PIN*2)); break;
		case GPIO_PORTB: GPIOB->OSPEEDER &= ~(3<<(PIN*2)); GPIOB->OSPEEDER |= (Speed<<(PIN*2)); break;
		case GPIO_PORTC: GPIOC->OSPEEDER &= ~(3<<(PIN*2)); GPIOC->OSPEEDER |= (Speed<<(PIN*2)); break;
		default : return ret_Error;
		}
	}
	return ret_OK;
}

ret_t MGPIO_SetPinPUPDR(u32 GPIO_PORT,u32 PIN,u32 PUPDR)
{
	if((PIN>=0)&&(PIN<=15)&&(PUPDR>=0)&&(PUPDR<=2))
	{
		switch(GPIO_PORT)
		{
		case GPIO_PORTA: GPIOA->PUPDR &= ~(3<<(PIN*2)); GPIOA->PUPDR |= (PUPDR<<(PIN*2)); break;
		case GPIO_PORTB: GPIOB->PUPDR &= ~(3<<(PIN*2)); GPIOB->PUPDR |= (PUPDR<<(PIN*2)); break;
		case GPIO_PORTC: GPIOC->PUPDR &= ~(3<<(PIN*2)); GPIOC->PUPDR |= (PUPDR<<(PIN*2)); break;
		default : return ret_Error;
		}
	}
	return ret_OK;
}

ret_t MGPIO_SetPinAtomicValue(u32 GPIO_PORT,u32 PIN,u32 VALUE)
{
	if((PIN>=0)&&(PIN<=PIN15)&&(VALUE>=0)&&(VALUE<=VALUE_HIGH))
	{
		if(VALUE==VALUE_HIGH)//write on low part in the register
		{
			switch(GPIO_PORT)
			{
			case GPIO_PORTA: GPIOA->BSRR = (1<<PIN);break;
			case GPIO_PORTB: GPIOB->BSRR = (1<<PIN);break;
			case GPIO_PORTC: GPIOC->BSRR = (1<<PIN);break;
			}
		}
		if(VALUE==VALUE_LOW)//write on high part of the register
		{
			switch(GPIO_PORT)
			{
			case GPIO_PORTA: GPIOA->BSRR = (1<<(PIN+16));break;
			case GPIO_PORTB: GPIOB->BSRR = (1<<PIN<<16);break;
			case GPIO_PORTC: GPIOC->BSRR = (1<<PIN<<16);break;
			}
		}return ret_OK;
	}
	else{
		return ret_Error;
	}
}
ret_t MGPIO_SetPinsAtomicValue(u32 GPIO_PORT,u32 numbers,u32 VALUE)
{
	if((VALUE>=0)&&(VALUE<=VALUE_HIGH))
	{
		if(VALUE==VALUE_HIGH)//write on low part in the register
		{
			switch(GPIO_PORT)
			{
	        case GPIO_PORTA: (GPIOA->BSRR) =(numbers);break;
	        case GPIO_PORTB: (GPIOA->BSRR) =(numbers);break;
	        case GPIO_PORTC: (GPIOA->BSRR) =(numbers);break;

			}
		}
		if(VALUE==VALUE_LOW)//write on high part of the register
		{
			switch(GPIO_PORT)
			{
			case GPIO_PORTA: GPIOA->BSRR = (numbers<<(16));break;
			case GPIO_PORTB: GPIOB->BSRR = (numbers<<16);break;
			case GPIO_PORTC: GPIOC->BSRR = (numbers<<16);break;
			}
		}return ret_OK;
	}
	else{
		return ret_Error;
	}
}
ret_t MGPIO_SetPinsValue(u32 GPIO_PORT,u32 PIN)
{

		switch(GPIO_PORT)
		{
		case GPIO_PORTA: GPIOA->ODR =PIN ; break;
		case GPIO_PORTB: GPIOB->ODR =PIN; break;
		case GPIO_PORTC: GPIOC->ODR =PIN ; break;


		}return ret_OK;
}
ret_t MGPIO_Setalternate_function(u32 GPIO_PORT,u32 GPIO_PIN,u32 GPIO_AF){
	if(GPIO_PORT>=0 && GPIO_PORT<=2 && GPIO_AF>=0 && GPIO_AF<=15)
		{
			if(GPIO_PIN>=0 && GPIO_PIN<=7)
			{
				switch(GPIO_PORT)
				{
				case GPIO_PORTA: GPIOA->AFRL &= ~(0xF<<GPIO_PIN*4); GPIOA->AFRL |= (GPIO_AF<<GPIO_PIN*4); break;
				case GPIO_PORTB: GPIOB->AFRL &= ~(0xF<<GPIO_PIN*4); GPIOB->AFRL |= (GPIO_AF<<GPIO_PIN*4); break;
				case GPIO_PORTC: GPIOC->AFRL &= ~(0xF<<GPIO_PIN*4); GPIOC->AFRL |= (GPIO_AF<<GPIO_PIN*4); break;
				}
			}
			else if(GPIO_PIN>=8 && GPIO_PIN<=15)
			{
				switch(GPIO_PORT)
				{
				case GPIO_PORTA: GPIOA->AFRH &= ~(0xF<<(GPIO_PIN-8)*4); GPIOA->AFRH |= (GPIO_AF<<(GPIO_PIN-8)*4); break;
				case GPIO_PORTB: GPIOB->AFRH &= ~(0xF<<(GPIO_PIN-8)*4); GPIOB->AFRH |= (GPIO_AF<<(GPIO_PIN-8)*4); break;
				case GPIO_PORTC: GPIOC->AFRH &= ~(0xF<<(GPIO_PIN-8)*4); GPIOC->AFRH |= (GPIO_AF<<(GPIO_PIN-8)*4); break;
				}
			}
			else
			{
				return ret_Error;
			}
		}
		return ret_OK;
}

