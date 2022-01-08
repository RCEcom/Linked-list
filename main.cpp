#include <iostream>
#include "CArr.h"

namespace mystd
{
	void myendl()
	{
		wprintf(L"\n");
	}

	class CMyOStream
	{
	public:
		CMyOStream& operator << (int _idata)
		{
			printf("%d", _idata);
			return *this;
		}
		CMyOStream& operator << (const wchar_t* _idata)
		{
			wprintf(L"%s", _idata);
			return *this;
		}
		CMyOStream& operator << (void(*pfuc)(void))
		{
			pfuc();
			return *this;
		}
	};

	class CMyOstream_input
	{
	public:
		CMyOstream_input& operator >> (int& _idata)
		{
			scanf_s("%d", &_idata);
			return *this;
		}
	};
	CMyOstream_input mycin;
	CMyOStream mycout;
}
int main(void)
{
	//직접 구현한 std::cout, std::endl, std::cin
	CList<int> myList;
	myList.push_back(100);
	myList.push_back(200);
	myList.push_back(300);	
	CList<int>::iterator mylister = myList.begin();
	for (mylister; mylister != myList.end(); mylister++)
	{
		mystd::mycout << *mylister << mystd::myendl;
	}
	mylister = myList.begin();
	std::cout << "<===============================>" << std::endl;
	mylister = myList.erase(mylister);
	for (mylister; mylister != myList.end(); mylister++)
	{
		mystd::mycout << *mylister << mystd::myendl;
	}
	return 0;
} 