#ifndef _UIL_RECURRING_TEMPLATE_HEADER_
#define _UIL_RECURRING_TEMPLATE_HEADER_

#include "./UILTypes.h"

namespace UIL
{
	// Serves two purposes: Provides an accessor to get the current object's type as well as makes a class's purpose obvious
	template<typename TYPE>
	class RecurringTemplate
	{
	private:
		RecurringTemplate()						= delete;
		RecurringTemplate(RecurringTemplate&)	= delete;
		RecurringTemplate(RecurringTemplate&&)	= delete;
		~RecurringTemplate()					= delete;

	protected:
		FORCEINLINE TYPE* Self() { return (TYPE*)this; }
	};
}

#endif
