#include "rHeap_sample.h"
#include "../src/rArrayList.h"
#include "../src/rHeap.h"
#include "ryimTestUtility.h"


testHeap::testHeap()
{

}
testHeap::~testHeap()
{

}

void testHeap::test()
{
	typedef Ryim::arraylist<int> myvec;
	typedef Ryim::arraylist<int>::iterator myvecIt;
	{
		myvec temp1 = { 26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78 };
		printstream(temp1, std::string("ArrayList testInitial1:"));
		ryimTestTimer timer("rHeap");
		Ryim::heap::buildHeap<myvecIt>()(temp1.begin(), temp1.end());
		printstream(temp1, std::string("buildHeap:"));

		std::cout << std::boolalpha << Ryim::heap::isHeap<myvecIt>()(temp1.begin(), temp1.end()) << std::endl;
		temp1.push_back(3);
		Ryim::heap::pushHeap<myvecIt>()(temp1.begin(), temp1.end());
		printstream(temp1, std::string("pushHeap:"));

		myvecIt ret = Ryim::heap::popHeap<myvecIt>()(temp1.begin(), temp1.end());
		print(temp1.begin(), ret, std::string("popHeap:"));
		std::cout << *ret << std::endl;


	}

}