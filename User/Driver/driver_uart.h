//#ifndef _driver_uart_h_
//#define _driver_uart_h_
//
//#include "device_uart.h"
//#include "stm32f1xx_hal.h"
//#include "usart.h"
//#include "dma.h"
//
//#include "FreeRTOS.h"
//#include "semphr.h"
//
////#define		UART_RX_MAX_SIZE				(1024)
////#define		UART_RX_MSG_SIZE				(64)
////#define		UART_RX_MSG_NUM					(UART_RX_MAX_SIZE / UART_RX_MSG_SIZE)
////#define		UART_TX_MAX_SIZE				(1024)
////#define		UART_TX_MSG_SIZE				(64)
////#define		UART_TX_MSG_NUM					(UART_TX_MAX_SIZE / UART_TX_MSG_SIZE)
//
////typedef struct
////{
////	uint8_t * start;
////	uint8_t * stop;
////}uart_pointer_t;
//
////typedef struct
////{
////	uint16_t count;
////	uart_pointer_t num[UART_RX_MSG_NUM];
////	uart_pointer_t * in;
////	uart_pointer_t * out;
////	uart_pointer_t * end;
////	void * buf;
////}uart_control_t;
//
//typedef struct
//{
//	UART_HandleTypeDef * huart;
//	bool dma;
//	DMA_HandleTypeDef * hdma_usart_tx;
//	DMA_HandleTypeDef * hdma_usart_rx;
//	SemaphoreHandle_t xTxSem;
//}driver_uart_data_t;
//
//typedef struct driver_uart
//{
//	device_t device;
//	void * driver_data;
//	bool (* init)(struct driver_uart * me);
//	bool (* deinit)(struct driver_uart * me);
//	bool (* write)(struct driver_uart * me,const void * buf,uint32_t len,uint32_t time_out);
//	bool (* read)(struct driver_uart * me,void * buf,uint32_t len,uint32_t time_out);
//}driver_uart_t;
//
//#endif
