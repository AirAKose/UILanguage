#ifndef _UIL_TEMPLATED_ARRAY_HEADER_
#define _UIL_TEMPLATED_ARRAY_HEADER_

#include "UILTypes.h"
#include "UILMemoryManager.h"

namespace UIL
{
	template <typename TYPE, IMemoryManager* MEM>
	class ArrayBase
	{
	private:
		UINT	_nLen;
		UINT	_nAvail;
		TYPE*	_pArr;

		FORCEINLINE TYPE* _CreateArray(UINT nSize) { return MEM->New<TYPE>(nSize); }
		FORCEINLINE void _DeleteArray(TYPE* pArray) { MEM->Delete<TYPE>(pArray); }
		FORCEINLINE void _CopyArray(TYPE* pDest, const TYPE* const pSrc, UINT nCount) { MEM->Copy<TYPE>(pDest, pSrc, nCount); }
		FORCEINLINE void _RenewArray(TYPE* pDest, UINT nCount) { MEM->Renew<TYPE>(pDest, nCount); }

	public:
		ArrayBase(UINT nSize = 0) { _pArr = _CreateArray(nSize); _nLen = nSize; _nAvail = nSize; }
		ArrayBase(const TYPE* const pOther, UINT nSize) :ArrayBase(nSize) { _CopyArray(_pArr, pOther, nSize); }
		ArrayBase(const ArrayBase<TYPE>& copy):ArrayBase(*copy, copy.Available()) {  }
		ArrayBase(ArrayBase<TYPE>&& move)
		{
			_pArr	= move._pArr;
			_nLen	= move._nLen;
			_nAvail	= move._nAvail;
			
			move._pArr = NULL; // Null other array so it isn't deleted
		}

		~ArrayBase() { _DeleteArray(_pArr); }

		FORCEINLINE UINT	Length() const		{ return _nLen; }
		FORCEINLINE UINT	Available() const	{ return _nAvail; }

		void				Reserve(UINT nCount);

		void				PushBack(const TYPE& item);
		void				PushFront(const TYPE& item);
		void				Insert(const TYPE& item, UINT nIndex);
		void				Append();

		UBOOL				operator==(const ArrayBase<TYPE>& other) const;
		TYPE&				operator[](UINT nIndex);
		FORCEINLINE TYPE*	operator*() const { return _pArr; }
	};

}

#endif