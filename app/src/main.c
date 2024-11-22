#include "stm32f0xx.h"
#include "bsp.h"
#include "main.h"

// Static functions
static void SystemClock_Config (void);

// FreeRTOS tasks
void vTask1 	(void *pvParameters);
void vTask2 	(void *pvParameters);
// Kernel objects
xSemaphoreHandle xSem;

BaseType_t xTaskCreate ( TaskFunction_t               pxTaskCode,
                         const char * const           pcName,
                         const configSTACK_DEPTH_TYPE usStackDepth,
                         void * const                 pvParameters,
                         UBaseType_t                  uxPriority,
                         TaskHandle_t * const         pxCreatedTask );

// Main function
int main()
{
	// Configure System Clock
	SystemClock_Config();

	// Initialize LED & Button pin
	BSP_LED_Init();
	BSP_PB_Init();

	// Initialize Debug Console
	BSP_Console_Init();
	my_printf("Console ready!\r\n");

	// Start Trace Recording
	xTraceEnable(TRC_START);
	// Create Semaphore object (this is not a 'give')
	xSem = xSemaphoreCreateBinary();
	// Give a nice name to the Semaphore in the trace recorder
	vTraceSetSemaphoreName(xSem, "xSEM");
	// Create Tasks
	xTaskCreate(vTask1, "Task_1", 256, NULL, 2, NULL);
	xTaskCreate(vTask2, "Task_2", 256, NULL, 1, NULL);
	// Start the Scheduler
	vTaskStartScheduler();

	while(1)
	{
		// The program should never be here...
	}
}

/*
 * Clock configuration for the Nucleo STM32F072RB board
 * HSE input Bypass Mode            -> 8MHz
 * SYSCLK, AHB, APB1                -> 48MHz
 * PA8 as MCO with /16 prescaler    -> 3MHz
 */

static void SystemClock_Config()
{
	uint32_t	HSE_Status;
	uint32_t	PLL_Status;
	uint32_t	SW_Status;
	uint32_t	timeout = 0;
	timeout = 1000000;

	// Start HSE in Bypass Mode
	RCC->CR |= RCC_CR_HSEBYP;
	RCC->CR |= RCC_CR_HSEON;

	// Wait until HSE is ready
	do
	{
		HSE_Status = RCC->CR & RCC_CR_HSERDY_Msk;
		timeout--;
	} while ((HSE_Status == 0) && (timeout > 0));

	// Select HSE as PLL input source
	RCC->CFGR &= ~RCC_CFGR_PLLSRC_Msk;
	RCC->CFGR |= (0x02 <<RCC_CFGR_PLLSRC_Pos);

	// Set PLL PREDIV to /1
	RCC->CFGR2 = 0x00000000;

	// Set PLL MUL to x6
	RCC->CFGR &= ~RCC_CFGR_PLLMUL_Msk;
	RCC->CFGR |= (0x04 <<RCC_CFGR_PLLMUL_Pos);

	// Enable the main PLL
	RCC-> CR |= RCC_CR_PLLON;
	// Wait until PLL is ready
	do
	{
		PLL_Status = RCC->CR & RCC_CR_PLLRDY_Msk;
		timeout--;
	} while ((PLL_Status == 0) && (timeout > 0));

	// Set AHB prescaler to /1
	RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	//Set APB1 prescaler to /1
	RCC->CFGR &= ~RCC_CFGR_PPRE_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE_DIV1;

	// Enable FLASH Prefetch Buffer and set Flash Latency
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

	// Select the main PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait until PLL becomes main switch input
	do
	{
		SW_Status = (RCC->CFGR & RCC_CFGR_SWS_Msk);
		timeout--;
	} while ((SW_Status != RCC_CFGR_SWS_PLL) && (timeout > 0));

	// Update SystemCoreClock global variable
	SystemCoreClockUpdate();
}

/*
 *	Task_1
 *
 *	- Prints current time (OS tick) every 1s
 *	- Using precise period delay
 */
void vTask1 (void *pvParameters)
{
	portTickType	now, xLastWakeTime;
	uint16_t		n = 0;
	// Initialize timing
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		n++;
		now = xTaskGetTickCount();
		my_printf("\r\n Task_1 #%2d @tick = %6d ", n, now);
		// Wait here for 1s since last wake-up
		vTaskDelayUntil (&xLastWakeTime, (1000/portTICK_RATE_MS));
	}
}

/*
 *	Task_2
 *
 *	- Toggles LED and prints '.' every 100ms
 *	- Internal (blocking) loop if button is pressed
 */
void vTask2 (void *pvParameters)
{
	while(1)
	{
		// Loop here if button is pressed
		while(BSP_PB_GetState()==1);
		// Otherwise toggle LED and suspend task for 100ms
		BSP_LED_Toggle();
		my_printf(".");
		vTaskDelay(100);
	}
}
