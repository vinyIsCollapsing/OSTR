/**
  ******************************************************************************
  * @file    Templates/Src/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"


/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
// void SVC_Handler(void)
// {
// }

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
// void PendSV_Handler(void)
// {
// }

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
// void SysTick_Handler(void)
// {
//   //HAL_IncTick();
// }

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * This function handles EXTI line 13 interrupt request.
  */
extern xSemaphoreHandle xSem;

void EXTI4_15_IRQHandler()
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	// Test for line 13 pending interrupt
	if ((EXTI->PR & EXTI_PR_PR13_Msk) != 0)
	{
		// Clear pending bit 13 by writing a '1'
		EXTI->PR = EXTI_PR_PR13;

		// Release the semaphore
		xSemaphoreGiveFromISR(xSem, &xHigherPriorityTaskWoken);

	    // Perform a context switch to the waiting task
	    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
	}
}

/*
 * BSP_NVIC_Init()
 * Setup NVIC controller for desired interrupts
 */
/*
 * BSP_NVIC_Init()
 * Setup NVIC controller for desired interrupts
 */
void BSP_NVIC_Init()
{
	// Set maximum priority for EXTI line 4 to 15 interrupts
	NVIC_SetPriority(EXTI4_15_IRQn,
			configMAX_API_CALL_INTERRUPT_PRIORITY + 1);

	// Enable EXTI line 4 to 15 (user button on line 13) interrupts
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}



/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 

/**
  * @}
  */
