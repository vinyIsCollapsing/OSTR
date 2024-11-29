/*
 * FreeRTOSConfig.h
 *
 *  Created on: Nov 19, 2024
 *      Author: vinic
 */

#ifndef INC_FREERTOSCONFIG_H_
#define INC_FREERTOSCONFIG_H_

/*
 * Here is a good place to include header files that are
 * required across your application.
 */
#include "stm32f0xx.h"
extern uint32_t    SystemCoreClock;
#define configUSE_PREEMPTION                        1
#define configUSE_TICKLESS_IDLE                     0
#define configCPU_CLOCK_HZ                          ( SystemCoreClock )
#define configTICK_RATE_HZ                          ( ( TickType_t ) 100 )
#define configMAX_PRIORITIES                        5
#define configMINIMAL_STACK_SIZE                    ( ( uint16_t ) 128 )
#define configMAX_TASK_NAME_LEN                     16
#define configUSE_16_BIT_TICKS                      0
#define configIDLE_SHOULD_YIELD                     1
#define configUSE_TASK_NOTIFICATIONS                1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES       2
#define configUSE_MUTEXES                           1
#define configUSE_RECURSIVE_MUTEXES                 0
#define configUSE_COUNTING_SEMAPHORES               0
#define configQUEUE_REGISTRY_SIZE                   10
#define configUSE_QUEUE_SETS                        0
#define configUSE_TIME_SLICING                      0
#define configSTACK_DEPTH_TYPE                      uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE            size_t
#define configHEAP_CLEAR_MEMORY_ON_FREE             1
/* Memory allocation related definitions. */
#define configSUPPORT_STATIC_ALLOCATION             0
#define configSUPPORT_DYNAMIC_ALLOCATION            1
#define configKERNEL_PROVIDED_STATIC_MEMORY         0
#define configTOTAL_HEAP_SIZE                       ( ( size_t ) ( 7 * 1024 ) )
#define configAPPLICATION_ALLOCATED_HEAP            0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP   0
#define configENABLE_HEAP_PROTECTOR                 0
/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                         0
#define configUSE_TICK_HOOK                         0
#define configCHECK_FOR_STACK_OVERFLOW              1
#define configUSE_MALLOC_FAILED_HOOK                1
#define configUSE_DAEMON_TASK_STARTUP_HOOK          0
#define configUSE_SB_COMPLETED_CALLBACK             0
/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS               0
#define configUSE_TRACE_FACILITY                    1
#define configUSE_STATS_FORMATTING_FUNCTIONS        0
/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES                       0
#define configMAX_CO_ROUTINE_PRIORITIES             1
/* Software timer related definitions. */
#define configUSE_TIMERS                            1
#define configTIMER_TASK_PRIORITY                   3
#define configTIMER_QUEUE_LENGTH                    10
#define configTIMER_TASK_STACK_DEPTH                configMINIMAL_STACK_SIZE
/* Interrupt nesting behavior configuration. */
#define configMAX_API_CALL_INTERRUPT_PRIORITY       5
/* Define to trap errors during development. */
void vAssertCalled(char *file, int  line);
// #define configASSERT(x) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }
#define configASSERT(x) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )
/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                    0
#define INCLUDE_uxTaskPriorityGet                   0
#define INCLUDE_vTaskDelete                         0
#define INCLUDE_vTaskSuspend                        0
#define INCLUDE_xResumeFromISR                      0
#define INCLUDE_vTaskDelayUntil                     1
#define INCLUDE_vTaskDelay                          1
#define INCLUDE_xTaskGetSchedulerState              0
#define INCLUDE_xTaskGetCurrentTaskHandle           1
#define INCLUDE_uxTaskGetStackHighWaterMark         1
#define INCLUDE_uxTaskGetStackHighWaterMark2        0
#define INCLUDE_xTaskGetIdleTaskHandle              0
#define INCLUDE_eTaskGetState                       0
#define INCLUDE_xEventGroupSetBitFromISR            1
#define INCLUDE_xTimerPendFunctionCall              0
#define INCLUDE_xTaskAbortDelay                     0
#define INCLUDE_xTaskGetHandle                      0
#define INCLUDE_xTaskResumeFromISR                  0
/*
 * Definitions that map the FreeRTOS port interrupt handlers
 * to their CMSIS standard names
 */
#define vPortSVCHandler                             SVC_Handler
#define xPortPendSVHandler                          PendSV_Handler
#define xPortSysTickHandler                         SysTick_Handler
/* A header file that defines trace macro can be included here. */
/* Integrates the Tracealyzer recorder with FreeRTOS */
#if ( configUSE_TRACE_FACILITY == 1 )
#include "trcRecorder.h"
#endif

#endif /* INC_FREERTOSCONFIG_H_ */
