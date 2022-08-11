#ifndef NODE_HPP
#define NODE_HPP

#include "Pair.hpp"

namespace ft
{
	template <class T1, class T2>
	struct Node
	{
		Node			*parent;
		Node			*right;
		Node			*left;
		ft::pair<T1, T2>	value;
//.................................................................................Constructors
		explicit Node(void) : parent(NULL), left(NULL), right(NULL), value()
		{
		}

		explicit Node(const ft::pair<T1, T2> &data): parent(NULL), left(NULL), right(NULL), value(data)
		{
		}

		Node(const Node &x) : parent(x.parent), left(x.left), right(x.right), value(x.value)
		{
		}

		~Node(void)
		{
		}
//.................................................................................
		Node&		operator=(const Node &obj)
		{
			if (*this != obj)
			{
				parent = obj.parent;
				left = obj.left;
				right = obj.right;
				value = obj.value;
			}
			return *this;
		}



		
	};
}

#endif
