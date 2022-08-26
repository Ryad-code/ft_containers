#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <iomanip>
#include "Pair.hpp"
#include "Iterator.hpp"
#include "Map_iterator.hpp"
#include "Enable_if.hpp"
#include "Is_integral.hpp"
#include "Lexicographical_compare.hpp"

namespace ft
{
////////AVL NODE STRUCT
	template <typename V>
	struct Node
	{
		V	value;
		Node*	left;
		Node*	right;
		Node*	parent;
		bool	last;
		Node(V v, Node* l, Node* r, Node* p, bool x = false): value(v), left(l), right(r), parent(p), last(x) {}
		~Node() {}
	};
////////MAP CLASS
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
//......................TYPE DEFINITION
			typedef	Key								key_type;
			typedef	T								mapped_type;
			typedef	ft::pair<const key_type, mapped_type>				value_type;
			typedef	Compare								key_compare;
			typedef	Node<value_type>						node_type;
			typedef Alloc								allocator_type;
			//Allocators and Iterators typedef
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_type			difference_type;
			typedef map_iterator<value_type, node_type*>				iterator;
			typedef map_iterator<const value_type, node_type*>			const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;	
//......................VALUE COMPARE CLASS
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c): comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_type;
					typedef	value_type	second_type;
					bool	operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		protected:
			node_allocator	_alloc;
			key_compare	_key_compare;
			size_type	_size;
			node_type*	_root;

		public:
			//Construct & Destruct
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_alloc(alloc),
				_key_compare(comp),
				_size(0),
				_root(NULL) {}
			
			template <class InputIterator>
			map (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_alloc(alloc),
				_key_compare(comp),
				_size(0),
				_root(NULL)
			{
				insert(first, last);
			}

			map(const map& obj):
				_alloc(obj._alloc),
				_key_compare(obj._key_compare),
				_size(0),
				_root(NULL)
			{
				*this = obj;
			}

			~map()
			{
				clear_node(_root);
			}

			map& operator=(const map& obj)
			{
				clear_node(_root);
				insert(obj.begin(), obj.end());
				return *this;
			}

////////////////////////PRIVATE TREE FUNCTIONS
		private:
			node_type*	new_node(const value_type& val, node_type *parent)
			{
				node_type* temp = _alloc.allocate(1);
				_alloc.construct(temp, node_type(val, NULL, NULL, parent, false));
				_size++;
				return temp;
			}

			node_type*	min_node(node_type *current)
			{
				//Litte diff here
				while (current->left)
					current = current->left;
				return current;
			}

			node_type*	max_node(node_type* current)
			{
				while (current->right)
					current = current->right;
				return current;
			}

			node_type*	insert_node_root(const value_type& val, node_type* current, node_type *parent = NULL)
			{
				if (!_root)
				{
					_root = new_node(val, NULL);
					node_type* l = new_node(value_type(key_type(), mapped_type()), _root);
					_size--;
					_root->right = l;
					l->last = true;
					return _root;
				}
				if (_root->last)
				{
					node_type* new_root = new_node(val, NULL);
					_root->parent = new_root;
					new_root->right = _root;
					_root = new_root;
					return _root;
				}
				return insert_node(val, current, parent);
			}

			node_type*	insert_node(const value_type& val, node_type* current, node_type* parent)
			{
				if (!current)
					return new_node(val, parent);
				if (current->last)
				{
					node_type* to_insert = new_node(val, parent);
					current->parent = to_insert;
					to_insert->right = current;
					current = to_insert;
					return current;
				}
				if (_key_compare(val.first, current->value.first))
					current->left = insert_node(val, current->left, current);
				else if (_key_compare(current->value.first, val.first))
					current->right = insert_node(val, current->right, current);
				return current;
			}

			node_type*	delete_node(node_type* current, const key_type& key)
			{
				if (!current || current->last)
					return current;
				if (_key_compare(key, current->value.first))
					current->left = delete_node(current->left, key);
				else if (_key_compare(current->value.first, key))
					current->right = delete_node(current->right, key);
				else
				{
					if (!current->left || !current->right)
					{
						node_type* temp = current->left ? current->left : current->right;
						if (!current->left && !current->right)
						{
							temp = current;
							_alloc.destroy(temp);
							_alloc.deallocate(temp, 1);
							current = NULL;
							_size--;
						}
						else
						{
							temp->parent = current->parent;
							node_type* temp1 = current;
							current = temp;
							_alloc.destroy(temp1);
							_alloc.deallocate(temp1, 1);
							_size--;
						}
					}
					else
					{
						node_type* temp = min_node(current->right);
						if (temp != current->right)
						{
							temp->right = current->right;
							current->right->parent = temp;
						}
						temp->left = current->left;
						current->left->parent = temp;
						temp->parent->left = NULL;
						temp->parent = current->parent;
						if (_root == current)
							_root = temp;
						_alloc.destroy(current);
						_alloc.deallocate(current, 1);
						_size--;
						current =  temp;
					}
				}
				return current;
			}

			void		clear_node(node_type* current)
			{
				if (current)
				{
					clear_node(current->left);
					clear_node(current->right);
					_alloc.destroy(current);
					_alloc.deallocate(current, 1);
					if (_size > 0)
						_size--;
					if (current == _root)
						_root = NULL;
				}
					
			}
			
			node_type*	find_key(const key_type& key, node_type* current)
			{
				if (!current || current->last)
					return NULL;
				if (_key_compare(key, current->value.first))
					return find_key(key, current->left);
				else if (_key_compare(current->value.first, key))
					return find_key(key, current->right);
				else
					return current;
			}

			node_type*	const_find_key(const key_type& key, node_type* current) const
			{
				if (!current || current->last)
					return NULL;
				if (_key_compare(key, current->value.first))
					return const_find_key(key, current->left);
				else if (_key_compare(current->value.first, key))
					return const_find_key(key, current->right);
				else
					return current;
			}

			void		tree_init(void)
			{
				insert(value_type(key_type(), mapped_type()));
				_root->last = true;
				_size--;
			}
////////////////////////PUBLIC CLASS METHODS
		public:
//......................CAPACITY
			bool		empty(void) const
			{
				return _size == 0;
			}

			size_type	size(void) const
			{
				return _size;
			}

			size_type	max_size(void) const
			{
				return _alloc.max_size();
			}
//......................OBSERVERS
			key_compare	key_comp(void) const
			{
				return _key_compare;
			}

			value_compare	value_comp(void) const
			{
				return value_compare(key_compare());
			}
//......................ITERATOR METHODS
			iterator	begin(void)
			{
				if (_size == 0)
					return iterator(_root);
				node_type* temp = _root;
				while (temp && temp->left)
					temp = temp->left;
				return iterator(temp);
			}

			const_iterator	begin(void) const
			{
				if (_size == 0)
					return const_iterator(_root);
				node_type* temp = _root;
				while (temp && temp->left)
					temp = temp->left;
				return const_iterator(temp);
			}

			iterator	end(void)
			{
				if (!_root)
					tree_init();
				if (_size == 0)
					return iterator(_root);
				node_type* temp = _root;
				while (temp && temp->right)
					temp = temp->right;
				return iterator(temp);
			}

			const_iterator	end(void) const
			{
				if (_size == 0)
					return const_iterator(_root);
				node_type* temp = _root;
				while (temp && temp->right)
					temp = temp->right;
				return const_iterator(temp);
			}

			reverse_iterator	rbegin(void)
			{
				return reverse_iterator(end()--);
			}

			const_reverse_iterator	rbegin(void) const
			{
				return const_reverse_iterator(end()--);
			}

			reverse_iterator	rend(void)
			{
				return everse_iterator(begin());
			}

			const_reverse_iterator	rend(void) const
			{
				return const_reverse_iterator(begin());
			}
//......................ELEMENT ACCES
			mapped_type&		operator[](const key_type& key)
			{
				node_type* temp = find_key(key, _root);
				if (temp)
					return temp->value.second;
				insert(value_type(key, mapped_type()));
				return find_key(key, _root)->value.second;
			}
//......................MODIFIERS
			pair<iterator, bool>	insert(const value_type& val)
			{
				size_t temp = _size;
				insert_node_root(val, _root);
				return (pair<iterator,bool>(find_key(val.first, _root), temp != _size));
			}

			iterator		insert(iterator pos, const value_type& val)
			{
				(void)pos;
				insert_node_root(val, _root);
				return iterator(find_key(val.first, _root));
			}

			template <class InputIterator>
			void 			insert (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				for (;first != last; first++)
					insert(*first);
			}

			void			erase(iterator pos)
			{
				erase(pos->first);
			}

			size_type		erase(const key_type& key)
			{
				size_type temp = _size;
				_root = delete_node(_root, key);
				return temp - _size;
			}

			void			erase(iterator first, iterator last)
			{
				map<key_type, mapped_type> temp(first, last);
				iterator it1 = temp.begin();
				iterator it2 = temp.end();
				for (; it1 != it2; it1++)
					_root = delete_node(_root, it1->first);
			}

			void			swap(map& obj)
			{
				node_allocator temp_alloc = _alloc;
				key_compare temp_key_compare = _key_compare;
				size_type temp_size = _size;
				node_type* temp_root = _root;
				_alloc = obj._alloc;
				_key_compare = obj._key_compare;
				_size = obj._size;
				_root = obj._root;
				obj._alloc = temp_alloc;
				obj._key_compare = temp_key_compare;
				obj._size = temp_size;
				obj._root = temp_root;
			}

			void			clear(void)
			{
				clear_node(_root);
			}
//......................OPERATIONS
			iterator		find(const key_type& key)
			{
				node_type* temp = find_key(key, _root);
				if (temp)
					return iterator(temp);
				return end();
			}

			const_iterator		find(const key_type& key) const
			{
				node_type* temp = const_find_key(key, _root);
				if (temp)
					return const_iterator(temp);
				return end();
			}

			size_type		count(const key_type& key) const
			{
				node_type* temp = const_find_key(key, _root);
				if (temp)
					return 1;
				return 0;
			}

			iterator		lower_bound(const key_type& key)
			{
				iterator it1 = end();
				for (iterator it2 = begin(); it2 != it1; it2++)
					if (!_key_compare(it2->first, key))
						return it2;
				return it1;
			}

			const_iterator		lower_bound(const key_type& key) const
			{
				const_iterator it1 = end();
				for (const_iterator it2 = begin(); it2 != it1; it2++)
					if (!_key_compare(it2->first, key))
						return const_iterator(it2);
				return it1;
			}

			iterator		upper_bound(const key_type& key)
			{
				iterator it1 = end();
				for (iterator it2 = begin(); it2 != it1; it2++)
					 if (_key_compare(key, it2->first))
						 return it2;
				return it1;
			}

			const_iterator		upper_bound(const key_type& key) const
			{
				const_iterator it1 = end();
				for (const_iterator it2 = begin(); it2 != it1; it2++)
					if (_key_compare(key, it2->first))
						return const_iterator(it2);
				return it1;
			}

			pair<iterator,iterator> equal_range (const key_type& key)
			{
				return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& key) const
			{
				return pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
			}
//......................ALLOCATOR
			allocator_type get_allocator() const
			{
				return _alloc;
			}
	};
//......................UTILS
			template <class InputIterator1, class InputIterator2>
			bool equal1(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
			{
				while (first1!=last1)
				{
					if (!(*first1 == *first2))
						return false;
					++first1; ++first2;
				}
				return true;
			}
////////////////////////NON-MEMBER FUNCTIONS (overload)
			template <class Key, class T, class Compare, class Alloc>
			bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				return equal1(lhs.begin(), lhs.end(), rhs.begin());
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
			{
				return !(lhs == rhs);
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator< (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
			{
				return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
			{
				return (lhs < rhs || lhs == rhs);
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator> (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
			{
				return rhs < lhs;
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
			{
				return (lhs > rhs || lhs == rhs);
			}

			template <class Key, class T, class Compare, class Alloc>
			void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
			{
				x.swap(y);
			}
			
}

#endif

