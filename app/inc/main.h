/*
 * main.h
 *
 *  Created on: Nov 19, 2024
 *      Author: vinic
 */

#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_

// Device header
#include "stm32f0xx.h"
// BSP functions
#include "bsp.h"
// FreeRTOS headers
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "stream_buffer.h"

#include "readTask.h"
#include "writeTask.h"

/*
 * printf() and sprintf() from printf-stdarg.c
 */
// Global functions
int my_printf	(const char *format, ...);
int my_sprintf	(char *out, const char *format, ...);

#endif /* APP_INC_MAIN_H_ */
