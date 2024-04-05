#ifndef _assert_h_
#define _assert_h_

#include <stdint.h>
#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif

#define				ASSERT_USE

void _assert_func(void);

#if defined (ASSERT_USE)
#define				assert(ptr)				do				\
{															\
	if(!(ptr))												\
	{														\
		_log(TAG,LOG_LEVEL_ERROR,__LINE__,"assert failure!\r\n");	\
		_assert_func();										\
	}														\
	else													\
	{														\
		_log(TAG,LOG_LEVEL_TRACE,__LINE__,"assert success!\r\n");	\
	}														\
}while(0)

#else
#define				assert(ptr)				
#endif

#ifdef __cplusplus
}
#endif

#endif
