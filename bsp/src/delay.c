/*
 * delay.c
 *
 *  Created on: Nov 29, 2024
 *      Author: vinic
 */


#include "delay.h"

/*
 *  Basic delay functions
 */

void BSP_DELAY_ms(uint32_t delay)
{
	uint32_t	i;
	for(i=0; i<(delay*2500); i++);		// Tuned for ms at 48MHz
}

void BSP_DELAY_us(uint32_t delay)
{
	uint32_t	i;
	for(i=0; i<(delay*3); i++);		// Tuned for µs at 48MHz
}
