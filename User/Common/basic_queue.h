#ifndef _basic_queue_h_
#define _basic_queue_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"

typedef struct
{
	uint8_t * buf;
	uint16_t head;
	uint16_t tail;
	uint16_t size_total;
	uint16_t size_free;
}basic_queue_t;

void basic_queue_init(basic_queue_t * const me,void * buf,uint16_t size);
bool basic_queue_push(basic_queue_t * const me,void * buf,uint16_t size);
uint16_t basic_queue_pull(basic_queue_t * const me,void * buf,uint16_t size);
uint16_t basic_queue_pop(basic_queue_t * const me,uint16_t size);
uint16_t basic_queue_pull_pop(basic_queue_t * const me,void * buf,uint16_t size);
void basic_queue_clear(basic_queue_t * const me);
uint16_t basic_queue_get_size_free(basic_queue_t * const me);
bool basic_queue_is_empty(basic_queue_t * const me);
bool basic_queue_is_full(basic_queue_t * const me);

#ifdef __cplusplus
}
#endif

#endif