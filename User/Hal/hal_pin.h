#ifndef _hal_pin_h_
#define _hal_pin_h_

#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    PIN_MODE_INPUT = 0,
    PIN_MODE_INPUT_PULLUP,
    PIN_MODE_INPUT_PULLDOWN,
    PIN_MODE_OUTPUT_PP,
    PIN_MODE_OUTPUT_OD,
    PIN_MODE_MAX,
};

typedef struct
{
    device_t super;
    const struct hal_pin_ops * ops;
    uint8_t mode;
    bool status;
}hal_pin_t;

typedef struct hal_pin_ops
{
    bool (* init)(hal_pin_t * const me);
    bool (* set_mode)(hal_pin_t * const me,uint8_t mode);
    bool (* set_status)(hal_pin_t * const me,bool status);
    bool (* get_status)(hal_pin_t * const me,bool * status);
}hal_pin_ops_t;

#define             HAL_PIN_CAST(dev)               ((hal_pin_t *)dev)

/* For low-level driver. */
void hal_pin_register(hal_pin_t * const me,const char * name,const hal_pin_ops_t * ops,void * user_data);
/* For high-level code. */
void hal_pin_set_mode(device_t * const me,uint8_t mode);
void hal_pin_set_status(device_t * const me,bool status);
void hal_pin_get_status(device_t * const me,bool * status);

#ifdef __cplusplus
}
#endif

#endif
/* ----------------------------- end of file -------------------------------- */
