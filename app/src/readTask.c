/*
 * readTask.c
 *
 *  Created on: Jan 13, 2025
 *      Author: vinic
 */
#include "readTask.h"

static xTaskHandle vTaskPub_handle;
static xQueueHandle xSubscribeQueue;
static xSemaphoreHandle ledMutex;
xSemaphoreHandle sems[MAX_SEMAPHORE];

uint8_t sensor_states[SENSOR_TABLE_SIZE] = {0};

static void updateSubs(subscribe_message_t *subs, subscribe_message_t *new_sub);
static void print_subscription_table(subscribe_message_t *subs);
static void uartSensor(uint8_t *sensors);
static void publish(subscribe_message_t *subs, uint8_t *sensors);

BaseType_t vTaskPubInit(){
	size_t i;

    // Create the subscription queue
    xSubscribeQueue = xQueueCreate(QUEUE_LENGTH, sizeof(subscribe_message_t));

	ledMutex = xSemaphoreCreateMutex();
	for(i = 0; i < MAX_SEMAPHORE; i++) {
		sems[i] = xSemaphoreCreateBinary();
	}

    xTaskCreate(vTask_Pub, "vTask_Pub", 128, NULL, 1, &vTaskPub_handle);

    my_printf("READ TASK DEFINED\r\n");


    return pdPASS;
}

void vTask1_Pub(){
	subscribe(1,1,0);
	xSemaphoreTake(sems[1], portMAX_DELAY);

	xSemaphoreTake(ledMutex, portMAX_DELAY);
	BSP_LED_On();
	vTaskDelay(100 / portTICK_PERIOD_MS);
	BSP_LED_Off();
	xSemaphoreGive(ledMutex);

	subscribe(1, 1, 1);
	xSemaphoreTake(sems[1], portMAX_DELAY);

	xSemaphoreTake(ledMutex, portMAX_DELAY);
	BSP_LED_On();
	vTaskDelay(100 / portTICK_PERIOD_MS);
	BSP_LED_Off();
	vTaskDelay(200 / portTICK_PERIOD_MS);
	BSP_LED_On();
	vTaskDelay(100 / portTICK_PERIOD_MS);
	BSP_LED_Off();
	xSemaphoreGive(ledMutex);
}
void vTask2_Pub(){
	subscribe(2, 2, 0);
	xSemaphoreTake(sems[2], portMAX_DELAY);

	xSemaphoreTake(ledMutex, portMAX_DELAY);
	BSP_LED_On();
	vTaskDelay(200 / portTICK_PERIOD_MS);
	BSP_LED_Off();
	xSemaphoreGive(ledMutex);

	subscribe(2, 2, 1);
	xSemaphoreTake(sems[2], portMAX_DELAY);

	xSemaphoreTake(ledMutex, portMAX_DELAY);
	BSP_LED_On();
	vTaskDelay(200 / portTICK_PERIOD_MS);
	BSP_LED_Off();
	vTaskDelay(400 / portTICK_PERIOD_MS);
	BSP_LED_On();
	vTaskDelay(200 / portTICK_PERIOD_MS);
	BSP_LED_Off();
	xSemaphoreGive(ledMutex);
}

void vTask_Pub(void *pvParameters){
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200 / portTICK_PERIOD_MS;

	xLastWakeTime = xTaskGetTickCount();

	subscribe_message_t subscription_table[MAX_SUBSCRIBERS] = {0};
	subscribe_message_t msg;
	size_t i;
	// char rx_byte;

	// Reseting the message
	for(i = 0; i < MAX_SUBSCRIBERS; i++) {
	 	subscription_table[i].sem_id = 0;
	   	subscription_table[i].sensor_id = 0;
	   	subscription_table[i].sensor_state = 0;
	}

	for(i = 0; i < SENSOR_TABLE_SIZE; i++) {
		sensor_states[i] = 0;
	}
	// BSP_LED_Toggle();

	while (1) {
	  	if(xQueueReceive(xSubscribeQueue, &msg, 0)){
	  		updateSubs(subscription_table, &msg);
	   		print_subscription_table(subscription_table);
	   	} else {
	   		my_printf(".");
	   	}

	   	uartSensor(sensor_states);
		publish(subscription_table, sensor_states);

		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

BaseType_t subscribe(uint8_t sem_id, uint8_t sensor_id, uint8_t sensor_state)
{
	subscribe_message_t data = {
		.sem_id = sem_id,
		.sensor_id = sensor_id,
		.sensor_state = sensor_state
	};

	return xQueueSend(xSubscribeQueue, &data, 0);
}


static void updateSubs(subscribe_message_t *subs, subscribe_message_t *new_sub) {
    size_t i;

    my_printf("Subscribing...");

    // Check for duplicates
    for (i = 0; i < MAX_SUBSCRIBERS; i++) {
        if (subs[i].sem_id == new_sub->sem_id &&
            subs[i].sensor_id == new_sub->sensor_id &&
            subs[i].sensor_state == new_sub->sensor_state) {
            my_printf("Subscription already exists\r\n");
            return;
        }
    }

    // Add the new subscription to the first available slot
    for (i = 0; i < MAX_SUBSCRIBERS; i++) {
        if (subs[i].sem_id == 0) {
            subs[i] = *new_sub;
            my_printf("Adding subscription in slot [%d]\r\n", i);
            return;
        }
    }

    // If the table is full
    my_printf("No available slots for new subscription\r\n");
}

static void print_subscription_table(subscribe_message_t *subs) {
    for (int i = 0; i < MAX_SUBSCRIBERS; i++) {
        my_printf("[%d] %d %d %d\r\n", i, subs[i].sem_id, subs[i].sensor_id, subs[i].sensor_state);
    }
}

static void uartSensor(uint8_t *sensors)
{
	uint8_t rx;
	size_t i;
	if( (USART2->ISR & USART_ISR_RXNE) != USART_ISR_RXNE ) return;
	rx = USART2->RDR;
	switch(rx) {
	case 'a': sensors[1] = 0; break;
	case 'b': sensors[1] = 1; break;
	case 'c': sensors[2] = 0; break;
	case 'd': sensors[2] = 1; break;
	}
	my_printf("sensors = [ ");
	for(i = 1; i <= SENSOR_TABLE_SIZE; i++) {
		my_printf("%d ", sensors[i]);
	}
	my_printf("]\r\n");
}

static void publish(subscribe_message_t *subs, uint8_t *sensors) {
	size_t i;
	uint8_t sensor, sem;

	for(i = 0; i < MAX_SUBSCRIBERS; i++) {
		if(subs[i].sem_id == 0) continue;

		sensor = subs[i].sensor_id;
		sem = subs[i].sem_id;

		if(sensors[sensor] == subs[i].sensor_state) continue;

		xSemaphoreGive(sems[sem]);

		my_printf("published\r\n");

		subs[i].sem_id = 0;
		subs[i].sensor_id = 0;
		subs[i].sensor_state = 0;
	}
}

