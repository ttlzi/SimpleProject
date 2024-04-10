#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif

static void module_null_init(void);
static void _get_init_export_table(void);
static void _export_func_init(uint8_t level);

INIT_EXPORT(module_null_init,EXPORT_LEVEL_0);

static _export_t * _export_init_table = NULL;
static uint32_t _export_init_count = 0;
static uint8_t _export_init_level_max = EXPORT_LEVEL_0;

void export_run(void)
{
	_get_init_export_table();
	for(uint8_t level = 0;level <= _export_init_level_max;level++)
		_export_func_init(level);
}

static void _get_init_export_table(void)
{
	_export_t *func_block = (_export_t *)&init_module_null_init;
    uint32_t address_last = 0;
    
    while (1)
    {
        address_last = ((uint32_t)func_block - sizeof(_export_t));
        _export_t *table = (_export_t *)address_last;
        if (table->magic_head != EXPORT_ID_HEAD || table->magic_tail != EXPORT_ID_TAIL)
            break;
        func_block = table;
    }
    _export_init_table = func_block;

    uint32_t i = 0;
    while (1)
    {
        if (_export_init_table[i].magic_head == EXPORT_ID_HEAD && _export_init_table[i].magic_tail == EXPORT_ID_TAIL)
        {
            if (_export_init_table[i].level > _export_init_level_max)
                _export_init_level_max = _export_init_table[i].level;
            i ++;
        }
        else
            break;
    }
    _export_init_count = i;
}

static void _export_func_init(uint8_t level)
{
	for(uint32_t index = 0;index < _export_init_count;index++)
	{
		if(_export_init_table[index].level == level)
		{
			((void (*)(void))_export_init_table[index].func)();
		}
	}
}

static void module_null_init(void)
{
	// Nothing at all
}

#ifdef __cplusplus
}
#endif