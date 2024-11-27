#include "stm32f0xx.h"
#include "bsp.h"
#include "main.h"

// Define Event Group flags
#define	BIT0	( (EventBits_t)( 0x01 <<0) )   // This is not mandatory but it provides
#define BIT1	( (EventBits_t)( 0x01 <<1) )   // friendly alias for individual event

// Static functions
static void SystemClock_Config (void);

// FreeRTOS tasks
void vTask1 		(void *pvParameters);
void vTask2 		(void *pvParameters);
// Timer callback function
void vTaskTimer		(TimerHandle_t xTimer);
// Declare Timer Object
TimerHandle_t	my_timer;
TickType_t	ticks;
// Trace User Events Channels
traceString ue1;

// Kernel objects
xSemaphoreHandle xSem;
xSemaphoreHandle xSem;
xQueueHandle	xConsoleQueue;
EventGroupHandle_t myEventGroup;

// Trace User Events Channels
//traceString ue1, ue2;

// Define the message_t type as an array of 64 char
typedef uint8_t msg_t[64];

// Main function
int main()
{
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
	xTraceEnable(TRC_START);		// vTraceEnable(TRC_START);

	// Create Event Group                   // <-- Create Event Group here
	myEventGroup = xEventGroupCreate();

	// Create Timer object
	my_timer = xTimerCreate("my_timer", 200, pdTRUE, NULL, vTaskTimer);
	// Start Timer
	xTimerStart(my_timer, 0);
	ticks = xTimerGetExpiryTime(my_timer);
	// Register the Trace User Event Channels
	ue1 = xTraceRegisterString("ticks");

	// Create Semaphore object
	//xSem = xSemaphoreCreateBinary();

	// Give a nice name to the Semaphore in the trace recorder
	//vTraceSetSemaphoreName(xSem, "xSEM");

	// Create Tasks
	xTaskCreate(vTask1,		"Task_1", 		256, NULL, 1, NULL);
	xTaskCreate(vTask2,		"Task_2", 		256, NULL, 2, NULL);

	// Register the Trace User Event Channels
	// ue1 = xTraceRegisterString("count");
	// ue2 = xTraceRegisterString("msg");

	// Create Queue to hold console messages
	// xConsoleQueue = xQueueCreate(4, sizeof(msg_t *));

	// Give a nice name to the Queue in the trace recorder
	// vTraceSetQueueName(xConsoleQueue, "Console Queue");

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
		my_printf("-");
		// Wait for 1s
		vTaskDelay(1000);
	}
}
/*
 *	Task_2
 */
void vTask2 (void *pvParameters)
{
	while(1)
	{
		my_printf("#");
		// Wait for 500ms
		vTaskDelay(500);
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
 */
void vTaskTimer (TimerHandle_t xTimer)
{
	vTracePrintF(ue1, (char *)"%d", (uint32_t)ticks);

	my_printf("\tTimer callback\r\n");

	ticks = xTimerGetExpiryTime(my_timer);
	BSP_LED_Toggle();
}

/*
 * Task_Console
 */
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
