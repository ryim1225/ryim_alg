#ifndef _R_ARRAY_LIST_H_
#define _R_ARRAY_LIST_H_

#include "rIterator.h"
#include "rUtility.h"
#include "rMemory.h"

namespace Ryim
{
	template <typename Elem, typename Alloc = std::allocator<Elem> > 
	class arraylist
	{
	public:
		typedef arraylist<Elem, Alloc> _Myt;

		typedef typename Elem value_type;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename Elem* pointer;
		typedef typename const Elem* const_pointer;
		typedef typename Elem& reference;
		typedef typename const Elem& const_reference;
						 
		typedef typename arraylist_iterator<_Myt>		iterator;
		typedef typename arraylist_const_iterator<_Myt> const_iterator;

		arraylist()
		{
			m_listFirst = pointer();
			m_listLast  = pointer();
			m_listEnd   = pointer();
		}

		explicit arraylist(size_type initialCapacitySize)
		{
			_construct(initialCapacitySize);
		}

#if _MSC_VER  < 1800
#else
		arraylist(std::initializer_list<value_type> initList)
		{
			if (_Buy(initList.size()))
				this->m_listLast = Ryim::AlgTools::copy(initList.begin(), initList.end(), this->m_listFirst);
		}

		_Myt& operator=(std::initializer_list<value_type> initList)
		{
			if (_Buy(initList.size()))
				this->m_listLast = Ryim::AlgTools::copy(initList.begin(), initList.end(), this->m_listFirst);
			return (*this);
		}
#endif

		arraylist(size_type initialCapacitySize, const Elem& element)
		{
			_construct(initialCapacitySize);
			std::uninitialized_fill_n(begin(), initialCapacitySize, element);
			m_listLast = m_listEnd;
		}

		arraylist(const _Myt& right)
		{   // construct by copying _Right
			if (_Buy(right.size()))
				this->m_listLast = Ryim::AlgTools::copy(right.m_listFirst, right.m_listLast, this->m_listFirst);
		}

		const arraylist& operator=(const _Myt& right)
		{   // construct by copying _Right
			if (this == &right)
			{
				return *this;
			}
			if (_Buy(right.size()))
				this->m_listLast = Ryim::AlgTools::copy(right.m_listFirst, right.m_listLast, this->m_listFirst);

			return *this;
		}

		~arraylist(void)
		{
			_releaseAll();
		}

		void clear()
		{
			_releaseAll();
			_construct(m_listEnd - m_listFirst);
		}


		iterator begin()
		{
			return iterator(this->m_listFirst, this);
		}

		iterator end()
		{
			return iterator(this->m_listLast, this);
		}

		const_iterator begin() const
		{
			return const_iterator(this->m_listFirst, this);
		}

		const_iterator end() const
		{
			return const_iterator(this->m_listLast, this);
		}

		//
		// return first element of mutable sequence
		//
		reference front()
		{	
			return (*begin());
		}

		//
		// return first element of nonmutable sequence
		//
		const_reference front() const
		{	
			return (*begin());
		}

		//
		// return last element of mutable sequence
		//
		reference back()
		{	
			return (*(end() - 1));
		}

		//
		// return last element of nonmutable sequence
		//
		const_reference back() const
		{	
			return (*(end() - 1));
		}

		//
		// erase element at end
		//
		void pop_back()
		{
			if (empty())
			{
				return;
			}
			m_alloc.destroy(--m_listLast);
		}

		//
		// determine new length, padding as needed
		//
		void resize(size_type Newsize)
		{
			if (Newsize < size())
				erase(begin() + Newsize, end());
			else if (size() < Newsize)
			{	// pad as needed
				_Count = Newsize - size();
				if (_Unused_capacity() < _Count)
				{	// need more room, try to get it
					if (max_size() - size() < _Count)
						std::_Xlength_error("arraylist<T> too long");
					_reallocate(_Grow_to(size() + _Count));
				}

				std::_Uninitialized_default_fill_n(this->m_listLast, Newsize - size(), m_alloc);

				this->m_listLast += Newsize - size();
			}
		}

		void resize(size_type Newsize, const value_type& val)
		{
			if (Newsize < size())
				erase(begin() + Newsize, end());
			else if (size() < Newsize)
				push_back(end(), Newsize - size(), _Val);
		}


		//
		// determine new minimum length of allocated storage
		//
		void reserve(size_type Count)
		{	// determine new minimum length of allocated storage
			if (capacity() < Count)
			{	// something to do, check and reallocate
				if (max_size() < Count)
					std::_Xlength_error("arraylist<T> too long");
				_reallocate(Count);
			}
		}

		//
		// Get the allocator of this container object
		//
		Alloc get_allocator() const
		{	// return allocator object for values
			return (this->m_alloc);
		}

		//
		// at method --- Get the element accroding to the index given
		//
		reference at(size_type theIndex)
		{	
			_checkIndex(theIndex);
			return (*(this->_Myfirst + theIndex));
		}

		const_reference at(size_type theIndex) const
		{	
			_checkIndex(theIndex);
			return (*(this->_Myfirst + theIndex));
		}

		//
		// size method --- Get the size of container
		//
		size_type size() const
		{
			return (m_listLast - m_listFirst);
		}

		//
		// capacity method --- Get the capacity of container
		//
		size_type capacity() const
		{
			return (m_listEnd - m_listFirst);
		}

		//
		// return maximum possible length of sequence
		//
		size_type max_size() const
		{	
			return (m_alloc.max_size());
		}

		//
		// empty method --- Judge whether the container is empty
		//
		bool empty() const
		{
			return (m_listFirst == m_listLast);
		}

		//
		// [] method --- get value by container[index]
		//
		reference operator[](size_type theIndex) 
		{	// subscript
			_checkIndex(theIndex);
			return (*(this->m_listFirst + theIndex));
		}
		const_reference operator[](size_type theIndex) const
		{	// subscript nonmutable sequence
			_checkIndex(theIndex);
			return (*(this->m_listFirst + theIndex));
		}

		//
		// insert method --- insert the element into the container
		//
		iterator insert(const_iterator where_it, const Elem& item)
		{
			// check iterator
			_checkArrayIter(where_it, "vector insert iterator outside range");

			difference_type distnceWhere = where_it - this->begin();
			// insert the element
			if (m_listLast == m_listEnd)
			{
				this->_reallocate(2 * capacity());
				where_it = begin() + distnceWhere;
			}

			Ryim::AlgTools::copy_backward<const_iterator, iterator>(where_it, end(), end()+1); //unsafe

			*(m_listFirst + distnceWhere) = item;
			++m_listLast;
			return begin() + distnceWhere;
		}

		iterator insert(const_iterator where_it, size_type _Count,
			const value_type& _Val)
		{	// insert _Count * _Val at _Where
			// check iterator
			_checkArrayIter(where_it, "vector insert iterator outside range");
			difference_type distnceWhere = where_it - this->begin();
			if(0 == _Count);
			else if (_Count > _Unused_capacity())
			{
				this->reserve(size() + _Count);
				where_it = begin() + distnceWhere;
			}

			Ryim::AlgTools::copy_backward<const_iterator, iterator>(where_it, end(), end()+_Count); //unsafe
			std::uninitialized_fill_n(begin() + distnceWhere, _Count, _Val);
			this->m_listLast += _Count;
			return (begin() + distnceWhere);
		}

		template<class _Iter>
		typename std::enable_if<std::_Is_iterator<_Iter>::value,
			iterator>::type
			insert(const_iterator where_it, _Iter _First, _Iter _Last)
		{	// insert [_First, _Last) at _Where
			_checkArrayIter(where_it, "vector insert iterator outside range");
			size_type distnceWhere = where_it - begin();
			difference_type _Count = _Last - _First;

			if ((size_type)_Count>_Unused_capacity())
			{
				this->reserve(size() + _Count);
				where_it = begin() + distnceWhere;
			}

			size_type aaa = capacity();
			Ryim::AlgTools::copy_backward<const_iterator, iterator>(where_it, end(), end()+_Count); //unsafe
			iterator assignIt = begin() + distnceWhere;
			for (_Iter it = _First; it !=_Last; ++it, ++assignIt)
			{
				*assignIt = *it;
			}
			this->m_listLast += _Count;

			return (begin() + distnceWhere);
		}

		//
		// assign [_First, _Last), input iterators Or assign _Count * _Val
		//
		template<class _Iter>
		typename std::enable_if<std::_Is_iterator<_Iter>::value,
			iterator>::type
			assign(_Iter _First, _Iter _Last)
		{	// assign [_First, _Last), input iterators
			erase(begin(), end());
 			return insert(begin(), _First, _Last);
		}

		void assign(size_type _Count, const value_type& _Val)
		{	// assign _Count * _Val
			value_type _Tmp = _Val;	// in case _Val is in sequence
			erase(begin(), end());
			insert(begin(), _Count, _Tmp);
		}

		//
		// push_back method --- Push the element into the back of the container
		//
		void push_back(const Elem& item)
		{
			if (m_listLast == m_listEnd)
			{
				this->_reallocate(2 * capacity());
			}

			*m_listLast = item;
			++m_listLast;
		}

		//
		// erase method --- Erase the specific element
		//
		iterator erase(iterator where_it)
		{
			// check iterator
			_checkArrayIter(where_it, "vector erase iterator outside range");

			// erase the element
			difference_type _off = where_it - begin();
			Ryim::AlgTools::copy(begin()+_off + 1, end(), begin() + _off); // unsafe
			--m_listLast;
			m_alloc.destroy(m_listLast);
			return (begin() + _off);
		}

		iterator erase(iterator first_it, iterator last_it)
		{
			// check iterator
			_checkArrayIter(first_it, "vector erase iterator outside range");
			_checkArrayIter(last_it,   "vector erase iterator outside range");

			difference_type _off = last_it - first_it;
			// erase the element
			Ryim::AlgTools::copy(last_it, end(), first_it); // unsafe
			m_listLast -= _off;
			for (difference_type it = 1; it <= _off; ++it)
			{
				m_alloc.destroy(--m_listLast);
			}
			return first_it;
		}

		void swap(_Myt& _Right)
		{	// exchange contents with _Right
			if (this == &_Right)
				;	// same object, do nothing
			else if (this->get_allocator() == _Right.get_allocator())
			{	// same allocator, swap control information
				pointer temp = this->m_listFirst;
				this->m_listFirst = _Right.m_listFirst;
				_Right.m_listFirst = temp;

				temp = this->m_listLast;
				this->m_listLast = _Right.m_listLast;
				_Right.m_listLast = temp;

				temp = this->m_listEnd;
				this->m_listEnd = _Right.m_listEnd;
				_Right.m_listEnd = temp;

				Alloc tempAlloc = this->m_alloc;
				this->m_alloc = _Right.m_alloc;
				_Right.m_alloc = tempAlloc;
			}
			else
			{	// different allocator, do multiple moves
				throw illegalParameterValue("different allocator.");
			}
		}

	protected:
		void _construct(size_type listCapacity)
		{
			if (listCapacity < 1)
			{
				throw illegalParameterValue("Initial capacity must be > 0!");
			}

			m_listLast = m_listFirst = m_alloc.allocate(listCapacity + 1, m_listFirst);
			m_listEnd = m_listFirst + listCapacity;
		}

		bool _Buy(size_type _Capacity)
		{	// allocate array with _Capacity elements
			this->m_listFirst = pointer();
			this->m_listLast = pointer();
			this->m_listEnd = pointer();

			if (_Capacity == 0)
				return (false);
			else if (max_size() < _Capacity)
				std::_Xlength_error("arraylist<T> too long");	// result too long
			else
			{	// nonempty array, allocate storage
				this->m_listFirst = this->m_alloc.allocate(_Capacity);
				this->m_listLast = this->m_listFirst;
				this->m_listEnd = this->m_listFirst + _Capacity;
			}
			return (true);
		}


		size_type _Unused_capacity() const _NOEXCEPT
		{	// micro-optimization for capacity() - size()
			return (this->m_listEnd - this->m_listLast);
		}

		size_type _Grow_to(size_type _Count) const
		{	// grow by 50% or at least to _Count
			size_type _Capacity = capacity();

			_Capacity = max_size() - _Capacity / 2 < _Capacity
				? 0 : _Capacity + _Capacity / 2;	// try to grow by 50%
			if (_Capacity < _Count)
				_Capacity = _Count;
			return (_Capacity);
		}

		void _releaseAll()
		{
			for (pointer p = m_listFirst; p != m_listLast; ++p)
				m_alloc.destroy(p);

			 if(m_listFirst)
				m_alloc.deallocate(m_listFirst, m_listEnd - m_listFirst + 1);
		}

		void _reallocate(size_type _Count)
		{
			size_type oldCapacity = capacity();
			size_type distnceLast = size();
		
			if (0 == oldCapacity)
			{
				oldCapacity = 1;
			}
			std::ptrdiff_t newCapacity = Ryim::AlgTools::maximum<size_type>(oldCapacity, _Count);
			
			pointer newelements = m_alloc.allocate(newCapacity);
			Ryim::AlgTools::copy(begin(), end(), iterator(newelements, this)); // unsafe
			this->_releaseAll();

			m_listFirst = newelements;
			m_listLast = m_listFirst + distnceLast;
			m_listEnd = m_listFirst + newCapacity;
		}

		void _checkIndex(size_type theIndex) const
		{
			if (theIndex < 0 || theIndex >= size())
			{
				throw illegalIndex("index must be < array's size!");
			}
		}

		void _checkArrayIter(const_iterator it, char* errorMessage)
		{
			if (it.getCont() != this
				|| it < this->begin()
				|| this->end() < it)
				throw illegalIterator(errorMessage);
		}

	private:
		pointer    m_listFirst;  	// pointer to beginning of array
		pointer    m_listLast;	 	// pointer to current end of sequence
		pointer    m_listEnd;	    // pointer to end of array
		Alloc      m_alloc;
	};
}
#endif
