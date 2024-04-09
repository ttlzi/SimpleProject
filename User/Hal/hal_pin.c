//#include "hal_pin.h"

//#ifdef __cplusplus
//extern "C" {
//#endif

//LOG_TAG("hal_pin.c");

//void hal_pin_register(hal_pin_t * const me,const char * name,const hal_pin_ops_t * ops,void * user_data)
//{
//    assert(me != NULL);
//    assert(name != NULL);
//    assert(ops != NULL);

//    device_attr_t attr = {
//            .name = (char *)name,
//            .sole = true,
//            .type = 10,
//    };

//    device_register(&me->super,&attr);
//    me->super.user_data = user_data;
//    me->super.ops = NULL;
//    me->ops = ops;
//    me->ops->init(me);
//    me->mode = PIN_MODE_MAX;
//}

//void hal_pin_set_mode(device_t * const me,uint8_t mode)
//{
//    assert(me != NULL);
//    assert(mode < PIN_MODE_MAX);

//    hal_pin_t * pin = HAL_PIN_CAST(me);

//    if(pin->mode != mode)
//    {
//        pin->ops->set_mode(pin,mode);
//        pin->mode = mode;
//    }
//}

//void hal_pin_set_status(device_t * const me,bool status)
//{
//    assert(me != NULL);
//    assert(HAL_PIN_CAST(me)->mode < PIN_MODE_MAX);

//    hal_pin_t * pin = HAL_PIN_CAST(me);

//    if(status != pin->status && pin->mode > PIN_MODE_INPUT_PULLDOWN)
//    {
//        if(true == pin->ops->set_status(pin,status))
//            pin->status = status;
//    }
//}

//void hal_pin_get_status(device_t * const me,bool * status)
//{
//    assert(me != NULL);
//    assert(HAL_PIN_CAST(me)->mode < PIN_MODE_MAX);

//    hal_pin_t * pin = HAL_PIN_CAST(me);

//    if(pin->mode <= PIN_MODE_INPUT_PULLDOWN)
//    {
//        bool temp;
//        if(true == pin->ops->get_status(pin,&temp))
//        {
//            pin->status = temp;
//            *status = temp;
//        }
//    }
//}

//#ifdef __cplusplus
//}
//#endif

///*
// *  本文件实现对引脚的抽象化
// */
