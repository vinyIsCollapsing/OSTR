/*
 * delay.h
 *
 *  Created on: Nov 29, 2024
 *      Author: vinic
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "stm32f0xx.h"

/*
 * Software counting delays
 */

void BSP_DELAY_ms	(uint32_t delay);
void BSP_DELAY_us	(uint32_t delay);

#endif /* INC_DELAY_H_ */
