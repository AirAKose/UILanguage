#ifndef _UIL_MEMORY_MANAGER_HEADER_
#define _UIL_MEMORY_MANAGER_HEADER_

#include "./UILTypes.h"
#include "./UILDebug.h"
#include <memory>
#include <memory.h>

namespace UIL
{
	class IMemoryManager
	{
	public: // Override these
		virtual void*	Alloc(ISIZE nByteSize)											= 0;
		virtual void*	AllocZeroed(ISIZE nCount, ISIZE nSizePer)						= 0;
		virtual void	Free(void* pVal)												= 0;
		virtual void*	Renew(void* pVal, ISIZE nSize)									= 0;
		virtual void	Copy(void* pDest, const void* const pSource, ISIZE nByteSize)	= 0;

	public: // convenience / functionality for additional use
		IMemoryManager()						= default;
		IMemoryManager(IMemoryManager& other)	= delete;
		IMemoryManager(IMemoryManager&& other)	= delete;
		virtual ~IMemoryManager()				= default;

		template<typename TYPE, typename ... ARGTYPES>
		TYPE* New(ARGTYPES ... args);

		template<typename TYPE>
		TYPE* NewArray(ISIZE nCount);

		template<typename TYPE>
		void Delete(TYPE* pVal);

		template<typename TYPE>
		void DeleteArray(TYPE* pVal);

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
	};

	// An example memory manager layout. Not to be extended, essentially works the same as ::new and ::delete
	class BasicMemoryManager : public IMemoryManager
	{
	public:
		// Uses a static accessor with a static local variable so the manager is only created when used
		static BasicMemoryManager* StaticInstance();

		void*	Alloc(ISIZE nByteSize)											final;
		void*	AllocZeroed(ISIZE nCount, ISIZE nSizePer)						final;
		void	Free(void* pVal)												final;
		void*	Renew(void* pVal, ISIZE nSize)									final;
		void	Copy(void* pDest, const void* const pSource, ISIZE nByteSize)	final;
	};

	/*class IManagedMemory
	{
	private:
		IMemoryManager* pMemManager;
		IManagedMemory(IMemoryManager* pManager = GBasicMemoryManager) : pMemManager(pManager) {}
	};*/
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