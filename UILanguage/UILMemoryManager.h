#ifndef _UIL_MEMORY_MANAGER_HEADER_
#define _UIL_MEMORY_MANAGER_HEADER_

#include "UILTypes.h"
#include "UILDebug.h"
#include <memory>
#include <memory.h>

namespace UIL
{
	class IMemoryManager
	{
	public:
		template<typename TYPE>
		virtual TYPE* New(UINT nCount) = 0;

		template<typename TYPE>
		virtual void Delete(TYPE* pVal) = 0;

		template<typename TYPE>
		virtual TYPE* Renew(UINT nCount) = 0;

		template<typename TYPE>
		virtual void* Reserve(UINT nCount) = 0;
		virtual void* Reserve(UINT nByteSize) = 0;

		template<typename TYPE>
		virtual void Copy(TYPE* pDest, const TYPE* const pSource, UINT nCount) = 0;
		virtual void Copy(void* pDest, const void* const pSource, UINT nByteSize) = 0;
	};

	class BasicMemoryManager : public IMemoryManager
	{
	public:
		template<typename TYPE>
		TYPE* New(UINT nCount = 1) { CHECK(nCount > 0); return new TYPE[nCount]; }

		template<typename TYPE>
		void Delete(TYPE*& pVal) { CHECK(pVal != NULL); delete pVal; pVal = NULL; };

		template<typename TYPE>
		TYPE* Renew(TYPE*& pVal, UINT nCount = 1)
		{
			CHECK(pVal != NULL);
			TYPE* renewed = New<TYPE>(nCount);
			Copy<TYPE>(renewed, pVal, nCount);
			Delete(pVal);
			pVal = renewed;
		}


		template<typename TYPE>
		void Copy(TYPE* pDest, const TYPE* const pSource, UINT nCount)
		{
			Copy(pDest, pSource, nCount * sizeof(TYPE));
		}

		FORCEINLINE void Copy(void* pDest, const void* const pSource, UINT nByteSize)
		{
			CHECK(pDest != NULL && pSource != NULL);
			memcpy(pDest, pSource, nByteSize);
		}
	};
}

#endif