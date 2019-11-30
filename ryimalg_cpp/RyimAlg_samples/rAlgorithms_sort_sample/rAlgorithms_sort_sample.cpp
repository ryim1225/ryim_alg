#include "rAlgorithms_sort_sample.h"
#include "ryimTestUtility.h"


testAlgroithmsSort::testAlgroithmsSort()
{

}
testAlgroithmsSort::~testAlgroithmsSort()
{

}

void testAlgroithmsSort::test()
{
	typedef Ryim::arraylist<int> myvec;
	typedef Ryim::arraylist<int>::iterator myvecIt;

	{
		int temp1[] = { 26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78 };
		print(temp1, sizeof(temp1) / sizeof(int));
		ryimTestTimer timer("selection sort--1");
		Ryim::Sort::SelectionSort<int>()(temp1, sizeof(temp1) / sizeof(int));
		print(temp1, sizeof(temp1) / sizeof(int));
	}

	{
		Ryim::arraylist<int> temp1 { 26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78 };
		print(temp1);
		ryimTestTimer timer("selection sort--2");
		Ryim::Sort::SelectionSort<int>()(temp1.begin(), temp1.end());
		print(temp1);
	}

	{
		int temp2[] = { 26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78 };
		print(temp2, sizeof(temp2) / sizeof(int));
		ryimTestTimer timer("quick sort-1");
		Ryim::Sort::QuickSort<int>()(temp2, (sizeof(temp2) / sizeof(int)) );
		print(temp2, sizeof(temp2) / sizeof(int));
	}

	{
		int temp3[] = { 26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78 };
		print(temp3, sizeof(temp3) / sizeof(int));
		ryimTestTimer timer("quick sort-2");
		Ryim::Sort::QuickSort<int>()(temp3, (sizeof(temp3) / sizeof(int)), false);
		print(temp3, sizeof(temp3) / sizeof(int));
	}
	
	{
		myvec temp4 = { 26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78 };
		printstream(temp4, std::string("ArrayList testInitial1:"));
		ryimTestTimer timer("heap sort");
		Ryim::Sort::HeapSort<myvecIt,Ryim::AlgTools::great<int> >()(temp4.begin(), temp4.end());
		printstream(temp4, std::string("Heap Sort:"));
	}
}