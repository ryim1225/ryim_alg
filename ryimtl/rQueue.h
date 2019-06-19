#ifndef _R_QUEUE_H_
#define _R_QUEUE_H_

#include "rDoublyLinkedList.h"
#include "rArrayList.h"
#include "rHeap.h"

namespace Ryim
{
	template<typename Elem, class Container = Ryim::arraylist<Elem> >
	class Queue
	{
	public:
		Queue(){}
		~Queue(){}

		void clear()
		{
			m_allowContainer.clear();
		}

		void push_back(const Elem &item)
		{
			m_allowContainer.push_back(item);
		}

		void pop_front()
		{
			m_allowContainer.erase(m_allowContainer.begin());
		}

		Elem& front()
		{
			return m_allowContainer.front();
		}

		Elem& back()
		{
			return m_allowContainer.back();
		}

		std::size_t size() const
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

	template <typename Elem, typename Container = rArrayList<Elem>,
		typename Compare = AlgTools::less<typename Container::value_type> > 
	class rPriorityQueue 
	{
	public:
		rPriorityQueue()
		{
		}

		~rPriorityQueue()
		{
		}

		std::size_t size() const
		{
			m_allowContainer.size();
		}

		bool empty()
		{
			return m_allowContainer.empty();
		}

		void push(const Elem &item)
		{
			m_allowContainer.push_back(item);
			Ryim::heap::pushHeap<Container::iterator, Compare>()(m_allowContainer.begin(), m_allowContainer.end());
		}

		void pop()
		{
			Container::iterator it = Ryim::heap::popHeap<Container::iterator, Compare>()(m_allowContainer.begin(), m_allowContainer.end());
			m_allowContainer.erase(it);
		}

		const Elem& top()
		{
			return *(m_allowContainer.begin());
		}

	private:
		Container m_allowContainer;
	};
}
#endif