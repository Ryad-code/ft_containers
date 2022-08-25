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

			node_type*	insert_node(onst value_type& val, node_type* current, node_type* parent)
			{
				if (!current)
					return new_node(val, parent);
				if (current->last)
				{
					node_type* to_insert = new_node(val, parent);
					current->parent = to_insert;
					to_insert->right = current;
					current = to_insert;
					return current
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
						if (temp != currrent->right)
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
			


	};
}

#endif

