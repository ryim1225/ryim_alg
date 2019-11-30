#ifndef _R_S_LINK_LIST_H_
#define _R_S_LINK_LIST_H_
#include "rException.h"
#include "rIterator.h"

namespace Ryim
{
	// Singly-link list node
	template<typename Elem>
	class Link
	{
	public:
		Elem   element;
		Link * next;
		Link(const Elem &elemva, Link * nextval = NULL){element = elemva; next = nextval;}
		Link(Link * nextval = NULL){next = nextval;}
		Elem& operator*() const
		{
			return element;
		}
	//	void * operator new(size_t);
	//	void   operator delete(void* ptr);
	//private:
	//	static Link<Elem> * freelist; //Useable free space list
	};

	//template<typename Elem>
	//Link<Elem> * Link<Elem>::freelist = NULL;

	//template<typename Elem>
	//void* Link<Elem>::operator new(size_t)
	//{
	//	if(NULL == freelist)
	//	{
	//		return ::new Link; 
	//	}
	//	Link<Elem>* temp = freelist;
	//	freelist          = freelist->next;
	//	return temp;
	//}

	//template<typename Elem>
	//void Link<Elem>::operator delete(void* ptr)
	//{
	//	((Link<Elem>* ) ptr)->next = freelist;
	//	freelist = (Link<Elem> *) ptr;
	//}

	//////////////////////////////////////////////////////////////////////////
	// The Single-linked list.
	//////////////////////////////////////////////////////////////////////////
	template<typename Elem, typename Alloc = std::allocator<Link<Elem> > >
	class SLinkList
	{
	public:
		typedef SLinkList<Elem> _Myt;
		typedef typename Link<Elem>* nodeptr;
		typedef typename const Link<Elem>* const_nodeptr;

		typedef typename Elem value_type;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename Elem* pointer;
		typedef typename const Elem* const_pointer;
		typedef typename Elem& reference;
		typedef typename const Elem& const_reference;

		typedef typename singlelinkedlist_const_iterator<_Myt> const_iterator;
		typedef typename singlelinkedlist_iterator<_Myt> iterator;

		SLinkList():m_size(0){init();}
		~SLinkList(){removeall();}
		void init()
		{
			m_head = m_alloc.allocate(1);
			m_head->next = m_head;
		}

		void removeall()
		{
			if (empty())
			{
				this->freeNode(m_head);
				return;
			}

			while (m_head != m_head->next)
			{
				Link<Elem> *ptemp = m_head->next;
				m_head->next  = ptemp->next;
				this->freeNode(ptemp);
			}

			this->freeNode(m_head);
			return;
		}

		void clear(){removeall(); init();}

		bool empty()
		{
			return (0 == m_size);
		}

		iterator begin()
		{
			return iterator(m_head->next, this);
		}

		iterator end()
		{
			return iterator(m_head, this);
		}


		const_iterator begin() const
		{
			return const_iterator(m_head->next, this);
		}

		const_iterator end() const
		{
			return const_iterator(m_head, this);
		}

		reference front() const
		{
			return (*begin());
		}

		reference back() const
		{
			return (*prevnodeptr(m_head));
		}

		nodeptr prevnodeptr(nodeptr _currPos)
		{
			nodeptr prevtemp = m_head;
			
			while (prevtemp->next != _currPos)
			{
				prevtemp = prevtemp->next;
			}
			return prevtemp;
		}

		nodeptr nextnodeptr(nodeptr _currPos)
		{
			nodeptr prevtemp;
			prevtemp = _currPos->next;
			return prevtemp;
		}

		size_type size() const
		{
			return m_size;
		}

		bool insert(iterator _where, const Elem &item)
		{
			if (_where.getCont() != this)
			{
				throw illegalIterator("list insert iterator outside range ");
			}

			nodeptr temp;
			nodeptr pwhere;
			pwhere = const_cast<nodeptr>(_where.base());
			temp = m_alloc.allocate(1);
			temp->element = item;
			temp->next = pwhere->next;
			pwhere->next = temp;
			++m_size;
			return true;
		}

		void push_front(const Elem& item)
		{
			nodeptr temp;
			temp = m_alloc.allocate(1);
			temp->element = item;
			temp->next = m_head->next;
			m_head->next = temp;
			++m_size;
			return;
		}

		void push_back(const Elem &item)
		{
			nodeptr frontOfHead = prevnodeptr(m_head);
			nodeptr temp;
			temp = m_alloc.allocate(1);
			temp->element = item;
			temp->next = m_head;
			frontOfHead->next = temp;
			++m_size;
		}

		void remove(const Elem &value)
		{
			// erase each element matching _Val
			const Elem _Val = value;	// in case it's removed along the way
			if (empty()) return;

			nodeptr _Pnode = m_head;
			while (_Pnode->next != m_head)
				if (_Val == _Pnode->next->element)
				{	// match, remove it
					const nodeptr _Perase = _Pnode->next;
					_Pnode->next = _Perase->next;
					this->freeNode(_Perase);

					--m_size;
				}
				else
					_Pnode = _Pnode->next;
		}

		iterator erase(iterator Itrase)
		{
			if (Itrase.getCont() != this)
			{
				throw illegalIterator("ryim list erase iterator outside range ");
			}

			nodeptr nodeperv = this->prevnodeptr(Itrase.base());
			nodeperv->next = (Itrase.base())->next;
			this->freeNode(Itrase.base());
			--m_size;
			return ++iterator(nodeperv, this);
		}

	private:
		void freeNode(nodeptr node)
		{
			m_alloc.destroy(node);
			m_alloc.deallocate(node, 1);
		}
		nodeptr   m_head;
		size_type m_size;
		Alloc	  m_alloc;
	};
}
#endif