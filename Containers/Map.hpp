#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <iomanip>
#include <../Utils/Pair.hpp>

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
		Node(V v, Node* l, Node* r, Node* p, bool l = false): value(v), left(l), right(r), parent(p), last(e) {}
		~Node() {}
	};
////////MAP CLASS
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft:pair<const Key, T> > >
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
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
			//Allocators and Iterators typedef
		
		protected:
			node_allocator	_alloc;
			key_compare	_key_compare;
			size_type	_size;
			node_type*	_root;

		public:
			//Construct & Destruct
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_alloc_type(alloc),
				_key_compare(comp),
				_size(0),
				_root(NULL) {}

								//--->Range constructor to do
			map(const map& obj):
				_alloc_type(obj.alloc_type),
				_key_compare(obj._key_compare),
				_size(0),
				_root(NULL)
			{
				*this = obj
			}

			~map() {}				//--->Destrcutor to do

			map& operator=(const map& obj) {}	//--->Operator =  to do

//......................TREE FUNCTIONS
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
					node_type* *last = new_node(value_type(key_type(), mapped_type()), _root);
					_size--;
					_root->right = last;
					last->last = true;
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
			//..INSERT_NODE to do
				
			


	};
}

#endif

