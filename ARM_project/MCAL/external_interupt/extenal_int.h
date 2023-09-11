/*
 * extenal_int.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Dell
 */

#ifndef EXTERNAL_INTERUPT_EXTENAL_INT_H_
#define EXTERNAL_INTERUPT_EXTENAL_INT_H_
#include "../../Common/std_types.h"
#include "../../common/bit_math.h"
typedef enum {
    EXTERNAL_LINE_PORT0=0,
    EXTERNAL_LINE_PORT1,
    EXTERNAL_LINE_PORT2,
    EXTERNAL_LINE_PORT3,
    EXTERNAL_LINE_PORT4,
    EXTERNAL_LINE_PORT5,
    EXTERNAL_LINE_PORT6,
    EXTERNAL_LINE_PORT7,
    EXTERNAL_LINE_PORT8,
    EXTERNAL_LINE_PORT9,
    EXTERNAL_LINE_PORT10,
    EXTERNAL_LINE_PORT11,
    EXTERNAL_LINE_PORT12,
    EXTERNAL_LINE_PORT13,
    EXTERNAL_LINE_PORT14,
    EXTERNAL_LINE_PORT15,
    EXTI_LINE_PVD_OUTPUT,
    EXTI_LINE_RTC_ALARM,
    EXTI_LINE_USB_WAKEUP,
    EXTI_LINE_RTC_TAMPER_TIMESTAMP=21,
    EXTI_LINE_RTC_WAKEUP=22
} EXTI_Line;
typedef enum{
	masked,
	not_masked
}maskable_t;
typedef enum{
	Rising,
	falling,
	change
}triger_t;
typedef enum{
	portA,
	portB,
	portC,
	portD,
	portE,
	portH
}port_t;
typedef struct {
	EXTI_Line line;
	triger_t triger;
	port_t port;
	void (*pt)(void);
}external_interupt;

Std_ReturnType port_selection_configure(external_interupt *ext_int);
Std_ReturnType enable_external_int(external_interupt *ext_int);
Std_ReturnType disable_external_int(external_interupt *ext_int);
Std_ReturnType enable_external_event(external_interupt *ext_int);
Std_ReturnType disable_external_event(external_interupt *ext_int);
Std_ReturnType configure_triger(external_interupt *ext_int);
Std_ReturnType ISR_function(external_interupt *ext_int);
Std_ReturnType clear_pending(EXTI_Line line);





#endif /* EXTERNAL_INTERUPT_EXTENAL_INT_H_ */
