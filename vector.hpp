#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>
#include "Vector_iterator.hpp"
#include "Enable_if.hpp"
#include "Lexicographical_compare.hpp"
#include "Is_integral.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T						value_type;
			typedef Allocator					allocator_type;
			typedef std::size_t					size_type;
			typedef std::ptrdiff_t					difference_type;
			typedef value_type&					reference;
			typedef const value_type&				const_reference;
			typedef value_type*					pointer;
			typedef const value_type*				const_pointer;
			typedef ft::random_access_iterator<T>			iterator;
			typedef ft::random_access_iterator<const T>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			pointer		_pointer;
			allocator_type	_alloc;
			size_type	_capacity;
			size_type	_size;

		public:
//.....................................................................................//CONSTRUCTORS
			explicit vector(const Allocator& alloc = Allocator()) : _pointer(0), _alloc(alloc), _capacity(0), _size(0)
			{
			};

			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _pointer(0), _alloc(alloc), _capacity(count), _size(count)
			{
				_pointer = _alloc.allocate(count);
				for (size_type i(0); i < count; i++)
				{
					_alloc.construct(_pointer + i, value);
				}
			};

			template <class InputIterator>
			vector( InputIterator first, InputIterator last, const Allocator& alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _pointer(NULL), _alloc(alloc), _capacity(0), _size(0)
			{
				assign(first, last);
			}

			vector(const vector<T,Allocator>& x) : _alloc(x._alloc)
			{
				_pointer = _alloc.allocate(x._capacity);
				for (size_type i(0); i < x._size; i++)
				{
					_alloc.construct(_pointer + i, *(x._pointer + i));
				}
				_size = x._size;
				_capacity = x._size;
			}

			vector<T, Allocator>& operator=(const vector< T, Allocator >& x)
			{
				if (this != &x)
					assign(x.begin(), x.end());
				return *this;
			}
//....................................................................................//DESTRUCTOR
			~vector(void)
			{
				clear();
				_alloc.deallocate(_pointer, _capacity);
			};
//......................ASSIGN
			template <class InputIterator>
			void assign( InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				erase(begin(), end());
				insert(begin(), first, last);
			}

			void assign(size_type n, const T& u)
			{
				erase(begin(), end());
				insert(begin(), n, u);
			}
//......................ALLOCATOR
			allocator_type get_allocator() const
			{
				return _alloc;
			}
//....................................................................................//CAPACITY
			bool empty(void) const			//Checks if vector is empty
			{
				return (_size == 0);
			};

			size_t size(void) const			//Returns the number of elements
			{
				return _size;
			};

			size_t max_size(void) const		//Returns the maximum possible number of elements
			{
				return _alloc.max_size();
			};

			void	resize(size_type sz, T c = T())
			{
				if (sz > size())
					insert(end(), sz - size(), c);
				else if (sz < size())
					erase(begin() + sz, end());
				else
					return;
			}

			size_t capacity(void) const		//Capacity of the current allocated storage (not necessarily equal to _size)
			{
				return _capacity;
			};

			void reserve(size_type new_capacity)		//Redefine capacity of the current allocated storage
			{
				if (new_capacity > max_size())
					throw std::length_error("vector::reserve");
				else if (new_capacity <= capacity())
					return;
				else
				{
					pointer	tmp;

					tmp = _alloc.allocate(new_capacity);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(tmp + i, *(_pointer + i));
						_alloc.destroy(_pointer + i);
					}
					_alloc.deallocate(_pointer, _capacity);
					_capacity = new_capacity;
					_pointer = tmp;
				}
			};
//................................................................................//ELEMENTS ACCESS
			reference	operator[](size_type index)
			{
				return *(_pointer + index);
			};
			
			const_reference	operator[](size_type index) const
			{
				return *(_pointer + index);
			};

			reference	at(size_type index)
			{
				if (index >= _size)
					throw std::out_of_range("out_of_range exception!");
				else
					return *(_pointer + index);
			};

			const_reference	at(size_type index) const
			{
				if (index >= _size)
					throw std::out_of_range("out_of_range exception!");
				else
					return *(_pointer + index);
			};
			
			reference	front(void)
			{
				return *(_pointer);
			};

			const_reference	front(void) const
			{
				return *(_pointer);
			};

			reference	back(void)
			{
				return *(_pointer + (_size - 1));
			};

			const_reference	back(void) const
			{
				return *(_pointer + (_size - 1));
			};
//....................................................................................//ITERATOR
			iterator begin()
			{
				return iterator(_pointer);
			};

			const_iterator begin() const
			{
				return const_iterator(_pointer);
			};

			iterator end()
			{
				return iterator(_pointer + _size);
			};

			const_iterator end() const
			{
				return const_iterator(_pointer + _size);
			};

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			};

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			};

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			};
		
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			};
//....................................................................................//MODIFIERS		
			void push_back( const T& x )
			{
				if (_capacity == 0) {
					reserve(1);
				}
				else if (_size == _capacity && _capacity != 0) {
					reserve(2 * _capacity);
				}
				_alloc.construct(_pointer + _size, x);
				_size++;
			};

			void pop_back()
			{
				_alloc.destroy(&this->back());
				_size--;
			};

			iterator insert( iterator position, const T& x )
			{
				size_type distance;
				distance = position - this->begin();
				if (_capacity == 0)
				{
					reserve(1);
				}
				else if (_capacity == _size && _capacity!= 0)
				{
					reserve(2 * _capacity);
				}
				for (size_type j(_size); j > distance; j--)
				{
					_alloc.construct(_pointer + j, _pointer[j - 1]);
				}
				_alloc.construct(_pointer + distance, x);
				_size++;
				return this->begin() + distance;
			};

			void insert( iterator position, size_type n, const T& x ) {
				if (n == 0)
					return ;
				difference_type distance;
				distance = position - this->begin();
				if (_capacity < _size + n && _size * 2 >= _size + n)
				{
					reserve(2 * _size);
				}
				else
				{
					reserve(_size + n);
				}
				for (difference_type i(_size - 1); i >= distance; i--)
				{
					_alloc.construct(_pointer + n + i, _pointer[i]);
					_alloc.destroy(_pointer + i);
				}
				_size += n;
				for (size_type j(0); j < n; j++)
				{
					_alloc.construct(_pointer + j + distance, x);
				}
			};

			template <class InputIterator>
			void insert( iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL )
			{
				difference_type distance = 0;
				size_type it_dist = 0;
				size_type prev_size = _size;
				size_type j = 0;
				InputIterator it = first;
				while (it != last)
				{
					it_dist++;
					it++;
				}
				distance = position - this->begin();
				if (_capacity < _size + it_dist && _size * 2 > _size + it_dist)
				{
					reserve(2 * _size);
				}
				else
				{
					reserve(_size + it_dist);
				}
				for (difference_type i(prev_size - 1); i >= distance; i--)
				{
					_alloc.construct(&_pointer[it_dist + i], _pointer[i]);
					_alloc.destroy(_pointer + i);
				}
				while (first != last)
				{
					_alloc.construct(&_pointer[j + distance], *first++);
					j++;
					_size++;
				}
			};

			iterator erase( iterator position )
			{
				size_type	distance;
				size_type	i;
				iterator	it;
				i = 0;
				it = this->begin();
				distance = position - it;
				i = distance;
				while (it + distance != this->end() - 1)
				{
					i++;
					_pointer[i - 1] = _pointer[i];
					it++;	
				}
				this->pop_back();
				return this->begin() + distance;
			};

			iterator erase( iterator first, iterator last)
			{
				size_type	i;
				iterator	it;
				i = 0;
				it = this->begin();
				while (it != first)
				{
					i++;
					it++;
				}
				while (first != last)
				{
					erase(it);
					++first;
				}
				return this->begin() + i;
			};

			void swap( vector<T,Allocator>& b)
			{
				std::swap(_pointer, b._pointer);
				std::swap(_size, b._size);
				std::swap(_capacity, b._capacity);
			};

			void clear()
			{
				for (size_type i(0); i < _size; i++)
				{
					_alloc.destroy(_pointer + i);
				}
				_size = 0;
			};
	};
//...................................................................................OPERATORS
		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return equal(lhs.begin(), lhs.end(), rhs.begin());
		}
	
		template <class T, class Allocator>
		bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		};

		template <class T, class Allocator>
		bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return (!(x==y));
		};

		template <class T, class Allocator>
		bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return (y < x);
		};

		template <class T, class Allocator>
		bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return (!(x < y));
		};

		template <class T, class Allocator>
		bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return (!(y < x));
		};
}

#endif
