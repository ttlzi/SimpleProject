#ifndef _app_h_
#define _app_h_

#include "main.h"
#include "stm32f1xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "event_groups.h"
#include "stream_buffer.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "assert.h"
#include "log.h"

#include "driver_pin.h"

#ifdef __cplusplus
extern "C" {
#endif

void app_main(void);

#ifdef __cplusplus
}
#endif

#endif
