#include "device.h"

LOG_TAG("device.c");

#ifdef __cplusplus
extern "C" {
#endif

static uint16_t _device_count = 0;
static device_t * _device_table[DEVICE_MAX_NUM];

static void _device_add(device_t * me);

void device_register(device_t * me,device_attr_t * attr)
{
    assert(me != NULL);
    assert(attr != NULL);
    assert(attr->name != NULL);

    memcpy(&me->attr,attr, sizeof(device_attr_t));
    _device_add(me);

}

void device_unregister(device_t * me)
{
	
}

static void _device_add(device_t * me)
{
    assert(_device_count < DEVICE_MAX_NUM);

    if(_device_count == 0)
    {
        for(uint16_t index = 0;index < DEVICE_MAX_NUM;index++)
            _device_table[index] = NULL;
    }
    _device_table[_device_count++] = me;
}

#ifdef __cplusplus
}
#endif
