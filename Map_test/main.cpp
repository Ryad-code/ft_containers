#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "../Utils/Pair.hpp"
#include "Node.hpp"

int main()
{
	//On declare la racine de l'arbre
        node<ft::pair<int, std::string> > *start = NULL;

	//On declare des ft::pair
	ft::pair<int, std::string> obj1 = ft::make_pair(1, "un");
	ft::pair<int, std::string> obj2 = ft::make_pair(2, "deux");
	ft::pair<int, std::string> obj3;

	//On stock les ft::pair dans des nodes que l'on cree
	add(&start, obj1);
	add(&start, obj2);
	add(&start, obj3 = ft::make_pair(3, "trois"));

	//Display
	display(start);
	std::cout << "\n";

//	node<ft::pair<int, std::string> > *obj = search(start, obj3);
//	n_delete(&start, obj);
	print(start, "");	

//	display(start);

	delete(start);

	return 0;
}


