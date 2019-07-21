#ifndef _R_UTILITY_H_
#define _R_UTILITY_H_

#include <deque>
#include <algorithm>
#include "rException.h"

namespace Ryim
{
    //////////////////////////////////////////////////////////////////////////
    namespace Assign
    {
        namespace assign_detail
        {
            template<typename T, typename cont = std::deque<T>>
            class generic_list
            {
            public:
                generic_list& operator()(const T& element)
                {
                    values.push_back(element);
                    return *this;
                }

                generic_list& operator,(const T& element)
                {
                    values.push_back(element);
                    return *this;
                }

                template< class Container >
                operator Container() const
                {
                    //static Container* c = NULL;
                    Container result;
                    typename cont::const_iterator it  = values.begin(), 
                        e   = values.end();
                    while( it != e )
                    {
                        result.insert( result.end(), *it );
                        ++it;
                    }
                    return result;
                }
            private:
                cont values;
            };

        }
        
        template< class T >
        inline assign_detail::generic_list<T>
            list_of()
        {
            return assign_detail::generic_list<T>()( T() );
        }

        template< class T >
        inline assign_detail::generic_list<T> 
            list_of( const T& t )
        {
            return assign_detail::generic_list<T>()( t );
        }
    }

    //////////////////////////////////////////////////////////////////////////
    namespace AlgTools
    {
        // TEMPLATE FUCTION swap
        template<typename Elem>
        void swap(Elem A[], int l, int r)
        {
            Elem temp;
            temp = A[l];
            A[l] = A[r];
            A[r] = temp;
            return;
        }
        //////////////////////////////////////////////////////////////////////////

        // TEMPLATE STRUCT equal_to
        template<class _Ty>
        struct compare
        {	// functor for compare Left to Right
            int operator()(const _Ty& _Left, const _Ty& _Right) const
            {	// if Left < Right, return -1;if Left > Right, return 1; otherwise, return 0
                 if (_Left < _Right) return -1;
                 else if (_Left > _Right) return 1;
                 else return 0;
            }
        };

        // TEMPLATE STRUCT equal_to
        template<class _Ty>
        struct equal_to
        {	// functor for operator==
            bool operator()(const _Ty& _Left, const _Ty& _Right) const
            {	// apply operator== to operands
                return (_Left == _Right);
            }
        };

        // TEMPLATE STRUCT not_equal_to
        template<class _Ty>
        struct not_equal_to
        {	// functor for operator!=
            bool operator()(const _Ty& _Left, const _Ty& _Right) const
            {	// apply operator== to operands
                return !(_Left == _Right);
            }
        };

        // TEMPLATE STRUCT less
        template<class _Ty>
        struct less
        {	// functor for operator<
            bool operator()(const _Ty& _Left, const _Ty& _Right) const
            {	// apply operator< to operands
                return (_Left < _Right);
            }
        };

        // TEMPLATE STRUCT great
        template<class _Ty>
        struct great
        {	// functor for operator<
            bool operator()(const _Ty& _Left, const _Ty& _Right) const
            {	// apply operator< to operands
                return (_Left > _Right);
            }
        };
        // TEMPLATE STRUCT less_equal
        template<class _Ty>
        struct less_equal
        {	// functor for operator<
            bool operator()(const _Ty& _Left, const _Ty& _Right) const
            {	// apply operator< to operands
                return !(_Left > _Right);
            }
        };

        // TEMPLATE STRUCT great_equal
        template<class _Ty>
        struct great_equal
        {	// functor for operator<
            bool operator()(const _Ty& _Left, const _Ty& _Right) const
            {	// apply operator< to operands
                return !(_Left < _Right);
            }
        };
        //////////////////////////////////////////////////////////////////////////

        // copy function --- it's unsafe
        template<typename InIt, typename OutIt>
        OutIt copy(InIt _First, InIt _Last, OutIt _Dest)
        {
            for (; _First != _Last; ++_Dest, ++_First)
                *_Dest = *_First;
            return (_Dest);
        }

        template<typename InIt, typename OutIt>
        void copy_backward(InIt _First, InIt _Last, OutIt _Dest)
        {
            while (_First != _Last)
                *--_Dest = *--_Last;
        }

        //////////////////////////////////////////////////////////////////////////
        // min_a_b function --- it's unsafe
        template<typename T>
        T minimum(T a, T b)
        {
            return (a < b) ? a : b;
        }

        //////////////////////////////////////////////////////////////////////////
        // min_a_b function --- it's unsafe
        template<typename T>
        T maximum(T a, T b)
        {
            return (a > b) ? a : b;
        }

        ///////////////////////////////////////////////////////////////////////////
        template<typename Elem>
        void changeLength1D(Elem*& a, std::size_t oldLength, std::size_t newLength)
        {
            if (newLength < 0)
                throw illegalParameterValue("new length must be >= 0!");

            Elem* temp = new Elem[newLength];
            std::size_t number = Ryim::AlgTools::minimum(oldLength, newLength);

            Ryim::AlgTools::copy(a, a + number, temp);

            delete[] a;
            a = temp;
        }
    }
}
#endif // !_UTILITY_H_
