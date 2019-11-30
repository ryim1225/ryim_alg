#ifndef _R_RYIM_SIMPLE_ALLOC_
#define _R_RYIM_SIMPLE_ALLOC_
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>
namespace Ryim
{
	template<typename T>
	class allocator
	{
	public:
		typedef T              value_type;
		typedef T*		       pointer;
		typedef const T*       const_pointer;
		typedef T&             reference;
		typedef const T&       const_reference;
		typedef std::size_t    size_type;
		typedef std::ptrdiff_t difference_type;

		// rebind allocator of type u
		template<typename U>
		struct rebind{typedef allocator<U> other;};

		pointer allocate(size_type n, const void* hint =0)
		{
			return _allocate( (difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n)
		{
			if (p)
			{
				::operator delete(p);
			}
		}

		void construct(pointer p, const_reference value)
		{
			new ((void*)p) value_type(value);
		}

		void destroy(pointer p)
		{
			if (NULL != p)
			{
				p->~T();
			};
		}

		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const_pointer const_address(const_reference x)
		{
			return (const_pointer)&x;
		}

		size_type max_size() const
		{
			return size_type(UINT_MAX/sizeof(T));
		}

	private:
		T* _allocate(std::ptrdiff_t size, T*)
		{
			std::set_new_handler(0);
			T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
			if (0 == tmp)
			{
				throw std::bad_alloc();
				std::abort();
			}
			return tmp;
		}
	};
}
#endif // !_RYIM_SIMPLE_ALLOC_
