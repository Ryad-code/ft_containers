#include <iomanip>
#include <iostream>
#include <string>
#include "../Utils/Pair.hpp"
#
#include "Node1.hpp"

int main()
{
	//Declaration de ft::pair<int, std::string>
	const ft::pair<int, std::string> p1 = ft::make_pair(1, "un");
	const ft::pair<int, std::string> p2 = ft::make_pair(2, "deux");
	const ft::pair<int, std::string> p3 = ft::make_pair(3, "trois");
	const ft::pair<int, std::string> p4 = ft::make_pair(4, "quatre");
	const ft::pair<int, std::string> p5 = ft::make_pair(5, "cinq");
	const ft::pair<int, std::string> p6 = ft::make_pair(6, "six");
	const ft::pair<int, std::string> p7 = ft::make_pair(7, "sept");
	const ft::pair<int, std::string> p8 = ft::make_pair(8, "huit");

	//Declaration de ft::map
	ft::map<int, std::string> map1;

	map1.insert_root_node(p8, NULL);
	map1.insert_root_node(p6, NULL);
	map1.insert_root_node(p1, NULL);
	map1.insert_root_node(p4, NULL);
	map1.insert_root_node(p2, NULL);
	map1.insert_root_node(p5, NULL);
	map1.insert_root_node(p7, NULL);
	map1.insert_root_node(p3, NULL);


	map1.display_tree(map1._root);

	map1.clear_nodes(map1._root);

	map1.display_tree(map1._root);

//	std::cout << map1._root->value.first << std::endl;
//	std::cout << map1._root->right->value.first << std::endl;
//	std::cout << map1._root->left->value.first << std::endl;
//	std::cout << map1._root->right->right->value.first << std::endl;

	return 0;
}
