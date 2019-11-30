#ifndef _R_STACK_H_
#define _R_STACK_H_
#include "rSingleLinkedList.h"

namespace Ryim
{
	// link stack
	template<typename Elem, class Container = Ryim::SLinkList<Elem> >
	class Stack
	{
	public:
		typedef typename Elem value_type;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename Elem* pointer;
		typedef typename const Elem* const_pointer;
		typedef typename Elem& reference;
		typedef typename const Elem& const_reference;

		Stack(){}
		~Stack() {}
	
		void clear()
		{
			m_allowContainer.clear();
		}
		void push(const Elem &item)
		{
			m_allowContainer.push_front(item);
		}
		void pop()
		{
			m_allowContainer.erase(m_allowContainer.begin());
		}

		Elem& top()
		{
			return m_allowContainer.front();
		}
		
		size_type size() const
		{
			m_allowContainer.size();
		}

		bool empty()
		{
			return m_allowContainer.empty();
		}
	private:
		Container m_allowContainer;
	};
}
#endif