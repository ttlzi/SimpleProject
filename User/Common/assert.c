#include "assert.h"

#ifdef __cplusplus
extern "C" {
#endif

LOG_TAG("assert.c");

#if defined (ASSERT_USE)	

void _assert_func(void)
{
	while(1){};
}

#else

#endif

#ifdef __cplusplus
}
#endif
	