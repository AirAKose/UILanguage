#ifndef _UIL_TYPES_HEADER_
#define _UIL_TYPES_HEADER_
#include <stdint.h>
/*
	UI Language Common Type Definitions
		Redefined for shorter / more readable variants
		Also allows for easy updates and platform-specific fixes

	{copyright} 2017 Erekose Craft
*/

/**/
namespace UIL
{
	/* Integer Types */
	typedef int8_t				BYTE;
	typedef uint8_t				UBYTE;

	typedef BYTE				BOOL;
	typedef UBYTE				UBOOL;

	typedef int16_t				SHORT;
	typedef uint16_t			USHORT;

	typedef int32_t				INT;
	typedef uint32_t			UINT;

	typedef int64_t				INT64;
	typedef uint64_t			UINT64;

	typedef uint32_t			DWORD;
	typedef uint64_t			QWORD;

	typedef char				CHAR;
	typedef wchar_t				WCHAR;

#if UIL_USE_UTF_16
	typedef WCHAR				TCHAR;
#else
	typedef CHAR				TCHAR;
#endif

	/* Decimal Types */
	typedef float				FLOAT;
	typedef double				DOUBLE;
}

#define FORCEINLINE		inline

#define BITFIELD(NAME)	UIL::UBYTE NAME:1
#define NIBBLE(NAME)	UIL::UBYTE NAME:4


/* Predefined Values */
#define FALSE			0
#define TRUE			1

#define NULL			0

#endif
