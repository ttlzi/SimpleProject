#ifndef _export_h_
#define	_export_h_

#ifdef __cplusplus
extern "C" {
#endif
/* include ------------------------------------------------------------------ */
#include "def.h"
/* public define ------------------------------------------------------------ */
#define		EXPORT_ID_HEAD				(0xabcd1234)
#define		EXPORT_ID_TAIL				(0xa1b2c3d4)
/* public define ------------------------------------------------------------ */
enum
{
	EXPORT_LEVEL_0 = 0,
	EXPORT_LEVEL_1,
	EXPORT_LEVEL_2,
	EXPORT_LEVEL_3,
	EXPORT_LEVEL_4,
	EXPORT_LEVEL_5,
	EXPORT_LEVEL_6,
	EXPORT_LEVEL_7,
	EXPORT_LEVEL_MAX,
};
/* public typedef ----------------------------------------------------------- */
typedef struct
{
	uint32_t magic_head;
	const char * name;
	void * func;
	uint8_t level;
	uint32_t magic_tail;
}_export_t;

#define		INIT_EXPORT(_func,_level)		USED const _export_t init_##_func SECTION("init_export") = 	\
{																										\
	.magic_head = EXPORT_ID_HEAD,																		\
	.name = #_func,																						\
	.func = (void *)&_func,																				\
	.level = _level,																					\
	.magic_tail = EXPORT_ID_TAIL,																		\
}
/* public functions --------------------------------------------------------- */
void export_run(void);
/* ----------------------------- end of file -------------------------------- */
#ifdef __cplusplus
}
#endif

#endif