#ifndef _log_h_
#define _log_h_

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

#define				LOG_USE
#define				LOG_COLOR_USE				
#define				LOG_TAG(tag)				static const char *TAG = tag
#define				LOG_BUF_SIZE				(1024)
#define				LOG_MSG_SIZE				(64)
#define				LOG_MSG_NUM					(LOG_BUF_SIZE / LOG_MSG_SIZE)
	
#if defined(LOG_COLOR_USE)
#define				LOG_LEVEL_LABEL_TRACE		"\033[1;37;40m [Trace] \033[0m"
#define				LOG_LEVEL_LABEL_INFO		"\033[1;34;40m [Info ] \033[0m" 
#define				LOG_LEVEL_LABEL_DEBUG		"\033[1;32;40m [Debug] \033[0m"
#define				LOG_LEVEL_LABEL_WARN		"\033[1;33;40m [Warn ] \033[0m"
#define				LOG_LEVEL_LABEL_ERROR		"\033[1;31;40m [Error] \033[0m"
#else 
#define				LOG_LEVEL_LABEL_TRACE		"[Trace]"
#define				LOG_LEVEL_LABEL_INFO		"[Info ]"
#define				LOG_LEVEL_LABEL_DEBUG		"[Debug]"
#define				LOG_LEVEL_LABEL_WARN		"[Warn ]"
#define				LOG_LEVEL_LABEL_ERROR		"[Error]"
#endif

static const char * const log_level_label[] = {
	LOG_LEVEL_LABEL_ERROR,
	LOG_LEVEL_LABEL_WARN,
	LOG_LEVEL_LABEL_DEBUG,
	LOG_LEVEL_LABEL_INFO,
	LOG_LEVEL_LABEL_TRACE,
};

enum
{
	LOG_LEVEL_ERROR = 0,
	LOG_LEVEL_WARN,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_TRACE,
	LOG_LEVEL_MAX,
};

void u1_printf(char *fmt,...);
void log_lock(void);
void log_unlock(void);
void log_set_level(uint8_t level);
void _log(const char * tag, uint8_t level, uint32_t line, const char * fmt, ...);

#if defined(LOG_USE)
#define				log_t(...)				_log(TAG,LOG_LEVEL_TRACE,__LINE__,__VA_ARGS__)
#define				log_i(...)				_log(TAG,LOG_LEVEL_INFO,__LINE__,__VA_ARGS__)
#define				log_d(...)				_log(TAG,LOG_LEVEL_DEBUG,__LINE__,__VA_ARGS__)
#define				log_w(...)				_log(TAG,LOG_LEVEL_WARN,__LINE__,__VA_ARGS__)
#define				log_e(...)				_log(TAG,LOG_LEVEL_ERROR,__LINE__,__VA_ARGS__)
#else
#define				log_t(...)
#define				log_i(...)
#define				log_d(...)
#define				log_w(...)
#define				log_e(...)
#endif

#ifdef __cplusplus
}
#endif

#endif
