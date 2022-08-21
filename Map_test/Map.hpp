#ifndef NODE1_HPP
#define NODE1_HPP

namespace ft
{
/////////////////////////////////////////////////////////////////////////TREE_NODE
template <typename V>
struct node
{
	V value;
	node *left;
	node *right;
	node *parent;
//	bool last;
	node(V v, node *l, node *r, node *p, bool e = false) : value(v), left(l), right(r), parent(p)/*, last(e)*/ {}
	~node() {}
};

////////////////////////////////////////////////////////////////////////CLASS MAP
template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:
//......................................................................TYPE_DEFINITION
		typedef	Key								key_type;
		typedef	T								mapped_type;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef Compare								key_compare;
		typedef	node<value_type>						node_type;
		typedef	Alloc								allocator_type;
		typedef	typename allocator_type::template rebind<node_type>::other	node_allocator;
		typedef typename allocator_type::size_type				size_type;
//......................................................................PRIVATE VARIABLES
//	private:...........A DECOMMENTER!!!
		node_type	*_root;
		node_allocator	_alloc;
		key_compare	_key_compare;
		size_type	_size;
//......................................................................CONSTRUCT & DESTRUCT
	public:
		explicit	map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_key_compare(comp),
			_size(0),
			_root(NULL) {}
		//.......Range & Copy constructor still missing
		//.......Operator= & destructor also missing
		
//......................................................................TREE_FUNCTIONS
		node_type*	new_node(const value_type& val, node_type *parent)
		{
			node_type *temp = _alloc.allocate(1);
			_alloc.construct(temp, node_type(val, NULL, NULL, parent/*, false*/));
			_size++;
			return temp;
		}

		node_type*	min_node(node_type* current)
		{
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

		node_type*	insert_root_node(const value_type& val, node_type* parent = NULL)
		{
			if (_root == NULL)
			{
				_root = new_node(val, NULL);
				return _root;
			}
			else
				return insert_node(val, _root, parent);
		}

		node_type*	insert_node(const value_type& val, node_type* current, node_type* parent)
		{
			if (current == NULL)
			{
				current = new_node(val, parent);
				current->parent = parent;
			}
			if (val.first < current->value.first)
				current->left = insert_node(val, current->left, current);
			else if (val.first > current->value.first)
				current->right = insert_node(val, current->right, current);
			return current;
		}

		void		clear_nodes(node_type* current)
		{
			if (current)
			{
				clear_nodes(current->left);
				clear_nodes(current->right);
				_alloc.destroy(current);
				_alloc.deallocate(current, 1);
				if (_size > 0)
					_size--;
				if (current == _root)
					_root = NULL;
			}
		}
//................................TREE_DISPLAY................................//
		void		display_tree(node_type* start)
		{
			if (start == NULL)
				std::cout << "Empty tree" << std::endl;
			else
				display(start);
		}

		void		display(node_type* start)
		{
			if (start->left)
				display(start->left);
			if (start->value.first)
				std::cout << start->value.first << "::" << start->value.second << std::endl;
			if (start->right)
				display(start->right);
		}
};

}
#endif
