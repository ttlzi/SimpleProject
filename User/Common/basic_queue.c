#include "basic_queue.h"

LOG_TAG("basic_queue.c");

void basic_queue_init(basic_queue_t * const me,void * buf,uint16_t size)
{
	assert(me != NULL);
	assert(buf != NULL);
	
	me->buf = (uint8_t *)buf;
	me->size_total = size;
	me->size_free = size;
	me->head = 0;
	me->tail = 0;
}

bool basic_queue_push(basic_queue_t * const me,void * buf,uint16_t size)
{
	assert(me != NULL);
    assert(me->buf != NULL);
	assert(buf != NULL);
	
	if(size > me->size_free)
		return false;
	else
	{
		for(uint16_t index = 0;index < size;index++)
		{
			me->buf[me->head] = ((uint8_t *)buf)[index];
			me->head = (me->head + 1) % me->size_total;
			me->size_free--;
		}
	}
	return true;
}

uint16_t basic_queue_pull(basic_queue_t * const me,void * buf,uint16_t size)
{
	assert(me != NULL);
    assert(me->buf != NULL);
	assert(buf != NULL);
	
	uint16_t size_data = me->size_total - me->size_free;
	uint16_t size_pull = size > size_data ? size_data : size;
	for(uint16_t index = 0;index < size_pull;index++)
	{
		((uint8_t *)buf)[index] = me->buf[(me->tail + index) % me->size_total];
	}
	return size_pull;
}

uint16_t basic_queue_pop(basic_queue_t * const me,uint16_t size)
{
    assert(me != NULL);
    assert(me->buf != NULL);

	uint16_t size_data = me->size_total - me->size_free;
	uint16_t size_pop = size > size_data ? size_data : size;
	
	me->tail = (me->tail + size_pop) % me->size_total;
	me->size_free += size_pop;
	
	return size_pop;
}

uint16_t basic_queue_pull_pop(basic_queue_t * const me,void * buf,uint16_t size)
{
    assert(me != NULL);
    assert(me->buf != NULL);
    assert(buf != NULL);

	uint16_t size_data = me->size_total - me->size_free;
    uint16_t size_pull_pop = size > size_data ? size_data : size;
	
	for(uint16_t index = 0;index < size_pull_pop;index++)
	{
		((uint8_t *)buf)[index] = me->buf[(me->tail + index) % me->size_total];
	}
	
	me->tail = (me->tail + size_pull_pop) % me->size_total;
	me->size_free += size_pull_pop;
	return size_pull_pop;
}

void basic_queue_clear(basic_queue_t * const me)
{
	assert(me != NULL);
	assert(me->buf != NULL);
	
	me->size_free = me->size_total;
	me->head = me->tail = 0;
}

uint16_t basic_queue_get_size_free(basic_queue_t * const me)
{
    assert(me != NULL);
    assert(me->buf != NULL);

	return me->size_free;
}

uint16_t basic_queue_get_size_total(basic_queue_t * const me)
{
    assert(me != NULL);
    assert(me->buf != NULL);

    return me->size_total;
}

bool basic_queue_is_empty(basic_queue_t * const me)
{
    assert(me != NULL);
    assert(me->buf != NULL);

	return ((me->size_free == me->size_total) ? true : false);
}

bool basic_queue_is_full(basic_queue_t * const me)
{
    assert(me != NULL);
    assert(me->buf != NULL);

	return ((me->size_free == 0) ? true : false);
}