#include "stm32f0xx.h"
#include "bsp.h"
#include "main.h"

// Define Event Group flags
#define	BIT0	( (EventBits_t)( 0x01 <<0) )   // This is not mandatory but it provides
#define BIT1	( (EventBits_t)( 0x01 <<1) )   // friendly alias for individual event

// Static functions
static void SystemClock_Config (void);

// FreeRTOS tasks
void vTask1 	(void *pvParameters);
void vTask2 	(void *pvParameters);
void vTaskHWM 	(void *pvParameters);

xTaskHandle	vTask1_handle;
xTaskHandle	vTask2_handle;
xTaskHandle 	vTaskHWM_handle;

// Timer callback function
// void vTaskTimer		(TimerHandle_t xTimer);
// Declare Timer Object
// TimerHandle_t	my_timer;
// TickType_t	ticks;

// Kernel objects
xSemaphoreHandle xSem;
xSemaphoreHandle xConsoleMutex;
xQueueHandle	 xConsoleQueue;
// EventGroupHandle_t myEventGroup;

// Trace User Events Channels
traceString ue1, ue2, ue3;

// Define the message_t type as an array of 60 char
typedef uint8_t message_t[64];		// typedef uint8_t msg_t[64];

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

	// Initialize Debug Console
	BSP_Console_Init();
	my_printf("Console Ready!\r\n");

	// Initialize NVIC
	//BSP_NVIC_Init();

	// Start Trace Recording
	vTraceEnable(TRC_START);		// xTraceEnable(TRC_START);

	// Report Free Heap Size
	free_heap_size = xPortGetFreeHeapSize();
	my_printf("\r\nFree Heap Size is %d bytes\r\n", free_heap_size);


	// Create Semaphore object (this is not a 'give')
	my_printf("\r\nNow creating Binary Semaphore...\r\n");
	xSem = xSemaphoreCreateBinary();
	vTraceSetSemaphoreName(xSem, "xSEM");
	free_heap_size = xPortGetFreeHeapSize();
	my_printf("Free Heap Size is %d bytes\r\n", free_heap_size);

	// Create Queue to hold console messages
	my_printf("\r\nNow creating Message Queue...\r\n");
	xConsoleQueue = xQueueCreate(4, sizeof(message_t));
	vTraceSetQueueName(xConsoleQueue, "Console Queue");
	free_heap_size = xPortGetFreeHeapSize();
	my_printf("Free Heap Size is %d bytes\r\n", free_heap_size);

	// Create a Mutex for accessing the console
	my_printf("\r\nNow creating Mutex...\r\n");
	xConsoleMutex = xSemaphoreCreateMutex();
	vTraceSetMutexName(xConsoleMutex, "Console Mutex");
	free_heap_size = xPortGetFreeHeapSize();
	my_printf("Free Heap Size is %d bytes\r\n", free_heap_size);

	// Register the Trace User Event Channels
	my_printf("\r\nNow registering Trace events...\r\n");
	ue1 = xTraceRegisterString("ticks");
	ue2 = xTraceRegisterString("msg");
	ue3 = xTraceRegisterString("HWM");
	free_heap_size = xPortGetFreeHeapSize();
	my_printf("Free Heap Size is %d bytes\r\n", free_heap_size);

	// Create Tasks
	my_printf("\r\nNow creating Tasks...\r\n");
	xTaskCreate(vTask1,	"Task_1",	128, NULL, 2, &vTask1_handle);
	xTaskCreate(vTask2,	"Task_2",	128, NULL, 3, &vTask2_handle);
	xTaskCreate(vTaskHWM,	"Task_HWM",	128, NULL, 1, &vTaskHWM_handle);
	free_heap_size = xPortGetFreeHeapSize();
	my_printf("Free Heap Size is %d bytes\r\n", free_heap_size);

	// Create Event Group                   // <-- Create Event Group here
	// myEventGroup = xEventGroupCreate();

	// Create Timer object
	// my_timer = xTimerCreate("my_timer", 200, pdTRUE, NULL, vTaskTimer);
	// Start Timer
	// xTimerStart(my_timer, 0);
	// ticks = xTimerGetExpiryTime(my_timer);
	// Register the Trace User Event Channels
	// ue1 = xTraceRegisterString("ticks");

	// Create Semaphore object
	//xSem = xSemaphoreCreateBinary();

	// Give a nice name to the Semaphore in the trace recorder
	//vTraceSetSemaphoreName(xSem, "xSEM");

	// Create Tasks
	// xTaskCreate(vTask1,		"Task_1", 		256, NULL, 1, NULL);
	// xTaskCreate(vTask2,		"Task_2", 		256, NULL, 2, NULL);

	// Register the Trace User Event Channels
	// ue1 = xTraceRegisterString("count");
	// ue2 = xTraceRegisterString("msg");

	// Create Queue to hold console messages
	// xConsoleQueue = xQueueCreate(4, sizeof(msg_t *));

	// Give a nice name to the Queue in the trace recorder
	// vTraceSetQueueName(xConsoleQueue, "Console Queue");

	// Start the Scheduler
	my_printf("\r\nNow Starting Scheduler...\r\n");
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
	uint8_t	msg[] = "This is task_1 message"; // 22 bytes string

	while(1)
	{
		// Send message to Trace Recorder
		vTracePrint(ue2, (char *)msg);

		// Wait for 20ms
		vTaskDelay(20);
	}
}

/*
 *	Task_2
 */
void vTask2 (void *pvParameters)
{
	uint8_t	msg[] = "This is a much longer task_2 message"; // 36 bytes string

	while(1)
	{
		// Send message to trace Recorder
		vTracePrint(ue2, (char *)msg);

		// Wait for 30ms
		vTaskDelay(30);
	}
}

/*
 * vTaskHWM
 */
void vTaskHWM (void *pvParameters)
{
	uint32_t	count;
	uint16_t	hwm_Task1, hwm_Task2, hwm_TaskHWM;
	uint32_t	free_heap_size;

	count = 0;

	// Prepare console layout using ANSI escape sequences
	my_printf("%c[0m",   0x1B);	// Remove all text attributes
	my_printf("%c[2J",   0x1B); 	// Clear console
	my_printf("%c[1;0H", 0x1B);	// Move cursor [1:0]

	my_printf("High Water Marks console");

	my_printf("%c[3;0H", 0x1B);	// Move cursor line 3
	my_printf("Iteration");

	my_printf("%c[4;0H", 0x1B);	// Move cursor line 4
	my_printf("Task1");

	my_printf("%c[5;0H", 0x1B);	// Move cursor line 5
	my_printf("Task2");

	my_printf("%c[6;0H", 0x1B);	// Move cursor line 6
	my_printf("TaskHWM");

	my_printf("%c[7;0H", 0x1B);	// Move cursor line 7
	my_printf("Free Heap");


	while(1)
	{
	  // Gather High Water Marks
	  hwm_Task1	= uxTaskGetStackHighWaterMark(vTask1_handle);
	  hwm_Task2 	= uxTaskGetStackHighWaterMark(vTask2_handle);
	  hwm_TaskHWM	= uxTaskGetStackHighWaterMark(vTaskHWM_handle);

	  // Get free Heap size
	  free_heap_size = xPortGetFreeHeapSize();

	  // Reports watermarks into Trace Recorder
	  vTracePrintF(ue3, (char *)"1[%d] 2[%d] HWM[%d]",
                             hwm_Task1,
                             hwm_Task2,
                             hwm_TaskHWM );

	  // Display results into console
	  my_printf("%c[0;31;40m", 0x1B); 	// Red over black

	  my_printf("%c[3;12H", 0x1B);
	  my_printf("%5d", count);

	  my_printf("%c[1;33;44m", 0x1B); 	// Yellow over blue

	  my_printf("%c[4;12H", 0x1B);
	  my_printf("%5d", hwm_Task1);

	  my_printf("%c[5;12H", 0x1B);
	  my_printf("%5d", hwm_Task2);

	  my_printf("%c[6;12H", 0x1B);
	  my_printf("%5d", hwm_TaskHWM);

	  my_printf("%c[1;35;40m", 0x1B); 	// Majenta over black
	  my_printf("%c[7;12H", 0x1B);
	  my_printf("%5d", free_heap_size);

	  my_printf("%c[0m", 0x1B); 		// Remove all text attributes
	  count++;

	  // Wait for 200ms
	  vTaskDelay(200);
	}
}

/*
 *	Task_3
 *	- Sends a message to console when a notification is received
 */
void vTask3 (void *pvParameters)
{
	BaseType_t	notif_pending;
	uint8_t		*pmsg;
	uint8_t		slot_index;
	while(1)
	{
		BSP_LED_Toggle();
		for(slot_index = 0; slot_index<2; slot_index++)
		{
			// Poll notification on slot #0 with no timeout
			notif_pending = xTaskNotifyWaitIndexed(slot_index, 0, 0, (uint32_t *)&pmsg, 0);
			// If a notification was received
			if (notif_pending == pdPASS)
			{
		        my_printf("Notification received on slot[%d] : %s", slot_index, pmsg);
			}
		}
		// Polling period
		vTaskDelay(100);
	}
}

/*
 * Timer Callback
void vTaskTimer (TimerHandle_t xTimer)
{
	vTracePrintF(ue1, (char *)"%d", (uint32_t)ticks);

	my_printf("\tTimer callback\r\n");

	ticks = xTimerGetExpiryTime(my_timer);
	BSP_LED_Toggle();
}
 */

/*
 * Task_Console
void vTaskConsole (void *pvParameters)
{
	msg_t *pmsg = NULL;

	while(1)
	{
		// Wait for something in the message Queue
		xQueueReceive(xConsoleQueue, &pmsg, portMAX_DELAY);

		// Send message to console
		my_printf((char *)pmsg);
	}
}
 */

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
 */
void vApplicationMallocFailedHook()
{
	my_printf("Malloc Failed\r\n");

	while(1);
}
