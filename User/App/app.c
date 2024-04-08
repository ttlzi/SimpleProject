#include "app.h"

#define		START_TASK_PRIO				(1)
#define		START_TASK_SIZE				(128)
void start_task(void *pvParamaters);

#define		LED_TASK_PRIO				(10)
#define		LED_TASK_SIZE				(512)
xTaskHandle LED_TaskHandle = NULL;
void led_task(void *pvParamaters);

#define		UART_TASK_PRIO				(10)
#define		UART_TASK_SIZE				(512)
xTaskHandle UART_TaskHandle = NULL;
void uart_task(void *pvParamaters);

void start_task(void *pvParamaters)
{
	portENTER_CRITICAL();
	xTaskCreate(led_task,"led_task",LED_TASK_SIZE,NULL,LED_TASK_PRIO,&LED_TaskHandle);
	xTaskCreate(uart_task,"uart_task",UART_TASK_SIZE,NULL,UART_TASK_PRIO,&UART_TaskHandle);
	portEXIT_CRITICAL();
	vTaskDelete(NULL);
}

void led_task(void *pvParamaters)
{
	bool led_status = false;
	while(1)
	{
		vTaskDelay(pdMS_TO_TICKS(100));
		if(led_status == true)
			led_status = false;
		else if(led_status == false)
			led_status = true;
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,led_status);
	}
}

void uart_task(void *pvParamaters)
{
	while(1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void app_main(void)
{
	xTaskCreate(start_task,"start_task",START_TASK_SIZE,NULL,START_TASK_PRIO,NULL);
	vTaskStartScheduler();
	while(1)
	{
		
	}
}
