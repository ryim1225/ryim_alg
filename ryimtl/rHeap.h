#ifndef _R_HEAP_H_
#define _R_HEAP_H_

#include "rUtility.h"
#include "rArrayList.h"
#include "rException.h"
#include <xutility>

namespace Ryim
{
	namespace heap
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		// Heap definitions:The binary heap is a data structure that can efficiently support the basic priority - queue operations.
		//  In a binary heap, the items are stored in an array such that each key is guaranteed to be larger than(or equal to) 
		//  the keys at two other specific positions.In turn, each of those keys must be larger than two more keys, and so forth.
		//  This ordering is easy to see if we view the keys as being in a binary tree structure 
		//  with edges from each key to the two keys known to be smaller.
		// Definition:A binary tree is heap - ordered if the key in each node is larger than(or equal to) the keys in that nodes two children(if any).
		// Proposition:The largest key in a heap - ordered binary tree is found at the root.
		// Bibliography:
		// https://algs4.cs.princeton.edu/24pq/
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		namespace tools_heap
		{
			enum error_code { isOK = 0, empty };

			template<typename RandomIter>
			error_code checkIter(RandomIter _first, RandomIter _last, RandomIter _pos)
			{
				error_code code = checkIter(_first, _last);
				if (isOK != code)
					return code;

				if (_first == _last && _pos != _last)
				{
					throw illegalIterator("the position has not belonged to the container!");
				}

				if (_first != _last && (_pos >= _last || _pos < _first))
					throw illegalIterator("the position has not belonged to the container!");

				return isOK;
			}

			template<typename RandomIter>
			error_code checkIter(RandomIter _first, RandomIter _last)
			{
				if (_first > _last)
					throw illegalIterator("this container is invalid!");
				else if (_last == _first)
					return empty;
				return isOK;
			}

			template<typename RandomIter>
			bool isLeaf(RandomIter _first, RandomIter _last, RandomIter _pos)
			{
				checkIter(_first, _last, _pos);

				typedef typename RandomIter::difference_type difference_type;
				difference_type count = _last - _first;
				difference_type npos = _pos - _first;
				return (npos >= count / 2) && (npos < count);
			}

			template<typename RandomIter>
			RandomIter leftchild(RandomIter _first, RandomIter _last, RandomIter _pos)
			{
				checkIter(_first, _last, _pos);

				typedef typename RandomIter::difference_type difference_type;
				difference_type npos = _pos - _first;
				return ((_first + (2 * npos + 1)) < _last) ? (_first + (2 * npos + 1)) : _last;
			}

			template<typename RandomIter>
			RandomIter rightchild(RandomIter _first, RandomIter _last, RandomIter _pos)
			{
				return ((leftchild(_first, _last, _pos) + 1) < _last) ? (leftchild(_first, _last, _pos) + 1) : _last;
			}

			template<typename RandomIter>
			RandomIter parent(RandomIter _first, RandomIter _last, RandomIter _pos)
			{
				checkIter(_first, _last, _pos);

				typedef typename RandomIter::difference_type difference_type;
				difference_type npos = _pos - _first;
				return _first + ((npos - 1) / 2);
			}

			// Put element into its correct place from bottom to top.
			template<typename RandomIter, typename Comp>
			class swim
			{
			public:
				void operator()(RandomIter _first, RandomIter _last, RandomIter _pos, std::random_access_iterator_tag)
				{
					while (Comp()(*_pos, *parent(_first, _last, _pos)))
					{
						RandomIter its_parent = parent(_first, _last, _pos);
						std::iter_swap(_pos, its_parent);
						_pos -= (_pos - its_parent);

					}
				}

				void operator()(RandomIter _first, RandomIter _last, RandomIter _pos)
				{
					if (isOK != tools_heap::checkIter(_first, _last, _pos))
						return;
					this->operator()(_first, _last, _pos, 
						typename std::iterator_traits<RandomIter>::iterator_category());
				}
			};

			// Put element into its correct place from top to bottom.
			template<typename RandomIter, typename Comp>
			class sink
			{
			public:
				void operator()(RandomIter _first, RandomIter _last, RandomIter _pos, std::random_access_iterator_tag)
				{
					while (!isLeaf(_first, _last, _pos))
					{
						RandomIter lc = leftchild(_first, _last, _pos);
						RandomIter rc = rightchild(_first, _last, _pos);
						//判断左右子节点符合要求， 将符合要求的与父节点比较
						if ((rc < _last) && Comp()(*rc, *lc))
						{
							lc = rc;
						}

						if (Comp()(*_pos, *lc))
						{
							return;
						}

						std::iter_swap(_pos, lc);
						_pos = lc;
					}
				}

				void operator()(RandomIter _first, RandomIter _last, RandomIter _pos)
				{
					if (isOK != tools_heap::checkIter(_first, _last, _pos))
						return;
					this->operator()(_first, _last, _pos, 
						typename std::iterator_traits<RandomIter>::iterator_category());
				}
			};

		}// end tools_heap


		// Make heap 
		template<typename RandomIter, typename Comp = AlgTools::less<RandomIter::value_type> >
		class buildHeap
		{
			typedef typename std::iterator_traits<RandomIter>::difference_type difference_type;
			
		public:
			void operator()(RandomIter _first, RandomIter _last)
			{
				if (tools_heap::isOK != tools_heap::checkIter(_first, _last))
					return;

				difference_type count = _last - _first;
				RandomIter pos = _first + (count - 1) / 2;
				for (; pos >= _first; --pos)
				{
					tools_heap::sink<RandomIter, Comp>()(_first, _last, pos);
				}
			}
		};

		// Is this heap?
		template<typename RandomIter, typename Comp = AlgTools::less<typename RandomIter::value_type> >
		class isHeap
		{
			typename std::iterator_traits<RandomIter>::value_type value_type;
		public:
			bool operator()(RandomIter _first, RandomIter _last)
			{
				if (tools_heap::isOK != tools_heap::checkIter(_first, _last))
					return false;
				
				for (RandomIter it = _last-1; it > _first; --it)
				{
					if (Comp()(*it, *tools_heap::parent(_first, _last, it)))
					{
						return false;
					}
				}
				return true;
			}
		};


		template<typename RandomIter, typename Comp = AlgTools::less<RandomIter::value_type> >
		class pushHeap 
		{
			//typename std::iterator_traits<RandomIter>::value_type value_type;
		public:
			void operator()(RandomIter _first, RandomIter _last)
			{
				isHeap<RandomIter, Comp>()(_first, _last - 1);
				tools_heap::swim<RandomIter, Comp>()(_first, _last, _last-1);
			}
		};

		template<typename RandomIter, typename Comp = AlgTools::less<RandomIter::value_type> >
		class popHeap
		{
		public:
			RandomIter operator()(RandomIter _first, RandomIter _last)
			{
				if (tools_heap::isOK != tools_heap::checkIter(_first, _last))
					return _last;

				std::iter_swap(_first, _last - 1);
				tools_heap::sink<RandomIter, Comp>()(_first, _last-1, _first);
				return _last - 1;
			}
		};
	}
}
#endif