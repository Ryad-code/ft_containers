#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include <cstddef>
#include <algorithm>

#include "../Utils/Iterator.hpp"
#include "../Utils/Pair.hpp"
#include "Node.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef Key							key_type;
			typedef T							mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef Compare							key_compare;
			typedef Allocator 						allocator_type;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef typename Allocator::size_type				size_type;
			typedef typename Allocator::difference_type			difference_type;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer			const_pointer;
		//.............................................................................
			typedef ft::Node<key_type, mapped_type>				map_node;
		//.............................................................................
			typedef ft::Iterator<value_type>				iterator;
			typedef ft::const Iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		//............................................................................
			typedef typename Allocator::template rebind<map_node>::other	node_allocator_type;
		//............................................................................


		//....................................................PRIVATE ATTRIBUTES
		private:
			key_compare		_compare;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			size_type		_size;
			map_node		*_root;
			map_node		*_begin;
			map_node		*_end;
		//....................................................PUBLIC SUB-CLASSES & METHODS
		public:
			class value_compare
			{
				friend class map;
				
				protected:
					Compare _comp;
					value_compare (Compare c) : _comp(c)
					{
					}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator () (const value_type &x, const value_type &y) const
					{
						return _comp(x.first, y.first);
					}
			};

		//....................................................CONSTRUCTORS
			explicit map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
				_compare(comp),
				_alloc(alloc),
				_node_alloc(std::allocator<map_node>()),
				_root(NULL),
				_end(NULL),
				_rend(NULL),
				_size(0)
			{
				_end = _node_alloc.allocate(1);
				_node_alloc.construct(_end, map_node());
				_rend = _node_alloc.allocate(1);
				_node_alloc.construct(_rend, map_node());
				_rend->parent = _end;
			}

			map (const map &x)
			{
				_end = _node_alloc.allocate(1);
				_node_alloc.construct(_end, map_node());
				_rend = _node_alloc.allocate(1);
				_node_alloc.construct(_rend, map_node());
				_rend->parent = _end;
				_root = NULL;
				*this = x;
			}

/*			template <class InputIterator>
			map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_alloc_type(alloc),
				_key_compare(comp),
				_size(0), _root(NULL)
			{
				insert(first, last);
				}*/


	};
}

#endif
