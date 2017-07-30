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

	typedef int16_t				INT16;
	typedef uint16_t			UINT16;

	typedef int32_t				INT32;
	typedef uint32_t			UINT32;

	typedef int64_t				INT64;
	typedef uint64_t			UINT64;

	typedef INT32				INT;
	typedef UINT32				UINT;

	typedef char				CHAR;
	typedef unsigned char		UCHAR;
	typedef signed char			SCHAR;

	typedef wchar_t				WCHAR;

#if UIL_USE_UTF_16
	typedef WCHAR				TCHAR;
#else
	typedef CHAR				TCHAR;
#endif

	/* Fractional Types */
	typedef float				FLOAT;
	typedef double				DOUBLE;

	/* String Types */
	typedef TCHAR*				CSTRING;

	/* Misc Types */
	typedef UBYTE				BITFIELD;
	typedef UINT64				ISIZE;
}

#if _MSC_VER
#define FORCEINLINE		__forceinline
#else
#define FORCEINLINE		inline
#endif

/* Predefined Values */
#define FALSE			0
#define TRUE			1

#define NULL			0

#endif
