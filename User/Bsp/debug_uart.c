#include "debug_uart.h"

static basic_queue_t queue_rx;
static uint8_t buf_rx[UART_RX_BUF_MAX_SIZE];
static basic_queue_t queue_tx;
static uint8_t buf_tx[UART_TX_BUF_MAX_SIZE];
static uint8_t byte_recv = 0;
static uint8_t byte_send = 0;

UART_HandleTypeDef huart;

void debug_uart_init(uint32_t baudrate)
{
    huart.Instance = USARTx;
    huart.Init.BaudRate = baudrate;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&huart);
    HAL_UART_Receive_IT(&huart,&byte_recv,1);

    basic_queue_init(&queue_rx,buf_rx,UART_RX_BUF_MAX_SIZE);
    basic_queue_init(&queue_tx,buf_tx,UART_TX_BUF_MAX_SIZE);
}

uint16_t debug_uart_send(void * buf,uint16_t len)
{
    uint16_t ret = 0;
    HAL_NVIC_DisableIRQ(USARTx_IRQn);
    if(basic_queue_is_empty(&queue_tx))
    {
        ret = basic_queue_push(&queue_tx,buf,len);
        if(basic_queue_pull_pop(&queue_tx,&byte_send,1) == 1)
            HAL_UART_Transmit_IT(&huart,&byte_send,1);
    }
    else
        ret = basic_queue_push(&queue_tx,buf,len);
    HAL_NVIC_EnableIRQ(USARTx_IRQn);
    return ret;
}

uint16_t debug_uart_recv(void * buf, uint16_t len)
{
    uint16_t ret = 0;
    HAL_NVIC_DisableIRQ(USARTx_IRQn);
    ret = basic_queue_pull_pop(&queue_rx,buf,len);
    HAL_NVIC_EnableIRQ(USARTx_IRQn);
    return ret;
}

void debug_uart_buf_clear(void)
{
    HAL_NVIC_DisableIRQ(USARTx_IRQn);
    basic_queue_clear(&queue_rx);
    basic_queue_clear(&queue_tx);
    HAL_NVIC_EnableIRQ(USARTx_IRQn);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t byte = 0;
    if(huart->Instance == USARTx)
    {
        if(basic_queue_pull_pop(&queue_tx,&byte,1))
        {
            HAL_UART_Transmit_IT(huart,&byte,1);
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USARTx)
    {
        HAL_UART_Receive_IT(huart,&byte_recv,1);
        basic_queue_push(&queue_rx,&byte_recv,1);
    }
}

void debug_uart_irqn_handler(void)
{
    HAL_UART_IRQHandler(&huart);
}

#if 0 //If STM32CubeMx has already been used to configure this serial port

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(huart->Instance == USARTx)
	{
		__HAL_RCC_USARTx_CLK_ENABLE();
		__HAL_RCC_GPIOx_CLK_ENABLE();

		GPIO_InitStruct.Pin = USARTx_Tx_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(USARTx_PORT, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = USARTx_Rx_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(USARTx_PORT, &GPIO_InitStruct);

		HAL_NVIC_SetPriority(USARTx_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USARTx_IRQn);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USARTx)
	{
		__HAL_RCC_USARTx_CLK_DISABLE();
		__HAL_RCC_GPIOx_CLK_DISABLE();

		HAL_GPIO_DeInit(USARTx_PORT,(USARTx_Tx_PIN | USARTx_Rx_PIN));

		HAL_NVIC_DisableIRQ(USARTx_IRQn);
	}
}

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart);
}

#endif