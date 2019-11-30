#ifndef _R_ITERATOR_H_
#define _R_ITERATOR_H_
#include <iterator>
#include "rException.h"

namespace Ryim
{
    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS arraylist_const_iterator
    template<class _Myvec>
    class arraylist_const_iterator
        : public std::iterator<std::random_access_iterator_tag,
        typename _Myvec::value_type,
        typename _Myvec::difference_type,
        typename _Myvec::const_pointer,
        typename _Myvec::const_reference>
    {	// const_iterator for arraylist
    public:
        typedef arraylist_const_iterator<_Myvec> _Myiter;

        typedef typename _Myvec::const_pointer   pointer;
        typedef typename _Myvec::const_reference reference;
        typedef typename _Myvec::difference_type difference_type;
        typedef typename _Myvec::value_type value_type;

        arraylist_const_iterator()
        {	// construct with null vector pointer
        }

        arraylist_const_iterator(pointer _Parg, const _Myvec* Myvec): 
            _ptr(_Parg)
            , _pMyvec(Myvec)
        {	// construct with pointer _Parg
        }

        reference operator*() const
        {	// return designated object
            return (*(this->_ptr));
        }

        pointer operator-> () const
        {	// return pointer to class object
            return this->_ptr;
        }

        _Myiter& operator++ ()
        {	// preincrement
            ++(this->_ptr);
            return (*this);
        }

        _Myiter operator++ (int)
        {	// postincrement
            _Myiter _Tmp = *this;
            ++*this;
            return (_Tmp);
        }

        _Myiter& operator--()
        {	// predecrement
            --(this->_ptr);
            return (*this);
        }

        _Myiter operator--(int)
        {	// postdecrement
            _Myiter _Tmp = *this;
            --*this;
            return (_Tmp);
        }

        _Myiter& operator+= (difference_type _Off)
        {	// increment by integer
        	this->_ptr += _Off;
        	return (*this);
        }

        _Myiter operator+(difference_type _Off) const
        {	// return this + integer
            _Myiter _Tmp = *this;
            _Tmp._ptr += _Off;
            return _Tmp;
        }

        _Myiter& operator-=(difference_type _Off)
        {	// decrement by integer
        	this->_ptr += _Off;
        	return (*this);
        }

        _Myiter operator-(difference_type _Off) const
        {	// return this - integer
            _Myiter _Tmp = *this;
            _Tmp._ptr -= _Off;
            return _Tmp;
        }

        difference_type operator-(const _Myiter& _Right) const
        {	// return difference of iterators
            return (this->_ptr - _Right._ptr);
        }

        reference operator[](difference_type _Off) const
        {	// subscript
            return (*(this->_ptr + _Off));
        }

        bool operator==(const _Myiter& _Right) const
        {	// subscript
            return (this->_ptr == _Right._ptr);
        }

        bool operator!=(const _Myiter& _Right) const
        {	// subscript
            return (!(*this == _Right));
        }
        const _Myvec* const getCont() const
        {
            return _pMyvec;
        }


        bool operator<(const _Myiter& _Right) const
        {	// test if this < _Right
            if (this->getCont() == 0
                || this->getCont() != _Right.getCont())
                throw("iterators incompatible");

            return (this->_ptr < _Right._ptr);
        }

        bool operator>(const _Myiter& _Right) const
        {	// test if this > _Right
            if (this->getCont() == 0
                || this->getCont() != _Right.getCont())
                throw("iterators incompatible");

            return (_Right < *this);
        }

        bool operator<=(const _Myiter& _Right) const
        {	// test if this <= _Right
            return (!(_Right < *this));
        }

        bool operator>=(const _Myiter& _Right) const
        {	// test if this >= _Right
            return (!(*this < _Right));
        }
    private:
        pointer _ptr;
        const _Myvec* _pMyvec;
    };

    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS arraylist_iterator
    template<class _Myvec>
    class arraylist_iterator
        : public arraylist_const_iterator<_Myvec>
    {	// iterator for arraylist
    public:
        typedef arraylist_iterator<_Myvec> _Myiter;
        typedef arraylist_const_iterator<_Myvec> _Mybase;
        typedef std::random_access_iterator_tag iterator_category;

        typedef typename _Myvec::value_type value_type;
        typedef typename _Myvec::difference_type difference_type;
        typedef typename _Myvec::pointer pointer;
        typedef typename _Myvec::reference reference;

        arraylist_iterator()
        {	// construct with null vector pointer
        }

        arraylist_iterator(pointer _Parg, const _Myvec* Myvec): _Mybase(_Parg, Myvec)
        {	// construct with pointer _Parg
        }

        reference operator*() const
        {	// return designated object
            return ((reference)**(_Mybase *)this);
        }

        pointer operator->() const
        {	// return pointer to class object
            return (std::pointer_traits<pointer>::pointer_to(**this));
        }

        _Myiter& operator++()
        {	// preincrement
            ++*(_Mybase *)this;
            return (*this);
        }

        _Myiter operator++(int)
        {	// postincrement
            _Myiter _Tmp = *this;
            ++*this;
            return (_Tmp);
        }

        _Myiter& operator--()
        {	// predecrement
            --*(_Mybase *)this;
            return (*this);
        }

        _Myiter operator--(int)
        {	// postdecrement
            _Myiter _Tmp = *this;
            --*this;
            return (_Tmp);
        }

        _Myiter& operator+=(difference_type _Off)
        {	// increment by integer
        	*(_Mybase *)this += _Off;
        	return (*this);
        }

        _Myiter operator+(difference_type _Off) const
        {	// return this + integer
            _Myiter _Tmp = *this;
            return (_Tmp += _Off);
        }

        _Myiter& operator-=(difference_type _Off)
        {	// decrement by integer
            return (*this += -_Off);
        }

        _Myiter operator-(difference_type _Off) const
        {	// return this - integer
            _Myiter _Tmp = *this;
            return (_Tmp -= _Off);
        }

        difference_type operator-(const _Mybase& _Right) const
        {	// return difference of iterators
            return (*(_Mybase *)this - _Right);
        }

        reference operator[](difference_type _Off) const
        {	// subscript
            return (*(*this + _Off));
        }
    };

    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS singlelinkedlist_const_iterator
    template<class _Mylist>
    class singlelinkedlist_const_iterator
        : public std::iterator<std::forward_iterator_tag,
        typename _Mylist::value_type,
        typename _Mylist::difference_type,
        typename _Mylist::pointer,
        typename _Mylist::reference>
    {	// iterator for singlelinkedlist
    public:
        typedef singlelinkedlist_const_iterator<_Mylist> _Myiter;
        typedef typename _Mylist::const_nodeptr _nodeptr;
        typedef typename _Mylist::const_pointer   pointer;
        typedef typename _Mylist::const_reference reference;
        typedef typename _Mylist::difference_type difference_type;
        typedef typename _Mylist::value_type value_type;

        singlelinkedlist_const_iterator()
        {	// construct with null vector pointer
        }

        singlelinkedlist_const_iterator(_nodeptr _Parg, const _Mylist* pMylist): _ptr(_Parg), _pMylist(pMylist)
        {	// construct with pointer _Parg
        }

        reference operator*()const
        {	// return designated object			
            //return this->_ptr->element;
            return (this->_ptr)->element;
        }

        pointer operator->() const
        {	// return pointer to class object
            return &(this->_ptr->element);
        }

        _Myiter& operator++()
        {	// preincrement
            this->_ptr = this->_ptr->next;
            return (*this);
        }

        _Myiter operator++(int)
        {	// postincrement
            _Myiter _Tmp = *this;
            ++*this;
            return (_Tmp);
        }

        _Myiter& operator--()
        {	// predecrement
            this->_ptr = _pMylist->prevnodeptr(this->_ptr);
            return (*this);
        }

        _Myiter operator--(int)
        {	// postdecrement
            _Myiter _Tmp = *this;
            --*this;
            return (_Tmp);
        }

        // _Myiter& operator+=(difference_type _Off) 
        // {	// increment by integer
        // 	for (difference_type i = 0; i<_Off; ++i)
        // 	{
        // 		this->_ptr = this->_ptr->next;
        // 	}	
        // 	return (*this);
        // }

        _Myiter operator+(difference_type _Off)
        {	// return this + integer
            _Myiter _Tmp = *this;
            _Tmp+=_Off;
            return  _Tmp;
        }

        // _Myiter& operator-=(difference_type _Off)
        // {	// increment by integer
        // 	for (difference_type i = 0; i<_Off; ++i)
        // 	{
        // 		--(*this);
        // 	}
        // 	return (*this);
        // }

        _Myiter operator-(difference_type _Off)
        {	// return this + integer
            _Myiter _Tmp = *this;
            _Tmp -= _Off;
            return  _Tmp;
        }

        bool operator==(const _Myiter& _Right) const
        {	// subscript
            return (this->_ptr == _Right._ptr);
        }

        bool operator!=(const _Myiter& _Right) const
        {	// subscript
            return (!(*this == _Right));
        }

        _nodeptr base() const
        {
            return _ptr;
        }

        const _Mylist* const getCont() const
        {
            return _pMylist;
        }


    private:
        _nodeptr _ptr;
        const _Mylist* _pMylist;
    };

    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS singlelinkedlist_iterator
    template<class _Mylist>
    class singlelinkedlist_iterator
        : public singlelinkedlist_const_iterator<_Mylist>
    {	// iterator for singlelinkedlist
    public:
        typedef singlelinkedlist_iterator<_Mylist> _Myiter;
        typedef singlelinkedlist_const_iterator<_Mylist> _Mybase;

        typedef typename _Mylist::nodeptr _nodeptr;
        typedef typename _Mylist::pointer   pointer;
        typedef typename _Mylist::reference reference;
        typedef typename _Mylist::value_type      value_type;
        typedef typename _Mylist::difference_type difference_type;

        singlelinkedlist_iterator()
        {	// construct with null vector pointer
        }

        singlelinkedlist_iterator(_nodeptr _Parg, const _Mylist* pMylist) : _Mybase(_Parg, pMylist)
        {	// construct with pointer _Parg
        }

        reference operator*()const
        {	// return designated object			
            //return this->_ptr->element;
            return (const_cast<reference>(**(_Mybase *)this));
        }

        pointer operator->() const
        {	// return pointer to class object
            return (const_cast<pointer>(**(_Mybase *)this));
        }

        _Myiter& operator++()
        {	// preincrement
            ++*(_Mybase *)this;
            return (*this);
        }

        _Myiter operator++(int)
        {	// postincrement
            _Myiter _Tmp = *this;
            ++*this;
            return (_Tmp);
        }

        _Myiter& operator--()
        {	// predecrement
            --*(_Mybase *)this;
            return (*this);
        }

        _Myiter operator--(int)
        {	// postdecrement
            _Myiter _Tmp = *this;
            --*this;
            return (_Tmp);
        }

        // _Myiter& operator+=(difference_type _Off)
        // {	// increment by integer
        // 	*(_Mybase *)this += _Off;
        // 	return (*this);
        // }

        _Myiter operator+(difference_type _Off)
        {	// return this + integer
            _Myiter _Tmp = *this;
            _Tmp += _Off;
            return  _Tmp;
        }
    };
    /////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS singlelinkedlist_const_iterator
    template<class _Mylist>
    class doublylinkedlist_const_iterator
        : public std::iterator<std::bidirectional_iterator_tag,
        typename _Mylist::value_type,
        typename _Mylist::difference_type,
        typename _Mylist::pointer,
        typename _Mylist::reference>
    {	// iterator for singlelinkedlist
    public:
        typedef doublylinkedlist_const_iterator<_Mylist> _Myiter;
        typedef typename _Mylist::const_nodeptr _nodeptr;
        typedef typename _Mylist::const_pointer   pointer;
        typedef typename _Mylist::const_reference reference;
        typedef typename _Mylist::value_type      value_type;
        typedef typename _Mylist::difference_type difference_type;

        doublylinkedlist_const_iterator()
        {	// construct with null vector pointer
        }

        doublylinkedlist_const_iterator(_nodeptr _Parg, const _Mylist* pMylist) : _ptr(_Parg), _pMylist(pMylist)
        {	// construct with pointer _Parg
        }

        reference operator*()const
        {	// return designated object			
            //return this->_ptr->element;
            return (this->_ptr)->element;
        }

        pointer operator->() const
        {	// return pointer to class object
            return &(this->_ptr->element);
        }

        _Myiter& operator++()
        {	// preincrement
            this->_ptr = this->_ptr->next;
            return (*this);
        }

        _Myiter operator++(int)
        {	// postincrement
            _Myiter _Tmp = *this;
            ++*this;
            return (_Tmp);
        }

        _Myiter& operator--()
        {	// predecrement
            this->_ptr = this->_ptr->prev;
            return (*this);
        }

        _Myiter operator--(int)
        {	// postdecrement
            _Myiter _Tmp = *this;
            --*this;
            return (_Tmp);
        }

        // _Myiter& operator+=(difference_type _Off)
        // {	// increment by integer
        // 	for (difference_type i = 0; i<_Off; ++i)
        // 	{
        // 		this->_ptr = this->_ptr->next;
        // 	}
        // 	return (*this);
        // }

        _Myiter operator+(difference_type _Off)
        {	// return this + integer
            _Myiter _Tmp = *this;
            _Tmp += _Off;
            return  _Tmp;
        }

        // _Myiter& operator-=(difference_type _Off)
        // {	// increment by integer
        // 	for (difference_type i = 0; i<_Off; ++i)
        // 	{
        // 		--(*this);
        // 	}
        // 	return (*this);
        // }

        _Myiter operator-(difference_type _Off)
        {	// return this + integer
            _Myiter _Tmp = *this;
            _Tmp -= _Off;
            return  _Tmp;
        }

        bool operator==(const _Myiter& _Right) const
        {	// subscript
            return (this->_ptr == _Right._ptr);
        }

        bool operator!=(const _Myiter& _Right) const
        {	// subscript
            return (!(*this == _Right));
        }

        _nodeptr base() const
        {
            return _ptr;
        }

        const _Mylist* const getCont() const
        {
            return _pMylist;
        }


    private:
        _nodeptr _ptr;
        const _Mylist* _pMylist;
    };

    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS singlelinkedlist_iterator
    template<class _Mylist>
    class doublylinkedlist_iterator
        : public doublylinkedlist_const_iterator<_Mylist>
    {	// iterator for singlelinkedlist
    public:
        typedef doublylinkedlist_iterator<_Mylist> _Myiter;
        typedef doublylinkedlist_const_iterator<_Mylist> _Mybase;

        typedef typename _Mylist::nodeptr _nodeptr;
        typedef typename _Mylist::pointer   pointer;
        typedef typename _Mylist::reference reference;
        typedef typename _Mylist::value_type      value_type;
        typedef typename _Mylist::difference_type difference_type;

        doublylinkedlist_iterator()
        {	// construct with null vector pointer
        }

        doublylinkedlist_iterator(_nodeptr _Parg, const _Mylist* pMylist) : _Mybase(_Parg, pMylist)
        {	// construct with pointer _Parg
        }

        reference operator*()const
        {	// return designated object			
            //return this->_ptr->element;
            return (const_cast<reference>(**(_Mybase *)this));
        }

        pointer operator->() const
        {	// return pointer to class object
            return (const_cast<pointer>(**(_Mybase *)this));
        }

        _Myiter& operator++()
        {	// preincrement
            ++*(_Mybase *)this;
            return (*this);
        }

        _Myiter operator++(int)
        {	// postincrement
            _Myiter _Tmp = *this;
            ++*this;
            return (_Tmp);
        }

        _Myiter& operator--()
        {	// predecrement
            --*(_Mybase *)this;
            return (*this);
        }

        _Myiter operator--(int)
        {	// postdecrement
            _Myiter _Tmp = *this;
            --*this;
            return (_Tmp);
        }

        // _Myiter& operator+=(difference_type _Off)
        // {	// increment by integer
        // 	*(_Mybase *)this += _Off;
        // 	return (*this);
        // }

        _Myiter operator+(difference_type _Off)
        {	// return this + integer
            _Myiter _Tmp = *this;
            _Tmp += _Off;
            return  _Tmp;
        }
    };
    /////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS rhashmap_const_iterator
    template<class _Mylist>
    class rhashmap_const_iterator {};
    ///////////////////////////////////////////////////////////////
    // TEMPLATE CLASS rhashmap_iterator
    template<class _Mylist>
    class rhashmap_iterator {};
    //////////////////////////////////////////////////////////////
}
#endif