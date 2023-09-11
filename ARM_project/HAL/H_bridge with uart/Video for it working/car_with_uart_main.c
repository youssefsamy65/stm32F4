#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/uart/uart.h"
#include "../../HAL/car/car.h"
motor_t motor = {
    .gpio = GPIO_PORTA,
    .pin = {PIN0, PIN1, PIN2, PIN3}
};
int main(){
	RCC_Enable_periClk(peri_AHB1_GPIOA,AHB1);

		RCC_Enable_periClk(peri_APB2_USART1,APB2);
	motor_init(&motor);


   	MGPIO_SetPinMode(GPIO_PORTA,PIN9,Mode_AF);
	MGPIO_SetPinMode(GPIO_PORTA,PIN10,Mode_AF);
	MGPIO_Setalternate_function(GPIO_PORTA,PIN9,AF7);
	MGPIO_Setalternate_function(GPIO_PORTA,PIN10,AF7);
usart_int(usart_1);
while(1){
	u8 x =usart_recive_byte(usart_1);
	motor_forward(&motor);
if(x=='f'){
		motor_forward(&motor);
	}
	else if(x=='b'){
		motor_backword(&motor);
	}
	else if(x=='l'){
		motor_left(&motor);
	}
	else if(x=='r'){
		motor_right(&motor);
	}
	else if(x=='s'){
			motor_stop(&motor);
		}
	else{
		motor_stop(&motor);
	}
}


return 0;
}
