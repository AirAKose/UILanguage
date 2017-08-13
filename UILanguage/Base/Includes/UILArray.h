#ifndef _UIL_TEMPLATED_ARRAY_HEADER_
#define _UIL_TEMPLATED_ARRAY_HEADER_

#include "./UILTypes.h"
#include "./UILMemory.h"
#include "./UILIterator.h"
#include "./UILRecurringTemplate.h"

namespace UIL
{
	template <typename TYPE>
	class ArrayBase: private RecurringTemplate<TYPE>
	{
	private:
		ArrayBase()					= delete;
		ArrayBase(ArrayBase& copy)	= delete;
		ArrayBase(ArrayBase&& move)	= delete;
		virtual ~ArrayBase()		= delete;

	public:
		FORCEINLINE TYPE::Iterator Begin()	{ return TYPE::Iterator::GetBegin(Self()); }
		FORCEINLINE TYPE::Iterator End()	{ return TYPE::Iterator::GetEnd(Self()); }

		template<typename FUNCTOR>
		TYPE& Sort(FUNCTOR predicate);
	};

	template<typename TYPE, ISIZE NUM>
	class SArray: public ArrayBase<SArray<TYPE,NUM>>
	{
	private:
		TYPE arr[NUM];
	public:


		template<ISIZE OtherNum>
		SArray(SArray<TYPE, OtherNum>& copy);

		class Iterator : UIL::IteratorBase<SArray, Iterator>
		{

		public:
			Iterator(const SArray& item);
			Iterator(const SArray* pItem);
			Iterator(const Iterator& copy);
			Iterator(const Iterator&& move);
			~Iterator() final;

			Iterator&	Increment();
			Iterator&	Decrement();
			UBOOL		IsValid();

			static Iterator GetBegin(const SArray* pItem);
			static Iterator GetEnd(const SArray* pItem);
		};


		FORCEINLINE UINT	Length()	const { return NUM; }
		FORCEINLINE TYPE*	operator*()	const { return arr; }
	};

	template <typename TYPE>
	class DArray: public ArrayBase<DArray<TYPE>>, public IManagedMemory
	{
		ISIZE	_nLen;
		ISIZE	_nAvail;
		TYPE*	_pArr;

		FORCEINLINE TYPE* _CreateArray(ISIZE nSize) { return Memory()->NewArray<TYPE>(nSize); }
		FORCEINLINE void _DeleteArray(TYPE* pArray) { Memory()->DeleteArray<TYPE>(pArray); }
		FORCEINLINE void _CopyArray(TYPE* pDest, const TYPE* const pSrc, ISIZE nCount) { Memory()->Copy<TYPE>(pDest, pSrc, nCount); }
		//FORCEINLINE void _RenewArray(TYPE* pDest, ISIZE nCount) { Memory()->Renew<TYPE>(pDest, nCount); }

	public:
		ArrayBase(UINT nSize = 0) { _pArr = _CreateArray(nSize); _nLen = nSize; _nAvail = nSize; }
		ArrayBase(const TYPE* const pOther, ISIZE nSize) :ArrayBase(nSize) { _CopyArray(_pArr, pOther, nSize); }
		ArrayBase(const ArrayBase<TYPE>& copy) :ArrayBase(*copy, copy.Available()) {  }
		ArrayBase(ArrayBase<TYPE>&& move)
		{
			_pArr = move._pArr;
			_nLen = move._nLen;
			_nAvail = move._nAvail;

			move._pArr = NULL; // Null other array so it isn't deleted
		}

		FORCEINLINE UINT	Length()	const { return _nLen; }
		FORCEINLINE UINT	Available()	const { return _nAvail; }
		FORCEINLINE TYPE*	operator*()	const { return _pArr; }
	};

}

#endif