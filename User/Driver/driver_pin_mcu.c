#include "driver_pin.h"

LOG_TAG("driver_pin.c");

static bool check_pin_name_valid(const char *name);
static GPIO_TypeDef *get_port_from_name(const char *name);
static uint16_t get_pin_from_name(const char *name);
static void gpio_clock_enable(const char *name);

static bool _init(driver_pin_t * const me);
static bool _set_mode(driver_pin_t * const me,uint8_t mode);
static bool _set_status(driver_pin_t * const me,uint8_t pin_status);
static bool _get_status(driver_pin_t * const me,uint8_t * pin_status);

static bool check_pin_name_valid(const char *name)
{
    bool valid = true;

    if ((strlen(name) != 4) || name[1] != '.')
    {
        valid = false;
    }
    else if (!(name[0] >= 'A' && name[0] <= 'F'))
    {
        valid = false;
    }
    else if (!(name[2] >= '0' && name[2] <= '9'))
    {
        valid = false;
    }
    else if (!(name[3] >= '0' && name[3] <= '9'))
    {
        valid = false;
    }

    char *str_num = (char *)&name[2];
    uint16_t pin_num = strtol(str_num,NULL,10);
    if (pin_num < 0 || pin_num >= 16)
    {
        valid = false;
    }

    return valid;
}

static GPIO_TypeDef *get_port_from_name(const char *name)
{
    static const GPIO_TypeDef *port_table[] =
    {
        GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, 
    };

    return (GPIO_TypeDef *)port_table[name[0] - 'A'];
}

static uint16_t get_pin_from_name(const char *name)
{
    char *str_num = (char *)&name[2];
    uint16_t pin_num = strtol(str_num,NULL,10);

    return (uint16_t)(1 << pin_num);
}

static void gpio_clock_enable(const char *name)
{
    /* Enable the clock. */
    if (get_port_from_name(name) == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if (get_port_from_name(name) == GPIOB)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if (get_port_from_name(name) == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
    else if (get_port_from_name(name) == GPIOD)
    {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
    else if (get_port_from_name(name) == GPIOE)
    {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    }
}

static bool _init(driver_pin_t * const me)
{
	assert(me != NULL);
	assert(me->pin_name != NULL);
	
	gpio_clock_enable(me->pin_name);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Pin = me->pin_num;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(me->pin_port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(me->pin_port, me->pin_num, GPIO_PIN_RESET);
	me->pin_mode = PIN_MODE_OUTPUT_PP;
	me->pin_status = false;
	
	return true;
}

static bool _set_mode(driver_pin_t * const me,uint8_t mode)
{
	assert(me != NULL);	
	assert(mode < PIN_MODE_MAX);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (mode == PIN_MODE_INPUT)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_PP)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
    }
	else
		return false;
    GPIO_InitStruct.Pin = me->pin_num;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(me->pin_port, &GPIO_InitStruct);
	me->pin_mode = mode;
	
	return true;
}

static bool _set_status(driver_pin_t * const me,uint8_t pin_status)
{
	assert(me != NULL);	
	
	if(me->pin_status != pin_status && me->pin_mode > PIN_MODE_INPUT_PULLDOWN)
	{
		HAL_GPIO_WritePin(me->pin_port,me->pin_num,pin_status ? GPIO_PIN_SET : GPIO_PIN_RESET);
		me->pin_status = pin_status ? GPIO_PIN_SET : GPIO_PIN_RESET;
		return true;
	}
	
	return false;
}

static bool _get_status(driver_pin_t * const me,uint8_t * pin_status)
{
	assert(me != NULL);	
	
	if(me->pin_mode <= PIN_MODE_INPUT_PULLDOWN)
	{
		*pin_status = HAL_GPIO_ReadPin(me->pin_port,me->pin_num);
		me->pin_status = *pin_status;
		return true;
	}
	
	return false;
}

void driver_pin_init(driver_pin_t * const me,const char * name,const char * pin_name)
{
	assert(me != NULL);
	assert(name != NULL);
	assert(pin_name != NULL);
	
	me->pin_name = (char *)pin_name;
	me->pin_port = get_port_from_name(me->pin_name);
	me->pin_num = get_pin_from_name(me->pin_name);
	me->pin_mode = PIN_MODE_MAX;
	me->pin_status = 0xff;
	
	me->init = _init;
	me->set_mode = _set_mode;
	me->set_status = _set_status;
	me->get_status = _get_status;
	
	me->init(me);
	me->set_mode(me,PIN_MODE_OUTPUT_PP);
	
	device_pin_register(&me->super,name,me);
	
}
