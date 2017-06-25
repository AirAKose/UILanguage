#ifndef _UIL_DEBUG_FUNCTIONS_HEADER_
#define _UIL_DEBUG_FUNCTIONS_HEADER_

#if _DEBUG || DEBUG
#include <stdio.h>

#define ERROR(TEXT) throw TEXT
#define CHECK(STATEMENT) if(!(STATEMENT)) ERROR("Assertion failed check "#STATEMENT)

#elif COMPILER_SUPPORTS_NOOP

#define ERROR __noop
#define CHECK __noop

#else

#define ERROR(...)
#define CHECK(...)

#endif

#endif