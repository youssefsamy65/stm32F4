#include "../HAL/seven_seg/seven_seg.h"

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"



u8 ret=1;
u8 number=7;

int main()
{
  // At this stage the system clock should have already been configured
  // at high speed.
	Enable_periClk(peri_AHB1_GPIOA,AHB1);
	Enable_periClk(peri_AHB1_GPIOB,AHB1);

    sevent_seg test = {
        .port = GPIO_PORTA,
        .pins = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6},
        .type= SEGMENT_COMMON_ANODE
    };
    sevent_seg test_2 = {
        .port = GPIO_PORTB,
        .pins = {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6},
        .type= SEGMENT_COMMON_CATHODE
    };
     ret&=seven_seg_init(&test);
     ret&=seven_seg_init(&test_2);

    while (1)
    {
	if( number<10 ){
		 ret&=	seven_seg_write(&test,number);
		 ret&=	seven_seg_stop(&test_2);
	}
	else if( number>=10 ){
		 ret&=	seven_seg_write(&test,(number/10));
		 ret&=	seven_seg_write(&test_2,(number%10));
	}

    }
}


// ----------------------------------------------------------------------------
