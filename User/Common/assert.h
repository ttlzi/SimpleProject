#ifndef _assert_h_
#define _assert_h_

#include "def.h"
#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif

#define		ASSERT_USE
#if defined (ASSERT_USE)	
#define				assert(ptr)				do				\
{															\
	if(!(ptr))												\
	{														\
		log_e("assert failure!\r\n");						\
		_assert_func();										\
	}														\
	else													\
		log_t("assert success!\r\n");						\
}while(0)

void _assert_func(void);
#else
#define		assert(ptr)
#endif

#ifdef __cplusplus
}
#endif

#endif
