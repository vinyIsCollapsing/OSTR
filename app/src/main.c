#include "main.h"

// Static functions
static void SystemClock_Config(void);
void vApplicationMallocFailedHook(void);

// FreeRTOS tasks
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

// FreeRTOS task handles
xTaskHandle vTask1_handle;
xTaskHandle vTask2_handle;

// Kernel objects
xSemaphoreHandle xSem;

// Main function
int main()
{
	uint32_t	free_heap_size;

	// Configure System Clock
	SystemClock_Config();

	// Initialize LED pin
	BSP_LED_Init();

	// Initialize the user Push-Button
	BSP_PB_Init();

    // Initialize NVIC
    BSP_NVIC_Init();

    myPrintfInit();
	// Initialize Debug Console
	BSP_Console_Init();
	// my_printf("Console Ready!\r\n");


	// Start Trace Recording
	xTraceEnable(TRC_START);		// xTraceEnable(TRC_START);



	// Create Semaphore
	// my_printf("\r\nNow creating Binary Semaphore...\r\n");
    xSem = xSemaphoreCreateBinary();
    vTraceSetSemaphoreName(xSem, "xSem");
    // xSem2 = xSemaphoreCreateBinary();
    // vTraceSetSemaphoreName(xSem2, "xSem2");

	// Report Free Heap Size
	free_heap_size = xPortGetFreeHeapSize();
	// my_printf("Free Heap Size is %d bytes\r\n", free_heap_size);

	// Create Tasks
	// my_printf("Creating Tasks...");
    xTaskCreate(vTask1, "Task_1", 128, NULL, 1, &vTask1_handle);
    xTaskCreate(vTask2, "Task_2", 128, NULL, 1, &vTask2_handle);
    //vTaskPubInit();
    writeTaskInit();
	// my_printf("OK\r\n");

	// Report Free Heap Size
	free_heap_size = xPortGetFreeHeapSize();
	// my_printf("Free Heap Size is %d bytes\r\n", free_heap_size);

	// Start the Scheduler
	// my_printf("Now Starting Scheduler...\r\n");
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

/*
 * Task_1
 */
void vTask1(void *pvParameters) {
	command_message_t msgTask1;

    while (1) {
    	// vTask1_Pub();

    	my_sprintf((char *) msgTask1, "Arthour ! Pas changer assiette pour fromage !\r\n");
    	sendMessage(&msgTask1);
		vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

/*
 * Task_2
 */
void vTask2(void *pvParameters) {
	command_message_t msgTask2;

    while(1){
    	// vTask2_Pub();

    	my_sprintf((char *) msgTask2, "Arthour ! Couhillere !\r\n");
    	sendMessage(&msgTask2);
    	vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

/*
 * Hook function for malloc failure
 */
void vApplicationMallocFailedHook() {
    while (1);
}

/*
 * Assertion Handler
 */
void vAssertCalled( char *file, int line )
{
	taskDISABLE_INTERRUPTS();

	my_printf("Assertion Failed\r\n");
	my_printf("File %s\r\n", file);
	my_printf("Line %d\r\n", line);

	while(1);
}

/*
 * Malloc failed Basic Hook
void vApplicationMallocFailedHook()
{
	my_printf("Malloc Failed\r\n");

	while(1);
}
 */

/*
 * Stack Overflow Basic Hook
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName)
{
	while(1);
}

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
