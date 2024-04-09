//#include "drv_pin.h"

//#ifdef __cplusplus
//extern "C" {
//#endif

//LOG_TAG("drv_pin.c");

//static bool check_pin_name_valid(const char * name);
//static GPIO_TypeDef * get_port_from_name(const char * name);
//static uint16_t get_pin_from_name(const char * name);
//static void gpio_clock_enable(const char * name);
//static bool _init(hal_pin_t * const me);
//static bool _set_mode(hal_pin_t * const me,uint8_t mode);
//static bool _set_status(hal_pin_t * const me,bool status);
//static bool _get_status(hal_pin_t * const me,bool * status);

//static const hal_pin_ops_t driver_pin_ops = {
//        .init = _init,
//        .set_mode = _set_mode,
//        .set_status = _set_status,
//        .get_status = _get_status,
//};

//void driver_pin_mcu_init(driver_pin_t * me, const char * name, const char * pin_name)
//{
//    assert(me != NULL);
//    assert(name != NULL);
//    assert(check_pin_name_valid(pin_name));

//    gpio_clock_enable(pin_name);
//    me->pin_name = pin_name;
//    hal_pin_register(&me->device,name,&driver_pin_ops,me);
//}

//static bool _init(hal_pin_t * const me)
//{
//    assert(me != NULL);

//    driver_pin_t * driver_pin = DRIVER_PIN_CAST(me->super.user_data);
//    GPIO_TypeDef * port = get_port_from_name(driver_pin->pin_name);
//    uint16_t pin = get_pin_from_name(driver_pin->pin_name);

//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Pin = pin;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(port, &GPIO_InitStruct);

//    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);

//    return true;
//}

//static bool _set_mode(hal_pin_t * const me,uint8_t mode)
//{
//    assert(me != NULL);
//    assert(mode < PIN_MODE_MAX);

//    driver_pin_t * driver_pin = DRIVER_PIN_CAST(me->super.user_data);
//    GPIO_TypeDef * port = get_port_from_name(driver_pin->pin_name);
//    uint16_t pin = get_pin_from_name(driver_pin->pin_name);

//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    if (mode == PIN_MODE_INPUT)
//    {
//        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//        GPIO_InitStruct.Pull = GPIO_NOPULL;
//    }
//    else if (mode == PIN_MODE_INPUT_PULLUP)
//    {
//        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//        GPIO_InitStruct.Pull = GPIO_PULLUP;
//    }
//    else if (mode == PIN_MODE_INPUT_PULLDOWN)
//    {
//        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//    }
//    else if (mode == PIN_MODE_OUTPUT_PP)
//    {
//        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//        GPIO_InitStruct.Pull = GPIO_NOPULL;
//    }
//    else if (mode == PIN_MODE_OUTPUT_OD)
//    {
//        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//        GPIO_InitStruct.Pull = GPIO_PULLUP;
//    }
//    GPIO_InitStruct.Pin = pin;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(port, &GPIO_InitStruct);

//    return true;
//}

//static bool _set_status(hal_pin_t * const me,bool status)
//{
//    assert(me != NULL);

//    driver_pin_t * driver_pin = DRIVER_PIN_CAST(me->super.user_data);
//    GPIO_TypeDef * port = get_port_from_name(driver_pin->pin_name);
//    uint16_t pin = get_pin_from_name(driver_pin->pin_name);

//    HAL_GPIO_WritePin(port,pin,(status ? GPIO_PIN_SET : GPIO_PIN_RESET));

//    return true;
//}

//static bool _get_status(hal_pin_t * const me,bool * status)
//{
//    assert(me != NULL);

//    driver_pin_t * driver_pin = DRIVER_PIN_CAST(me->super.user_data);
//    GPIO_TypeDef * port = get_port_from_name(driver_pin->pin_name);
//    uint16_t pin = get_pin_from_name(driver_pin->pin_name);

//    *status = HAL_GPIO_ReadPin(port, pin);

//    return true;
//}

//static bool check_pin_name_valid(const char * name)
//{
//    bool valid = true;

//    if ((strlen(name) != 4) || name[1] != '.')
//    {
//        valid = false;
//    }
//    else if (!(name[0] >= 'A' && name[0] <= 'F'))
//    {
//        valid = false;
//    }
//    else if (!(name[2] >= '0' && name[2] <= '9'))
//    {
//        valid = false;
//    }
//    else if (!(name[3] >= '0' && name[3] <= '9'))
//    {
//        valid = false;
//    }

//    char * str_num = (char *)&name[2];
//    uint16_t pin_num = strtol(str_num,NULL,10);
//    if (pin_num < 0 || pin_num >= 16)
//    {
//        valid = false;
//    }

//    return valid;
//}

//static GPIO_TypeDef * get_port_from_name(const char * name)
//{
//    static const GPIO_TypeDef * port_table[] = {
//            GPIOA,GPIOB,GPIOC,GPIOD,GPIOE
//    };
//    return (GPIO_TypeDef *)port_table[name[0] - 'A'];
//}

//static uint16_t get_pin_from_name(const char * name)
//{
//    char * str_num = (char *)&name[2];
//    uint16_t pin_num = strtol(str_num,NULL,10);
//    return (uint16_t)(1 << pin_num);
//}

//static void gpio_clock_enable(const char * name)
//{
//    if(get_port_from_name(name) == GPIOA)
//    {
//        __HAL_RCC_GPIOA_CLK_ENABLE();
//    }
//    else if(get_port_from_name(name) == GPIOB)
//    {
//        __HAL_RCC_GPIOB_CLK_ENABLE();
//    }
//    else if(get_port_from_name(name) == GPIOC)
//    {
//        __HAL_RCC_GPIOC_CLK_ENABLE();
//    }
//    else if(get_port_from_name(name) == GPIOD)
//    {
//        __HAL_RCC_GPIOD_CLK_ENABLE();
//    }
//    else if(get_port_from_name(name) == GPIOE)
//    {
//        __HAL_RCC_GPIOE_CLK_ENABLE();
//    }
//}

//#ifdef __cplusplus
//}
//#endif

