#include "rArrayList_sample.h"
#include "ryimTestUtility.h"


testArrayList::testArrayList()
{

}
testArrayList::~testArrayList()
{

}

void testArrayList::test()
{
	testInitial();
	testInsert();
	testErase();
}

void testArrayList::testInitial()
{
	typedef Ryim::arraylist<int> myvec;
	typedef Ryim::arraylist<int>::iterator myvecIt;
	ryimTestTimer timer("arraylist initial");

	myvec testInitial1(3);
	testInitial1.push_back(52);
	testInitial1.push_back(56);
	testInitial1.push_back(50);
	printCapacitySize(testInitial1);
	testInitial1.push_back(66);
	printCapacitySize(testInitial1);
	printstream<myvec>(testInitial1, std::string("ArrayList testInitial1:"));

	std::cout << testInitial1.front() << std::endl;
	std::cout << testInitial1.back() << std::endl;
	std::cout << testInitial1[3] << std::endl;

#if _MSC_VER  < 1800
#else
	Ryim::arraylist<int> testInitial2{ 1,5,2,8,9,7,3 };
	print<myvec>(testInitial2, std::string("ArrayList testInitial2:"));
#endif

	Ryim::arraylist<int> testInitial3 = Ryim::Assign::list_of(0)(2)(3);
	print<myvec>(testInitial3, std::string("ArrayList testInitial3:"));

	Ryim::arraylist<int> testInitial4 = (Ryim::Assign::list_of(0), 1, 3, 5, 6);
	print<myvec>(testInitial4, std::string("ArrayList testInitial4:"));
}

void testArrayList::testInsert()
{
	typedef Ryim::arraylist<int> myvec;
	typedef Ryim::arraylist<int>::iterator myvecIt;
	
	myvec testInsert1;
	testInsert1.reserve(5);
	testInsert1 = { 52,56,50,66 };

	myvec testInsert2(8);
	testInsert2 = { 1,1,2,3,5,8,13,21 };

	myvec testInsert3(2);
	testInsert3 = { 89,99 };
	///////////////////////////////////////////////////////////////////

	ryimTestTimer timer("arraylist insert");
	testInsert1.insert(testInsert1.begin(), 73);
	printCapacitySize(testInsert1);
	printstream(testInsert1, std::string("ArrayList testInsert1 after inserting 73:"));
	testInsert1.insert(testInsert1.end(), 2, 100);
	printCapacitySize(testInsert1);
	printstream(testInsert1, std::string("ArrayList testInsert1 after inserting 100, 100:"));

	myvecIt it1 = testInsert1.insert(testInsert1.begin() + 1, testInsert3.begin(), testInsert3.end());
	print(testInsert1, std::string("ArrayList testInsert1 after inserting testInsert3:"));
	std::cout << *it1 << std::endl;
	myvecIt it2 = testInsert1.insert(testInsert1.begin() + 2, testInsert2.begin(), testInsert2.end());
	print(testInsert1, std::string("ArrayList testInsert1 after inserting testInsert2:"));
	std::cout << *it2 << std::endl;
}

void testArrayList::testErase()
{
	typedef Ryim::arraylist<int> myvec;
	typedef Ryim::arraylist<int>::iterator myvecIt;

	myvec testErease1(20);
	testErease1 = { 1,1,2,3,5,8,13,21,34,55,89 };
	printCapacitySize(testErease1);

	ryimTestTimer timer("arraylist erase");
	myvecIt itreturn1 = testErease1.erase(testErease1.begin());
	print<myvec>(testErease1, std::string("ArrayList a1 after erease the first element:"));
	std::cout << "next element: " << *itreturn1 << std::endl;

	myvecIt itreturn2 = testErease1.erase(testErease1.end()-1);
	print<myvec>(testErease1, std::string("ArrayList a1 after erease the last element:"));
	std::cout << "next element: " << *itreturn2 << std::endl;

	myvecIt itreturn3 = testErease1.erase(testErease1.begin() + 3);
	print<myvec>(testErease1, std::string("ArrayList a1 after erease the third element:"));
	std::cout << "next element: " << *itreturn3 << std::endl;

	testErease1.pop_back();
	print<myvec>(testErease1, std::string("ArrayList a1 after pop back the last element:"));

	testErease1.clear();
	if (testErease1.empty())
	{
		std::cout << "It's already empty." << std::endl;
	}
	else
	{
		std::cout << "Failed to clear." << std::endl;
	}
}