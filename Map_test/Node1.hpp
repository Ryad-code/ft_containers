#ifndef NODE1_HPP
#define NODE1_HPP

template <typename V>
struct node
{
	V value;
	node *left;
	node *right;
	node *parent;
	bool last;
	node(V v, node *l, node *r, node *p, bool e = false) : value(v), left(l), right(r), parent(p), last(e) {}
	~node() {}
};

template <typename Key, typename T, typename Alloc = std::allocator<ft::pair<const Key, T> >
class map
{
	public:
//......................................................................TYPE_DEFINITION
		typedef	Key						key_type;
		typedef	T						mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef	node<value_type>				node_type;
		typedef	Alloc						allocator_type;
//......................................................................

		template <typename V>
		node<V>* new_node(const V& val, node<V> *parent)
		{
			node<V> *temp = Alloc::allocate(1);
			Alloc::construct(temp, node<V>(val, NULL, NULL, parent, false));
//			_size++;
			return temp;
		}
};
/*
node_type* min_value_node(node_type *node)
{
	node_type *current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

node_type* max_value_node(node_type *node)
{
	node_type *current = node;
	while (current->right != NULL)
		current = current->right;
	return current;
}

node_type* insert_node_check_root(const value_type& val, node_type *current, node_type *parent = NULL)
{
	if (!_root)
	{
		_root = new_node(val, NULL);
		node_type *last = new_node(value_type(key_type(), mapped_type()), _root);
		_size--;
		_root->right = last;
		last->last = true;
		return _root;
	}
	if (_root->last)
	{
		node_type *new_root = new_node(val, NULL);
		_root->parent = new_root;
		new_root->right = _root;
		_root = new_root;
		return _root;
	}
	return insert_node(val, current, parent);
}

node_type* insert_node(const value_type& val, node_type *current, node_type *parent)
{
	if (!current)
		return new_node(val, parent);
	if (current->last)
	{
		node_type *to_insert = new_node(val, parent);
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
*/
#endif
