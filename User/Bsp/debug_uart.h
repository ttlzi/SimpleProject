#ifndef _debug_uart_h_
#define _debug_uart_h_

#include "stm32f1xx_hal.h"
#include "basic_queue.h"

#define		USARTx									USART1
#define		__HAL_RCC_USARTx_CLK_ENABLE				__HAL_RCC_USART1_CLK_ENABLE
#define		__HAL_RCC_USARTx_CLK_DISABLE			__HAL_RCC_USART1_CLK_DISABLE
#define		__HAL_RCC_GPIOx_CLK_ENABLE				__HAL_RCC_GPIOA_CLK_ENABLE
#define		__HAL_RCC_GPIOx_CLK_DISABLE				__HAL_RCC_GPIOA_CLK_DISABLE
#define		USARTx_Tx_PIN							GPIO_PIN_9
#define		USARTx_Rx_PIN							GPIO_PIN_10
#define		USARTx_PORT								GPIOA
#define		USARTx_IRQn								USART1_IRQn

#define		UART_RX_BUF_MAX_SIZE					(64)
#define		UART_TX_BUF_MAX_SIZE					(512)

extern UART_HandleTypeDef huart;

void debug_uart_init(uint32_t baudrate);
uint16_t debug_uart_send(void * buf,uint16_t len);
uint16_t debug_uart_recv(void * buf, uint16_t len);
void debug_uart_buf_clear(void);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void debug_uart_irqn_handler(void);

#if 0
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);
void USART1_IRQHandler(void);
#endif

#endif