#ifndef _UIL_DEBUG_FUNCTIONS_HEADER_
#define _UIL_DEBUG_FUNCTIONS_HEADER_

#if _DEBUG || DEBUG
#include <exception>
#include <iostream>
#include <stdio.h>

class CheckFail : public std::exception
{
public:
	CheckFail(const char* str): std::exception(str) {}
	operator const char*() { return what(); }
};

#define CHECK(STATEMENT) if( !( STATEMENT ) ) throw CheckFail("Assertion failed check " #STATEMENT )

#elif COMPILER_SUPPORTS_NOOP

#define ERROR __noop
#define CHECK __noop

#else

#define ERROR(...)
#define CHECK(...)

#endif

#endif