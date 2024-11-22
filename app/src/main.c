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
// Trace User Events Channels
traceString ue1, ue2;
// Kernel Objects
xSemaphoreHandle xConsoleMutex;

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

	// Register the Trace User Event Channels
	 ue1 = xTraceRegisterString("count");
	 ue2 = xTraceRegisterString("msg");

	// Create a Mutex for accessing the console
	xConsoleMutex = xSemaphoreCreateMutex();

	// Give a nice name to the Mutex in the trace recorder
	vTraceSetMutexName(xConsoleMutex, "Console Mutex");

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
 */
void vTask1 (void *pvParameters)
{
	while(1)
	{
		// Take Mutex
		xSemaphoreTake(xConsoleMutex, portMAX_DELAY);

		// Send message to console
		my_printf("With great power comes great responsibility\r\n");

		// Release Mutex
		xSemaphoreGive(xConsoleMutex);

		vTaskDelay(20);
	}
}

/*
 *	Task_2
 */
void vTask2 (void *pvParameters)
{
	while(1)
	{
		// Take Mutex
		xSemaphoreTake(xConsoleMutex, portMAX_DELAY);

		// Send message to console
		my_printf("#");

		// Release Mutex
		xSemaphoreGive(xConsoleMutex);

		vTaskDelay(1);
	}
}
