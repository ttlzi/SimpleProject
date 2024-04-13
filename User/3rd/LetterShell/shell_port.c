#include "shell_port.h"
#include "shell.h"
#include "debug_uart.h"
#include "FreeRTOS.h"
#include "task.h"

#define		SHELL_BUFFER_SIZE				(512)

static Shell shell_uart;
static char shell_uart_buffer[SHELL_BUFFER_SIZE];

static void shell_create_task(void);

static void shell_uart_init(void)
{
	debug_uart_init(115200);
	shell_uart.read = (int16_t (*)(char *,uint16_t))debug_uart_recv;
	shell_uart.write = (int16_t (*)(char *,uint16_t))debug_uart_send;
	shellInit(&shell_uart,shell_uart_buffer,SHELL_BUFFER_SIZE);
	
	shell_create_task();
}
INIT_EXPORT(shell_uart_init,EXPORT_LEVEL_2);

#define		SHELL_TASK_PRIO				(10)
#define		SHELL_TASK_SIZE				(1024)
xTaskHandle SHELL_TaskHandle = NULL;
void shell_task(void *pvParameters);

static void shell_create_task(void)
{
	xTaskCreate(shell_task,"shell_task",SHELL_TASK_SIZE,NULL,SHELL_TASK_PRIO,&SHELL_TaskHandle);
}


void shell_task(void *pvParameters)
{
	(void )pvParameters;
	
	char byte;
	
	while(1)
	{
		while(shell_uart.read && shell_uart.read(&byte,1) == 1)
		{
			shellHandler(&shell_uart,byte);
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}	
