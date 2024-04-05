#ifndef _dev_def_h_
#define _dev_def_h_

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	const char * name;
	bool sole;
	uint8_t type;
}device_attr_t;

typedef struct
{
	device_attr_t attr;
	
	const struct device_ops * ops;
	
	void *user_data;
}device_t;

/*
 *  设备层操作应该有 读、写、打开、关闭、控制等几个基本操作
 */
typedef struct device_ops
{
	bool (* read)(device_t * me,uint32_t pos,void * buf,uint32_t len);
	bool (* write)(device_t * me,uint32_t pos,const void * buf,uint32_t len);
	bool (* open)(device_t * me);
	bool (* close)(device_t * me);
	bool (* ioctl)(device_t * me,uint8_t cmd,void *user_data);
}device_ops_t;

#define             DEVICE_MAX_NUM              (100)
#define             DEVICE_CAST(dev)                ((device_t *)dev)

void device_register(device_t * me,device_attr_t * attr);
void device_unregister(device_t * me);

#ifdef __cplusplus
}
#endif

#endif
