#ifndef _R_ALGORITHMS_H_
#define _R_ALGORITHMS_H_

#include "rUtility.h"
#include "rGraph.h"
#include "rArrayList.h"
#include "rHeap.h"
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

namespace Ryim
{
	namespace Sort
	{
		//////////////////////////////////////////////////////////////////////////
		// Bubble Sort
		// Pseudo-code:
		//       for i <- 1 to length[A]-1
		//            do for j <- length[A] downto i
		//                 do  if A[j] < A[j-1]
		//                        then exchange A[j] <-> A[j-1] 
		//////////////////////////////////////////////////////////////////////////
		template<typename Elem, typename Comp = AlgTools::less<Elem> >
		struct BubbleSort
		{
			void operator()(Elem A[], int length)
			{
				for (int i = 0; i<length - 1; ++i)
				{
					for (int j = length - 1; j>i; --j)
					{
						if (Comp()(A[j], A[j - 1]))
						{
							AlgTools::swap(A, j, j - 1);
						}
					}
				}
			}
		};
		
		//////////////////////////////////////////////////////////////////////////
		// Selection Sort:
		// One of the simplest sorting algorithms works as follows: 
		// First, find the smallest item in the array, and exchange it with the first entry. 
		// Then, find the next smallest item and exchange it with the second entry. 
		// Continue in this way until the entire array is sorted. 
		// This method is called selection sort because it works by repeatedly selecting the smallest remaining item.
		//
		// Proposition:
		// Selection sort uses ~n2/2 compares and n exchanges to sort an array of length n.
		//
		// Bibliography:
		// http://algs4.cs.princeton.edu/21elementary/
		//////////////////////////////////////////////////////////////////////////
		template<typename Elem, typename Comp = AlgTools::less<Elem> >
		struct SelectionSort
		{
			typedef typename Ryim::arraylist<Elem>::iterator arrayIterator;
			void operator()(Elem A[], int length)
			{
				for (int i = 0; i < length - 1; ++i)
				{
					int minIndex = i;
					for (int j = i + 1; j < length; ++j)
					{
						if (Comp()(A[j], A[minIndex]))
						{
							minIndex = j;
						}
					}
					AlgTools::swap(A, i, minIndex);
				}
			}
			//-------------------------------------------------------------------------------//
			void operator()(arrayIterator first, arrayIterator end)
			{
				typedef typename Ryim::arraylist<Elem>::difference_type difference_type;
				difference_type length = end - first;

				for (difference_type i = 0; i < length - 1; ++i)
				{
					difference_type minIndex = i;
					for (difference_type j = i + 1; j < length; ++j)
					{
						if ( Comp()( (*(first + j)), (*(first + minIndex)) ) )
						{
							minIndex = j;
						}
					}
					std::iter_swap(first + i, first + minIndex);
				}
			}
		};
	
		//////////////////////////////////////////////////////////////////////////
		// Insertion Sort:
		// The algorithm that people often use to sort bridge hands is to consider the cards one at a time, 
		// inserting each into its proper place among those already considered (keeping them sorted). 
		// In a computer implementation, we need to make space for the current item by moving larger items one position to the right,
		// before inserting the current item into the vacated position.
		//
		// Proposition:
		// For randomly ordered arrays of length N with with distinct keys, 
		// insertion sort uses ~N2/4 compares and ~N2/4 exchanges on the average. 
		// The worst case is ~ N2/2 compares and ~ N2/2 exchanges and the best case is N-1 compares and 0 exchanges.
		//
		// Bibliography:
		// http://algs4.cs.princeton.edu/21elementary/
		//////////////////////////////////////////////////////////////////////////
		template<typename Elem, typename Comp = AlgTools::less<Elem> >
		struct InsertionSort
		{
			void operator()(Elem A[], int length)
			{
				for (int i = 1; i<length; ++i)
				{
					for (int j = i; (j>0) && (Comp()(A[j], A[j - 1])); --j)
					{
						AlgTools::swap(A, j, j - 1);
					}
				}
			}

			void operator()(Elem A[], int length, int increment)
			{
				for (int i = increment; i<length; i += increment)
				{
					for (int j = i; (j >= increment) && (Comp()(A[j], A[j - increment])); j -= increment)
					{
						AlgTools::swap(A, j, j - increment);
					}
				}
			}
			//-------------------------------------------------------------------------------//
			typedef typename Ryim::arraylist<Elem>::iterator arrayIterator;
			typedef typename Ryim::arraylist<Elem>::difference_type array_difference_type;

			void operator()(arrayIterator first, arrayIterator end)
			{

				array_difference_type length = end - first;

				for (int i = 1; i<length; ++i)
				{
					for (int j = i; (j>0) && ( Comp()(*(first+j), *(first + (j - 1))) ); --j)
					{
						std::iter_swap(first + j, first + (j - 1));
					}
				}
			}

			void operator()(arrayIterator first, arrayIterator end, unsigned int increment)
			{
				array_difference_type length = end - first;

				for (int i = increment; i<length; i += increment)
				{
					for (int j = i; (j >= increment) && ( Comp()(*(first + j), *(first + (j - increment))) ); j -= increment)
					{
						std::iter_swap(first + j, first + (j - increment));
					}
				}
			}
		};

		//////////////////////////////////////////////////////////////////////////
		// Shell Sort  or  diminishing increment sort:
		// Shellsort is a simple extension of insertion sort that gains speed by allowing exchanges of entries that are far apart,
		// to produce partially sorted arrays that can be efficiently sorted, eventually by insertion sort.
		// The idea is to rearrange the array to give it the property 
		// that taking every hth entry(starting anywhere) yields a sorted sequence. Such an array is said to be h - sorted.
		// By h-sorting for some large values of h, we can move entries in the array long distances and 
		// thus make it easier to h-sort for smaller values of h. 
		// Using such a procedure for any increment sequence of values of h that ends in 1 will produce a sorted array: that is shellsort.
		// (将序列分成子序列，然后分别对子序列进行排序，最后将子序列组合起来。
		// shell排序将数组元素分成“虚拟”子序列，每个子序列用插入排序方法进行排序；
		// 另一组子序列也是如此选取，然后排序，以此类推)。
		//
		// Property: 
		// The number of compares used by shellsort with the increments 1, 4, 13, 40, 121, 364, ... is 
		// bounded by a small multiple of N times the number of increments used.
		//
        // Proposition: 
		// The number of compares used by shellsort with the increments 1, 4, 13, 40, 121, 364, ... is O(N3/2).
		//
		// Bibliography:
		// http://algs4.cs.princeton.edu/21elementary/
		//////////////////////////////////////////////////////////////////////////
		template<typename Elem, typename Comp = AlgTools::less<Elem> >
		class ShellSort
		{
		public:
			explicit ShellSort(int increase = 3):m_increasement(increase)
			{
			}

			void operator()(Elem A[], int n)
			{
				initializeSequence(n);
				std::vector<int>::reverse_iterator itBegin = h.rbegin();
				std::vector<int>::reverse_iterator itEnd = h.rend();
				while (itBegin != itEnd)
				{
					InsertionSort<Elem, Comp>()(A, n, *itBegin);
					++itBegin;
				}
			}

			typedef typename Ryim::arraylist<Elem>::iterator arrayIterator;
			typedef typename Ryim::arraylist<Elem>::difference_type array_difference_type;

			void operator()(arrayIterator first, arrayIterator end)
			{
				array_difference_type length = end - first;
				initializeSequence(length);
				std::vector<int>::reverse_iterator itBegin = h.rbegin();
				std::vector<int>::reverse_iterator itEnd = h.rend();
				while (itBegin != itEnd)
				{
					InsertionSort<Elem, Comp>()(first, end, *itBegin);
					++itBegin;
				}
			}

		private:
			void initializeSequence(int size)
			{
				//defult sequence: 1, 4, 13, 40, 121, 364, 1093, ...
				int temp = 1;
				h.reserve(size);
				h.push_back(temp);
				while (temp < (size / m_increasement))
				{
					temp = m_increasement * temp + 1;
					h.push_back(temp);
				}
				std::vector<int>(h).swap(h);
			}
		
		private:
			std::vector<int> h;
			int m_increasement;
		};

		//////////////////////////////////////////////////////////////////////////
		// Algorithm Name: Quick Sort
		// Quicksort is a divide-and-conquer method for sorting. It works by partitioning an array into two parts, then sorting the parts independently.
		// Quicksort uses ~2 N ln N compares(and one - sixth that many exchanges) on the average to sort an array of length N with distinct keys.
		// Quicksort uses ~N2 / 2 compares in the worst case, but random shuffling protects against this case.
		// Bibliography:
		// http://algs4.cs.princeton.edu/23quicksort/
		//////////////////////////////////////////////////////////////////////////
		template<typename Elem, typename Comp = AlgTools::less_equal<Elem> >
		class QuickSort
		{
		public:
			void operator()(Elem A[], int length, bool switch_shuffle = true)
			{
				if (switch_shuffle)
				{
					std::random_shuffle(A, A + length); // eliminate dependency of input
				}
				
				sort(A, 0, length - 1);
			}

		private:
			int partition(Elem A[], int left, int right)
			{
				int i, j;
				Elem pivotIndex = A[left];
				i = left;
				j = right;

				while (i != j)
				{
					// find item on right to swap
					while (Comp()(pivotIndex, A[j]) && i<j)
					{
						--j;
					}
					// find item on left to swap
					while (Comp()(A[i], pivotIndex) && i<j)
					{
						i++;
					}

					if (i<j)
					{
						AlgTools::swap(A, i, j);
					}
				}
				// put partitioning item piovtIndex at a[j]
				AlgTools::swap(A, left, j);

				// now, a[left .. j-1] <= a[j] <= a[j+1 .. right]
				return j;
			}

			void sort(Elem A[], int left, int right)
			{
				 if (left>right) return; // Don't sort 0 or 1 Elem
				// deal with small number of length of array
				//if (right < left + scaleM) {Ryim::Sort::InsertionSort<Elem>()(A, )};

				int j = partition(A, left, right);

				sort(A, left, j - 1);
				sort(A, j + 1, right);
			}

		//private:
		//	const int scaleM = 10;
		};

		//////////////////////////////////////////////////////////////////////////
		// Algorithm Name: Merge Sort
		// use divide-conquer
		// Pseudo-code:
		//       List mergesort(List inlist){
		//              if (length(inlist) <= 1) return inlist;
		//              List1 l1 = half of the items from inlist;
		//              List2 l2 = other half of the items from inlist;
		//              return merge(mergesort(l1), mergesort(l2));
		//            }
		//
		// Abstract in - place merge.The method merge(a, lo, mid, hi) puts the results of merging the subarrays a[lo..mid] with a[mid + 1..hi] into a single ordered array, 
		// leaving the result in a[lo..hi].While it would be desirable to implement this method without using a significant amount of extra space, 
		//such solutions are remarkably complicated.Instead, merge() copies everything to an auxiliary array and then merges back to the original.
		//
		// Top - down mergesort.Merge.java is a recursive mergesort implementation based on this abstract in - place merge.
		//	It is one of the best - known examples of the utility of the divide - and-conquer paradigm for efficient algorithm design.
		// Top - down mergesort uses between 1 / 2 N lg N and N lg N compares and at most 6 N lg N array accesses to sort any array of length N.
		//
		// Bottom-up mergesort. Even though we are thinking in terms of merging together two large subarrays, the fact is that most merges are merging together tiny subarrays.
		// Another way to implement mergesort is to organize the merges so that we do all the merges of tiny arrays on one pass, 
		// then do a second pass to merge those arrays in pairs, and so forth, continuing until we do a merge that encompasses the whole array.
		//	This method requires even less code than the standard recursive implementation. 
		//	We start by doing a pass of 1-by-1 merges (considering individual items as subarrays of size 1), 
		//	then a pass of 2-by-2 merges (merge subarrays of size 2 to make subarrays of size 4), then 4-by-4 merges, and so forth. 
		//	
		// Bibliography:
		// http://algs4.cs.princeton.edu/22mergesort/
		//////////////////////////////////////////////////////////////////////////
 		template<typename Elem, typename Comp = AlgTools::less_equal<Elem> >
 		class MergeSort
 		{
 		public:
 			void operator()(Elem a[], int length, int selected = 0)
 			{
				switch (selected)
				{
				case 0:
					sort_top_down(a, 0, length - 1);
					break;
				case 1:
					sort_bottom_up(a, length);
					break;
				default:
					sort_top_down(a, 0, length - 1);
					break;
				}
 			}

		private:
			void merge(Elem a[], int lo, int mid, int hi)
			{
				int length = hi + 1;
				Ryim::arraylist<Elem>  aux(length, 0);
				// copy to aux[]
				for (int k = lo; k <= hi; k++) {
					aux[k] = a[k];
				}

				// merge back to a[]
				int i = lo, j = mid + 1;
				for (int k = lo; k <= hi; k++) {
					if      (i > mid)                a[k] = aux[j++];
					else if (j > hi)                 a[k] = aux[i++];
					else if (Comp()(aux[j], aux[i])) a[k] = aux[j++];
					else                             a[k] = aux[i++];
				}
			}

			void sort_top_down(Elem a[], int lo, int hi) 
			{
				if (hi <= lo) return;
				int mid = lo + (hi - lo) / 2;
				sort_top_down(a, lo, mid);
				sort_top_down(a, mid + 1, hi);
				merge(a, lo, mid, hi);
			}

			void sort_bottom_up(Elem a[], int n)
			{
				for (int len = 1; len < n; len *= 2)
				{
					for (int lo = 0; lo < n - len; lo += len + len)
					{
						int mid = lo + len - 1;
						int hi = Ryim::AlgTools::minimum(lo + len + len - 1, n - 1);
						merge(a, lo, mid, hi);
					}
				}
			}
 		};

		//////////////////////////////////////////////////////////////////////////
		// Algorithm Name: Heap Sort
		//  We can use any priority queue to develop a sorting method.We insert all the keys to be sorted into a minimum - oriented priority queue,
		//  then repeatedly use remove the minimum to remove them all in order.When using a heap for the priority queue, we obtain heapsort.
		//	Focusing on the task of sorting, we abandon the notion of hiding the heap representation of the priority queue and use swim() and sink() directly.
		//  Doing so allows us to sort an array without needing any extra space, by maintaining the heap within the array to be sorted.
		//  Heapsort breaks into two phases : heap construction, where we reorganize the original array into a heap, and the sortdown, 
		//  where we pull the items out of the heap in decreasing order to build the sorted result.
		//	Heap construction.We can accomplish this task in time proportional to n lg n, by proceeding from left to right through the array, 
		//  using swim() to ensure that the entries to the left of the scanning pointer make up a heap - ordered complete tree, 
		//  like successive priority queue insertions.A clever method that is much more efficient is to proceed from right to left, 
		//  using sink() to make subheaps as we go.Every position in the array is the root of a small subheap; sink() works or such subheaps, as well.
		//  If the two children of a node are heaps, then calling sink() on that node makes the subtree rooted there a heap.
		//	Sortdown.Most of the work during heapsort is done during the second phase, where we remove the largest remaining items from the heap and 
		//  put it into the array position vacated as the heap shrinks.
		// Bibliography:
		// https://algs4.cs.princeton.edu/24pq/
		//////////////////////////////////////////////////////////////////////////
 		template<typename RandomIter, typename Comp = AlgTools::less<typename RandomIter::value_type> >
 		class HeapSort
 		{
 		public:
 			void operator()(RandomIter _first, RandomIter _last)
 			{
				Ryim::heap::buildHeap<RandomIter, Comp>()(_first, _last);

				RandomIter endian = _first + 1;
				for (RandomIter it = _last; it > endian;)
				{
					it = Ryim::heap::popHeap<RandomIter, Comp>()(_first, it);
				}
 			}
 		};
	}// END Namespace Sort

}// END Namespace Ryim
#endif