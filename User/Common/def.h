#ifndef _def_h_
#define _def_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "assert.h"
#include "export.h"
#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__CC_ARM) || defined(__CLANG_ARM)
	#include <stdarg.h>
	#define SECTION(x)				__attribute__((section(x)))
	#define	USED					__attribute__((used))
	#define ALIGN(n)				__attribute__((aligned(n)))
	#define WEAK					__attribute__((weak))
#elif defined(_IAR_SYSTEM)
	#include <stdarg.h>
	#define SECTION(x)				@ x
	#define	USED					__root
	#define PRAGMA(x)				_Pragma(#x)
	#define ALIGN(n)				PRAGMA(data_alignment=n)
	#define WEAK					__weak
#elif defined(__GNUC__)
	#include <stdarg.h>
	#define SECTION(x)				__attribute__((section(x)))
	#define	USED					__attribute__((used))
	#define ALIGN(n)				__attribute__((aligned(n)))
	#define WEAK					__attribute__((weak))
#else
	#error The Current Compiler is Not Supported
#endif

#ifdef __cplusplus
}
#endif

#endif
