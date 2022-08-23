#include <iostream>
#include "../../Utils/Pair.hpp"

namespace ft
{
template <typename V>
struct Node {
	V	value;
	Node	*left;
	Node	*right;
	int	height;
	Node(V v, Node* l = NULL, Node* r = NULL, int h = 0): value(v), left(l), right(r), height(h) {}
};

////////////////////////////////////////////////////////////////////////CLASS MAP
template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:
//.....................................................................TYPE DEFINITION
		typedef Key								key_type;
		typedef T								mapped_type;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef Compare								key_compare;
		typedef Node<value_type>						node_type;
		typedef Alloc								allocator_type;
		typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
		typedef typename allocator_type::size_type				size_type;
//.....................................................................PRIVATE VARIABLE
//	private:-------------->A DECOMMENTER
		node_type*		_root;
		node_allocator		_alloc;
		key_compare		_key_compare;
		size_type		_size;
//.....................................................................CONSTRUCT & DESTRUCT	
		explicit        map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
                        _alloc(alloc),
                        _key_compare(comp),
                        _size(0),
                        _root(NULL) {}
                //Range constructor
                //Copy constructor
                //Operator= 
                //Destructor
//.....................................................................TREE FUNCTIONS
		int		height(node_type* current)
		{
			if (current == NULL)
				return 0;
			return current->height;
		}

		int max(int a, int b)
		{
			return (a > b) ? a : b;
		}

		node_type*	create_node(const value_type& val)
		{
		       	new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type(val, NULL, NULL, 0));
			new_node->value = val;
			new_node->left = NULL;
			_size++;
			return new_node;
		}

		// Rotate right
		node_type* rightRotate(node_type* y)
		{
			node_type* x = y->left;
			node_type* T2 = x->right;
			x->right = y;
			y->left = T2;
			y->height = max(height(y->left), height(y->right)) + 1;
			x->height = max(height(x->left), height(x->right)) + 1;
			return x;
		}

		// Rotate left
		node_type* leftRotate(node_type* x)
		{
			node_type* y = x->right;
			node_type* T2 = y->left;
			y->left = x;
			x->right = T2;
			x->height = max(height(x->left), height(x->right)) + 1;
			y->height = max(height(y->left), height(y->right)) + 1;
			return y;
		}

		// Get the balance factor of each node
		int getBalanceFactor(node_type* current)
		{
			if (current == NULL)
				return 0;
			return (height(current->left)) - (height(current->right));
		}

		node_type* insert_node(const value_type& value, node_type* current)
		{
//......................Find the correct postion and insert the node
			if (current == NULL)
				return (create_node(value));
			if (value.first < current->value.first)
				current->left = insert_node(value, current->left);
			else if (value.first > current->value.first)
				current->right = insert_node(value, current->right);
			else
				return current;
//......................Update the balance factor of each node and balance the tree
			current->height = 1 + max(height(current->left), height(current->right));
			int balanceFactor = getBalanceFactor(current);
			if (balanceFactor > 1)
			{
				if (value.first < current->left->value.first)
				{
					return rightRotate(current);
				}
				else if (value.first > current->left->value.first)
				{
					current->left = leftRotate(current->left);
					return rightRotate(current);
				}
			}
			if (balanceFactor < -1)
			{
				if (value.first > current->right->value.first)
				{
					return leftRotate(current);
				}
				else if (value.first < current->right->value.first)
				{
					current->right = rightRotate(current->right);
					return leftRotate(current);
				}
			}
			return current;
		}
//....................................................................DISPLAY TREE
		void		display(node_type* root)
		{
			if (root->left)
				display(root->left);
			if (root)
				std::cout << root->value.first << "::" << root->value.second << std::endl;
			if (root->right)
				display(root->right);
		}

		void printTree(node_type* root, std::string indent, bool last)
		{
			if (root != nullptr)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "   ";
				}
				else
				{
					std::cout << "L----";
					indent += "|  ";
				}
				std::cout << root->value.first << "::" << root->value.second << std::endl;
				printTree(root->left, indent, false);
				printTree(root->right, indent, true);
			}
		}


};//end of Map class
} //end of namespace
