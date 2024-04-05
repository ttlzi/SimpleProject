#include "log.h"
#include "usart.h"
#include "dma.h"
#include <stdio.h>
#include <stdarg.h>

LOG_TAG("log.c");

static uint8_t log_level = LOG_LEVEL_DEBUG;
static uint8_t log_status = false;

static uint8_t usart_tx_buf[1024] = {0};

void u1_printf(char *fmt,...)
{

}

void log_lock(void)
{
	log_status = true;
}

void log_unlock(void)
{
	log_status = false;
}

void log_set_level(uint8_t level)
{
	#if defined (LOG_USE)
	if(level < LOG_LEVEL_MAX)
	{
		log_level = level;
		log_t("log now level is %d\r\n",level);
	}
	else
		log_e("log max level is %d,now your value is %d\r\n",LOG_LEVEL_TRACE,level);
	#else
	
	#endif
}

void _log(const char * tag, uint8_t level, uint32_t line, const char * fmt, ...)
{
	#if defined (LOG_USE)
    if(level <= log_level) 
	{
        sprintf((char *)usart_tx_buf, "%s", tag);
        sprintf((char *)(usart_tx_buf + strlen((const char *)usart_tx_buf)),"%s",log_level_label[level]);
        sprintf((char *)(usart_tx_buf + strlen((const char *)usart_tx_buf)),"Line %d:",line);
        va_list ap;
        va_start(ap,fmt);
        vsprintf((char *)(usart_tx_buf + strlen((const char *)usart_tx_buf)),fmt,ap);
        va_end(ap);
		size_t log_len = strlen((const char *)usart_tx_buf);
		if(log_len <= LOG_MSG_SIZE) 
		{
			
		}
        HAL_UART_Transmit(&huart1,usart_tx_buf,strlen((const char *)usart_tx_buf),1000);
    }
	#else
	
	#endif
}