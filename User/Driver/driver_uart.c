//#include "driver_uart.h"
//
//static uint8_t uart_rx_buf[UART_RX_MAX_SIZE];
//static uint8_t uart_tx_buf[UART_TX_MAX_SIZE];
//
//static driver_uart_data_t driver_uart_data =
//{
//	&huart1,
//	.dma = false,
//	&hdma_usart1_tx,
//	&hdma_usart1_rx,
//};
//
//static bool _init(driver_uart_t * me);
//static bool _deinit(driver_uart_t * me);
//static bool _write(driver_uart_t * me,const void * buf,uint32_t len,uint32_t time_out);
//static bool _read(driver_uart_t * me,void * buf,uint32_t len,uint32_t time_out);
//
//void driver_uart_init(driver_uart_t * me,const char * name)
//{
//
//}
//
//static bool _init(driver_uart_t * me)
//{
//
//	return false;
//}
//
//static bool _deinit(driver_uart_t * me)
//{
//	return false;
//}
//
//static bool _write(driver_uart_t * me,const void * buf,uint32_t len,uint32_t time_out)
//{
////	HAL_UART_Transmit_IT();
//	return false;
//}
//
//static bool _read(driver_uart_t * me,void * buf,uint32_t len,uint32_t time_out)
//{
//	return false;
//}
//
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart == &huart1)
//	{
//
//	}
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart == &huart1)
//	{
//
//	}
//}