#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <limits>
#include <typeinfo>
#include <cstddef>

namespace ft
{
	struct	input_iterator_tag {};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag: public input_iterator_tag {};
	struct	bidirectional_iterator_tag: public forward_iterator_tag {};
	struct	random_access_iterator_tag: public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T		value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer			pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T						value_type;
		typedef T*						pointer;
		typedef T&						reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T						value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};
//......................................................................RANDOM_ACCESS_ITERATOR

	template <class T>
	class random_access_iterator
	{
		protected:
			pointer	_current;

		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>:: pointer			pointer;

//.....................................................................CONSTRUCTORS
			random_access_iterator() : _current(0) {};
			
			explicit random_access_iterator(pointer x) : _current(x) {};
	};
}

#endif