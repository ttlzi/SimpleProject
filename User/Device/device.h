#ifndef _device_h_
#define _device_h_

#include "def.h"

typedef struct
{
    /* public data */
	const char * name;
    bool unique;
    bool busy;
    struct device_ops * device_ops;
    /* private data */
    void * user_data;
}device_t;

typedef struct device_ops
{
    bool (* write)(device_t * const me,uint32_t pos,const void * buf,uint16_t len);
    bool (* read)(device_t * const me,uint32_t pos,void * buf,uint16_t len);
    bool (* open)(device_t * const me);
    bool (* close)(device_t * const me);
    bool (* ioctl)(device_t * const me,uint8_t cmd,void * user_data);
}device_ops_t;

#define		DEVICE_MAX_NUM				(64)

void device_register(device_t * const me);
void device_unregister(device_t * const me);
device_t * device_find_from_table(const char * name);
void device_register_ops_to_device(device_t * const me,device_ops_t * ops);

#endif
