#ifndef _UIL_MANAGED_MEMORY_HEADER_
#define _UIL_MANAGED_MEMORY_HEADER_

#include "./UILMemoryManager.h"

namespace UIL
{
	class IMemoryManager;

	class IManagedMemory
	{
	private:
		IMemoryManager* pMemManager;

	protected:
		IManagedMemory(IMemoryManager* pMemoryManager = DEFAULT_MEM_MANAGER):
			pMemManager(pMemoryManager)
		{ }

	public:
		FORCEINLINE IMemoryManager* Memory() const
		{
			return pMemManager;
		}
	};
}

#endif
