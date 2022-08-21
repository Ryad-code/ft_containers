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
		//Range constructor
		//Copy constructor
		//Operator= 
		//Destructor
		
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

		bool		key_exist(const key_type& key, node_type* start)
		{
			bool res = false;
			if (start == NULL)
				return false;
			if (key == start->value.first)
				return true;
			if (start->left)
				 res = key_exist(key, start->left);
			if (start->right && !res)
				res = key_exist(key, start->right);
			return res;
		}

		node_type*	search_key(const key_type& key, node_type* current)
		{
			if (current == NULL)
				return current;
			if (_key_compare(key, current->value.first))
				return find_key(key, current->left);
			else if (_key_compare(current->value.first, key))
				return find_key(key, current->right);
			return current;
		}

		node_type*	find_key(const key_type& key, node_type* current)
		{
			if (key_exist(key, current) == false)
				return NULL;
			return search_key(key, current);
		}
		
		int		get_depth(node_type* current, int res)
		{
			if (current->right)
				return res = get_depth(current->right, res + 1);
			if (current->left)
				return res = get_depth(current->left, res + 1);
			return res;
		}
//.........................................................................DELETING_NODES		
		node_type*	delete_node(const key_type key, node_type* current)
		{	
			//Si la cle n'existe pas
			if (!current || key_exist(key, _root) == false)
				return NULL;
			//Initialisation de current = element a supprimer
			current = find_key(key, current);
			//Si l'element a supprimer est la racine--->Utile ? 
			if (key == _root->value.first)
			{
				//Deleting _root
				//return new_root
			}
			//Si l'element a supprimer est une feuille
			else if (!current->left && !current->right)
			{
				current->parent = NULL;
				_alloc.destroy(current);
				_alloc.deallocate(current, 1);
				current = NULL;
				_size--;
			}
			//Si l'element a supprimer n'est ni la racine ni une feuille
			else
			{	
				//Si l'element a supprimer a un seul enfant
				if (!current->right || !current->left)
				{
					//Si l'enfant est a droite
					if (current->right)
					{
						if (_key_compare(current->parent->value.first), key)
							current->parent->right = current->right;
						else if (key, _key_compare(current->parent->value.first))
							current->parent->left = current->right;
						current->right->parent = current->parent;
					}
					//Si l'enfant est a gauche
					else if (current->left)
					{
						if (_key_compare(current->parent->value.first), key)
							current->parent->right = current->left;
						else if (key, _key_compare(current->parent->value.first))
							current->parent->right = current->left;
						current->left->parent = current->parent;
					}
					_alloc.destroy(current);
					_alloc.deallocate(current, 1);
					current = NULL;
					_size--;
				}
				//Si l'element a supprimer a deux enfant
				else if (current->right && current->left)
				{
					node_type* temp;
					if (_key_compare(current->parent->value.first), key)
					{

					}
				}
			}
			return NULL;
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
