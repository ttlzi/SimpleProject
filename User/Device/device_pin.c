#include "device_pin.h"

LOG_TAG("device_pin.c");

static bool _write(device_t * const me,uint32_t pos,const void * buf,uint16_t len);
static bool _read(device_t * const me,uint32_t pos,void * buf,uint16_t len);
static bool _open(device_t * const me);
static bool _close(device_t * const me);
static bool _ioctl(device_t * const me,uint8_t cmd,void * user_data);

static device_ops_t device_pin_ops = {
	.write = _write,
	.read = _read,
	.open = _open,
	.close = _close,
	.ioctl = _ioctl,
};

void device_pin_register(device_t * const me,const char * name,void * user_data)
{
	assert(me != NULL);
	assert(name != NULL);
	assert(user_data != NULL);
	
	me->name = name;
	me->unique = true;
	me->busy = false;
	
	me->user_data = user_data;
    
	device_register_ops_to_device(me,&device_pin_ops);
	device_register(me);
}

static bool _write(device_t * const me,uint32_t pos,const void * buf,uint16_t len)
{
	assert(me != NULL);
	driver_pin_t * driver_pin = (driver_pin_t *)me->user_data;
	return driver_pin->set_status(driver_pin,*(bool *)buf);
}

static bool _read(device_t * const me,uint32_t pos,void * buf,uint16_t len)
{
	assert(me != NULL);
	driver_pin_t * driver_pin = (driver_pin_t *)me->user_data;
	return driver_pin->get_status(driver_pin,buf);
}

static bool _open(device_t * const me)
{
	assert(me != NULL);
	return true;
}

static bool _close(device_t * const me)
{
	assert(me != NULL);
	return true;
}

static bool _ioctl(device_t * const me,uint8_t cmd,void * user_data)
{
	assert(me != NULL);
	assert(user_data != NULL);
	
	driver_pin_t * driver_pin = (driver_pin_t *)me->user_data;
	
	switch(cmd)
	{
		case (0):
			return driver_pin->init(driver_pin);
			break;
		
		case (1):
			return driver_pin->set_mode(driver_pin,*(uint8_t *)user_data);
			break;
		
		default:
			return false;
			break;
	}
}
