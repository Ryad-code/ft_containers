#include <iomanip>
#include <iostream>
#include <string>
#include "../Utils/Pair.hpp"
#include "Map.hpp"

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
	//Insertion d'elements de la map
	map1.insert_root_node(p2, NULL);
	map1.insert_root_node(p6, NULL);
	map1.insert_root_node(p1, NULL);
	map1.insert_root_node(p4, NULL);
	map1.insert_root_node(p8, NULL);
	map1.insert_root_node(p5, NULL);
	map1.insert_root_node(p7, NULL);
	map1.insert_root_node(p3, NULL);

	//Display
//	map1.display_tree(map1._root);

	std::cout << map1.get_depth(map1._root, 0) << std::endl;
	std::cout << "\n";
	std::cout << map1.get_depth(map1._root->right, 0) << std::endl;
	std::cout << "\n";
	std::cout << map1.get_depth(map1._root->left, 0) << std::endl;

	//Suppression de tout les elements
//	map1.clear_nodes(map1._root);

//	map1.display_tree(map1._root);

	return 0;
}
