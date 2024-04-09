#include "device.h"

LOG_TAG("device.c");

static void _device_add_to_table(device_t * const me);

static uint16_t _device_count = 0;
static device_t *_device_table[DEVICE_MAX_NUM];

void device_register(device_t * const me)
{
	assert(me != NULL);
	
	_device_add_to_table(me);
}

void device_unregister(device_t * const me)
{
	
}

static void _device_add_to_table(device_t * const me)
{
	assert(me != NULL);
	if(_device_count == 0)
	{
		for(uint16_t index = 0;index < DEVICE_MAX_NUM;index++)
		{
			_device_table[index] = NULL;
		}
	}
	_device_table[_device_count++] = me;
}

device_t * device_find_from_table(const char * name)
{
	assert(_device_table[0] != NULL);
	assert(name != NULL);
	
	device_t * device = NULL;
	for(uint16_t index = 0;index < DEVICE_MAX_NUM;index++)
	{
		if(_device_table[index] == NULL)
			break;
		if(strcmp(name,_device_table[index]->name) == 0)
		{
			device = _device_table[index];
			break;
		}
	}
	return device;
}

void device_register_ops_to_device(device_t * const me,device_ops_t * ops)
{
	assert(me != NULL);
	assert(ops != NULL);
	
	me->device_ops = ops;
}
