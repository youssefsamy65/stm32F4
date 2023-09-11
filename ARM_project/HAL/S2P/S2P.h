/*
 * S2P.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Dell
 */

#ifndef S2P_S2P_H_
#define S2P_S2P_H_

#include "../../Common/std_types.h"
#include "../../common/bit_math.h"
typedef struct{
	u8 D_port;
	u8 S_port;
	u8 ST_port;
	u8 D_pin;
	u8 S_pin;
	u8 ST_pin;
}sp_info;
void send_bit_asynch(sp_info*sp,u16 user_byte);

#endif /* S2P_S2P_H_ */
