#ifndef _R_DOUBLY_LINKED_LIST_H_
#define _R_DOUBLY_LINKED_LIST_H_
#include "rException.h"
#include "rIterator.h"

namespace Ryim
{
	// Singly-link list node
	template<typename Elem>
	class dLink
	{
	public:
		Elem   element;
		dLink * next;
		dLink * prev;
		dLink(const Elem &elemva, dLink * prevp = NULL, dLink * nextval = NULL){element = elemva; prev = prevp; next = nextval;}
		dLink(dLink * prevp = NULL, dLink * nextval = NULL){prev = prevp; next = nextval;}
		Elem& operator*() const
		{
			return element;
		}
	//	void * operator new(size_t);
	//	void   operator delete(void* ptr);
	//private:
	//	static dLink<Elem> * freelist; //Useable free space list
	};

	//template<typename Elem>
	//dLink<Elem> * dLink<Elem>::freelist = NULL;

	//template<typename Elem>
	//void* dLink<Elem>::operator new(size_t)
	//{
	//	if(NULL == freelist)
	//	{
	//		return ::new dLink; 
	//	}
	//	dLink<Elem>* temp = freelist;
	//	freelist          = freelist->next;
	//	return temp;
	//}

	//template<typename Elem>
	//void dLink<Elem>::operator delete(void* ptr)
	//{
	//	((dLink<Elem>* ) ptr)->next = freelist;
	//	freelist = (dLink<Elem> *) ptr;
	//}


	// The fence point to the last one of the left part.
	template<typename Elem, typename Alloc = std::allocator<dLink<Elem> > >
	class DoublyLinkedList
	{
	public:
		typedef DoublyLinkedList<Elem> _Myt;
		typedef typename dLink<Elem>* nodeptr;
		typedef typename const dLink<Elem>* const_nodeptr;

		typedef typename Elem value_type;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename Elem* pointer;
		typedef typename const Elem* const_pointer;
		typedef typename Elem& reference;
		typedef typename const Elem& const_reference;

		typedef typename doublylinkedlist_const_iterator<_Myt> const_iterator;
		typedef typename doublylinkedlist_iterator<_Myt> iterator;


		DoublyLinkedList(int size = 1){init();}
		~DoublyLinkedList(){removeall();}
		void init()
		{
			m_head = m_alloc.allocate(1);
			m_head->next = m_head->prev = m_head;
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
				nodeptr ptemp = m_head->next;
				m_head->next  = ptemp->next;
				ptemp->prev   = m_head;
				this->freeNode(ptemp);
			}

			this->freeNode(m_head);
			return;
		}

		void clear() { removeall(); init(); }

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
			return (*(m_head->prev));
		}

		nodeptr prevnodeptr(nodeptr _currPos)
		{
			return _currPos->prev;
		}

		nodeptr nextnodeptr(nodeptr _currPos)
		{
			return _currPos->next;
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
			temp->prev = pwhere;
			temp->next->prev = temp;
			++m_size;
			return true;
		}

		void push_front(const Elem& item)
		{
			insert(begin(), item);
			return;
		}

		void push_back(const Elem &item)
		{
			insert(end(), item);
			return;
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
					_Perase->next->prev = _Pnode;
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

			nodeptr nodeperv = (Itrase.base())->prev;
			nodeperv->next = (Itrase.base())->next;
			(Itrase.base())->next->prev = nodeperv;
			this->freeNode(const_cast<nodeptr>(Itrase.base()));
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