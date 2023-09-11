/*
 * seven_seg.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Dell
 */

#ifndef SEVEN_SEG_SEVEN_SEG_H_
#define SEVEN_SEG_SEVEN_SEG_H_

#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/RCC/RCC.h"



/************************************************ Section: Function Declarations *************************************/

typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;
typedef struct {
	u32 pins[7];
    u32 port;
    segment_type_t type;
}sevent_seg;


Std_ReturnType seven_seg_init(sevent_seg * sevent_segment );
Std_ReturnType seven_seg_write(sevent_seg * sevent_segment,u32 number);
Std_ReturnType seven_seg_stop(sevent_seg * sevent_segment);


#endif /* SEVEN_SEG_SEVEN_SEG_H_ */
