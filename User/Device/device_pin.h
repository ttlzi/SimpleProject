#ifndef _device_pin_h_
#define _device_pin_h_

#include "device.h"
#include "driver_pin.h"

void device_pin_register(device_t * const me,const char * name,void * user_data);

#endif
