#ifndef _dev_def_h_
#define _dev_def_h_

#include "device_pin.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    /* public data */
    device_t super;
    /* private data */
	void * driver_ops;
	void * user_data;
}driver_t;

#ifdef __cplusplus
}
#endif

#endif
