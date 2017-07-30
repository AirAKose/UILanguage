#include "UILMemoryManager.h"
#include <iostream>
using namespace UIL;

BasicMemoryManager* GBasicManager = new BasicMemoryManager();
#define basic_new new(GBasicManager)
#define basic_new_array GBasicManager->NewArray

#define basic_delete GBasicManager->Delete
#define basic_delete_array GBasicManager->DeleteArray

class MyTestClass
{
	UINT index;
public:
	MyTestClass()
	{
		index = 0;
		std::cout << "Default Constructed properly!" << std::endl;
	}
	MyTestClass(UINT i)
	{
		index = (UINT)i;
		std::cout << "Constructed with index: " << i << std::endl;
	}
	~MyTestClass()
	{
		std::cout << "Destructor is called on: " << index << std::endl;
	}
};

int main(char** pArgs, int nArgCount)
{
	ISIZE nSize = 1;
	MyTestClass* test = basic_new_array<MyTestClass>(nSize);
	MyTestClass* testObj = basic_new MyTestClass(nSize+1);


	for (UINT i = 0; i < nSize; ++i)
	{
		test[i] = i;
	}

	basic_delete(testObj);
	basic_delete_array(test);

	TCHAR str[255];
	std::cin >> str;

	delete GBasicManager;
	return 0;
}