#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>
#include <stack> //iterator stack ???

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
		//	typedef std::vector<T>::iterator		it;
		//	typedef std::random_access_iterator<T>			iterator;
		//	typedef std::random_access_iterator<const T>		const_iterator;
		//	typedef std::reverse_iterator<iterator>			reverse_iterator;
		//	typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

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
//....................................................................................//DESTRUCTOR
			~vector(void)
			{
			//	clear(); ---> ne passe pas la compil
				_alloc.deallocate(_pointer, _capacity);
			};
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

			size_t capacity(void) const		//Capacity of the current allocated storage (not necessarily equal to _size)
			{
				return _capacity;
			};

			void reserve(int new_capacity)		//Redefine capacity of the current allocated storage
			{
				if (new_capacity > max_size())
					throw std::length_error("vector::reserve");
				else if (new_capacity <= capacity())
					return;
				else
				{
					pointer	tmp;

					tmp = _alloc.allocate(new_capacity);
					for (int i = 0; i < _size; i++)
					{
						_alloc.construct(tmp + i, *(_pointer + i));
						_alloc.destroy(_pointer + i);
					}
					_alloc.deallocate(_pointer, _capacity);
					_capacity = new_capacity;
					_pointer = tmp;
				}
			};
//................................................................................//TEST
			pointer get_pointer(void)
			{
				return _pointer;
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
//....................................................................................//MODIFIERS
			void	push_back(const T& value)
			{
				if (_capacity == 0)
					reserve(1);
				else if (_size == _capacity && _capacity != 0)
					reserve(_capacity + 1);
				_alloc.construct(_pointer + _size, value);
				_size++;
			};

			void	pop_back(void)
			{
				_alloc.destroy(_pointer + (_size - 1));
				_size--;
			};



	};
}

#endif
