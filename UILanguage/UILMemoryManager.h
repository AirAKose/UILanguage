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
		virtual void*	Alloc(ISIZE nByteSize) = 0;
		virtual void*	AllocZeroed(ISIZE nCount, ISIZE nSizePer) = 0;
		virtual void	Free(void* pVal) = 0;
		virtual void*	Renew(void* pVal, ISIZE nSize) = 0;

	public:
		template<typename TYPE, typename ... ARGTYPES>
		TYPE* New(ARGTYPES ... args)
		{
			TYPE* self = static_cast<TYPE*>(Alloc(sizeof(TYPE) * nCount));
			Construct<TYPE>(self, args);
			return self;
		}

		template<typename TYPE>
		TYPE* NewArray(ISIZE nCount)
		{
			CHECK(nCount > 0);
			void* pData = Alloc(sizeof(TYPE) * nCount + sizeof(UINT)); // Will always allocate a little more to keep count available
			TYPE* pArr = static_cast<TYPE*>((void*)((UCHAR*)pData + sizeof(UINT)));
			*((UINT*)pData) = nCount;
			for (UINT i = 0; i < nCount; ++i)
			{
				Construct<TYPE>( &pArr[i] ); // call default constructor
			}
			return pArr;
		}

		template<typename TYPE>
		void Delete(TYPE* pVal)
		{
			CHECK(pVal != nullptr);
			Destruct<TYPE>(pVal);
			Free(pVal);
		}

		template<typename TYPE>
		void DeleteArray(TYPE* pVal)
		{
			CHECK(pVal != nullptr);
			void* pStart = static_cast<UCHAR*>((void*)pVal) - sizeof(UINT); // Always puts a count before an array
			UINT count = *((UINT*)pStart);
			CHECK(count > 0);

			for (UINT i = 0; i < count; ++i)
			{
				Destruct<TYPE>(&pVal[i]);
			}
			Free(pStart);
		}

		template<typename TYPE, typename ... ARGTYPES>
		FORCEINLINE void Construct(TYPE* pObject,ARGTYPES ... args)
		{
			CHECK(pObject != nullptr);
			new(pObject) TYPE(args...);
		}

		/************************************************
		void Destruct(TYPE* pObject)
			Will call the destructor on an object
			WARNING: Only call on objects created with {@code Alloc} and manually constructed previously
				Otherwise you may end up double destructing something
		*************************************************/
		template<typename TYPE>
		FORCEINLINE void Destruct(TYPE* pObject)
		{
			CHECK(pObject != nullptr);
			pObject->~TYPE();
		}

		template<typename TYPE>
		FORCEINLINE void Copy(TYPE* pDest, const TYPE* const pSource)
		{
			Copy(static_cast<void*>(pDest), static_cast<void*>(pSource), sizeof(TYPE));
		}
		template<typename TYPE>
		FORCEINLINE void Copy(TYPE* pDest, const TYPE* const pSource, ISIZE nCount)
		{
			Copy(static_cast<void*>(pDest), static_cast<void*>(pSource), sizeof(TYPE) * nCount);
		}
		FORCEINLINE void Copy(void* pDest, const void* const pSource, ISIZE nByteSize)
		{
			CHECK(nByteSize > 0);
			CHECK(pDest != nullptr);
			CHECK(pSource != nullptr);
			memcpy(pDest, pSource, nByteSize);
		}
	};

	// An example memory manager layout
	class BasicMemoryManager : public IMemoryManager
	{
	public:
		void* Alloc(ISIZE nByteSize) final
		{
			CHECK(nByteSize > 0);
			return malloc((size_t)nByteSize);
		}

		void* AllocZeroed(ISIZE nCount, ISIZE nSizePer) final
		{
			CHECK(nCount > 0);
			CHECK(nSizePer > 0);
			return calloc(nCount, nSizePer);
		}

		void Free(void* pVal) final
		{
			CHECK(pVal != nullptr);
			free(pVal);
		}

		void* Renew(void* pVal, ISIZE nSize) final
		{
			return realloc(pVal, (size_t)nSize);
		}
	};
}

// Use placement-new for memory manager profiles
void* operator new(size_t nSize, UIL::IMemoryManager* pManager)
{
	CHECK(pManager != nullptr);
	return pManager->Alloc(nSize);
}
void* operator new[](size_t nSize, UIL::IMemoryManager* pManager)
{
	CHECK(pManager != nullptr);
	return pManager->Alloc(nSize);
}

void operator delete(void* pVal, UIL::IMemoryManager* pManager)
{
	if (pVal != nullptr)
	{
		pManager->Free(pVal);
	}
}
void operator delete[](void* pVal, UIL::IMemoryManager* pManager)
{
	if (pVal != nullptr)
	{
		pManager->Free(pVal);
	}
}

#endif