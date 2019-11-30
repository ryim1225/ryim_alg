#ifndef _R_HASH_MAP_H_
#define _R_HASH_MAP_H_
#include <functional>
#include <hash_map>
#include "rArrayList.h"
#include "rIterator.h"

namespace Ryim
{
	////////////////////////////////////////////////////
	// Hashing with separate chaining: A hash function converts keys into array indices.
	// The second component of a hashing algorithm is collision resolution : a strategy for handling
	// the case when two or more keys to be inserted hash to the same index.
	// A straightforward approach to collision resolution is to build, for each of the M array indices,
	// a linked list of the key - value pairs whose keys hash to that index.
	// The basic idea is to choose M to be sufficiently large that the lists are sufficiently short to enable 
	// efficient search through a two - step process : hash to find the list that could contain the key, 
	// then sequentially search through that list for the key
	//
	// Bibliography:
	// https://algs4.cs.princeton.edu/34hash/
	// <<Introduction to Algorithms>>
	///////////////////////////////////////////////////

	template<typename Key, typename T>
	struct  HashMapNode
	{
		std::pair<Key, T> kv;
		HashMapNode* next;
	};

	template<typename Key, typename T, typename Hash = std::hash<Key>, 
		typename Alloc = std::allocator<HashMapNode<Key, T>> >
	class rHashMap
	{
	public:
		typedef rHashMap<Key, T, Hash, Alloc> _Myt;
		typedef typename T mapped_type;
		typedef typename Key Key_type;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename HashMapNode* bucket;
		typedef typename Ryim::arraylist<bucket>* buckets;

		typedef typename rhashmap_iterator<_Myt>		iterator;
		typedef typename rhashmap_const_iterator<_Myt> const_iterator;
	public:
		rHashMap():
			m_nBucketsSize(997), 
			m_nSize(0)
		{};
		~rHashMap() {};
#if _MSC_VER  < 1800
#else
		rHashMap(std::initializer_list<std::pair<Key, mapped_type> > initList)
		{
			m_nBucketsSize = 997;
			m_nSize(0);
			for (auto i = initList.begin(); i != initList.end(); ++i)
			{
			}
		}

		_Myt& operator=(std::initializer_list<std::pair<Key, mapped_type> > initList)
		{
			for (auto i = initList.begin(); i != initList.end(); ++i)
			{
			}
			return (*this);
		}
#endif

		void insert(std::pair<Key, mapped_type> kv)
		{
			size_type code = hash(ky);
			bucket temp = m_pBuckets->at(code);

			if (temp)
			{
				temp->kv.second = kv.second;
			}
			else
			{
				bucket newNode = m_alloc.allocate(1);
				newNode->kv = kv;
				newNode->next = nullptr;

				m_pBuckets[code] = newNode;
				newNode->next = temp;
			}

			return;
		}

		mapped_type& operator[](const Key_type& ky)
		{
			bucket temp = findBucket(ky);
			if (temp)
			{
				return temp->kv.second;
			}
			else
			{
				throw; // to do
			}
		}

	private:
		void init()
		{
			m_pBuckets = new buckets(m_nBucketsSize, nullptr); 
		}

		void RemoveAll()
		{
			for (size_t i = 0; i<m_nBucketsSize; ++i)
			{
	/*			m_pBuckets[i]->removeall();
				if (nullptr != m_pBuckets[i])
				{
					delete m_pBuckets[i];
					m_pBuckets[i] = nullptr;
				}*/
			}

			if (nullptr != m_pBuckets)
			{
				delete m_pBuckets;
				m_pBuckets = nullptr;
			}
		}

		bucket findBucket(const Key_type& ky)
		{
			size_type code = hash(ky);
			bucket temp = m_pBuckets->at(code);
			while (temp != nullptr)
			{
				if (temp->kv.first == ky)
					break;
				
				temp = temp->next;
			}
			return temp;
		}

		size_type hash(const Key_type& kt)
		{
			return m_nHashCode(kt) % m_nBucketsSize;
		}

		
	private:
		buckets m_pBuckets;
		size_type m_nBucketsSize;
		size_type m_nSize;
		Hash m_nHashCode;
		Alloc m_alloc;
	};
}
#endif
