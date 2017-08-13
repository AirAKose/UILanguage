#include "../Includes/UILMemoryManager.h"

using namespace UIL;

template<typename TYPE, typename ... ARGTYPES>
TYPE* IMemoryManager::New(ARGTYPES ... args)
{
	TYPE* self = static_cast<TYPE*>(Alloc(sizeof(TYPE) * nCount));
	if (self != nullptr)
	{
		Construct<TYPE>(self, args);
	}
	return self;
}

template<typename TYPE>
TYPE* IMemoryManager::NewArray(ISIZE nCount)
{
	CHECK(nCount > 0);
	void* pData = Alloc(sizeof(TYPE) * nCount + sizeof(UINT)); // Will always allocate a little more to keep count available
	TYPE* pArr = static_cast<TYPE*>((void*)((UCHAR*)pData + sizeof(UINT)));
	*((UINT*)pData) = nCount;
	for (UINT i = 0; i < nCount; ++i)
	{
		Construct<TYPE>(&pArr[i]); // call default constructor
	}
	return pArr;
}

template<typename TYPE>
void IMemoryManager::Delete(TYPE* pVal)
{
	if (pVal != nullptr)
	{
		Destruct<TYPE>(pVal);
		Free(pVal);
	}
}

template<typename TYPE>
void IMemoryManager::DeleteArray(TYPE* pVal)
{
	if (pVal != nullptr)
	{
		void* pStart = static_cast<UCHAR*>((void*)pVal) - sizeof(UINT); // Always puts a count before an array
		UINT count = *((UINT*)pStart);
		CHECK(count > 0);

		for (UINT i = 0; i < count; ++i)
		{
			Destruct<TYPE>(&pVal[i]);
		}
		Free(pStart);
	}
}




BasicMemoryManager* BasicMemoryManager::StaticInstance()
{
	static thread_local BasicMemoryManager GBasicManager;
	return &GBasicManager;
}

void* BasicMemoryManager::Alloc(ISIZE nByteSize)
{
	CHECK(nByteSize > 0);
	return malloc((size_t)nByteSize);
}

void* BasicMemoryManager::AllocZeroed(ISIZE nCount, ISIZE nSizePer)
{
	CHECK(nCount > 0);
	CHECK(nSizePer > 0);
	return calloc(nCount, nSizePer);
}

void BasicMemoryManager::Free(void* pVal)
{
	CHECK(pVal != nullptr);
	free(pVal);
}

void* BasicMemoryManager::Renew(void* pVal, ISIZE nSize)
{
	return realloc(pVal, (size_t)nSize);
}

void BasicMemoryManager::Copy(void* pDest, const void* const pSource, ISIZE nByteSize)
{
	CHECK(nByteSize > 0);
	CHECK(pDest != nullptr);
	CHECK(pSource != nullptr);
	memcpy(pDest, pSource, nByteSize);
}