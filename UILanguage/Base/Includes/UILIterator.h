#ifndef _UIL_ITERATOR_HEADER_
#define _UIL_ITERATOR_HEADER_

#include "./UILTypes.h"
#include "./UILRecurringTemplate.h"

namespace UIL
{
	// Uses the Curiously Recurring Template Pattern to circumvent V-Tables
	template<typename CONTAINER, typename ITER>
	class IteratorBase: private RecurringTemplate<ITER>
	{
	public:
		IteratorBase()					= delete;
		IteratorBase(IteratorBase&)		= delete;
		IteratorBase(IteratorBase&&)	= delete;
		virtual ~IteratorBase()			= delete;

		FORCEINLINE operator bool()
		{
			return Self()->IsValid();
		}

		FORCEINLINE ITER& operator++()
		{
			return Self()->Increment();
		}

		FORCEINLINE ITER& operator++(UINT nIndicatesPostIncrement)
		{
			return Self()->Increment();
		}

		FORCEINLINE ITER& operator--()
		{
			return Self()->Decrement();
		}

		FORCEINLINE ITER& operator--(UINT nIndicatesPostIncrement)
		{
			return Self()->Decrement();
		}
	};
}

#endif