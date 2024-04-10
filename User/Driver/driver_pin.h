#ifndef _driver_pin_h_
#define _driver_pin_h_

#include "driver.h"
#include "stm32f1xx_hal.h"

enum pin_mode
{
    PIN_MODE_INPUT = 0,
    PIN_MODE_INPUT_PULLUP,
    PIN_MODE_INPUT_PULLDOWN,
    PIN_MODE_OUTPUT_PP,
    PIN_MODE_OUTPUT_OD,

    PIN_MODE_MAX
};

typedef struct driver_pin
{
    char * pin_name;
    uint8_t pin_mode;
    uint8_t pin_status;
    GPIO_TypeDef * pin_port;
    uint16_t pin_num;

    bool (* init)(struct driver_pin * const me);
    bool (* set_mode)(struct driver_pin * const me,uint8_t mode);
    bool (* set_status)(struct driver_pin * const me,uint8_t pin_status);
    bool (* get_status)(struct driver_pin * const me,uint8_t * pin_status);

    device_t super;
}driver_pin_t;

void driver_pin_init(driver_pin_t * const me,const char * name,const char * pin_name);

#endif
