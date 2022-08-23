#include <iostream>
#include <iomanip>
#include <string>

#include "AVL_tree.cpp"
#include "../../Utils/Pair.hpp"

int main()
{
	const ft::pair<int, std::string> p1 = ft::make_pair(1, "un");
	const ft::pair<int, std::string> p2 = ft::make_pair(2, "deux");
	const ft::pair<int, std::string> p3 = ft::make_pair(3, "trois");
	const ft::pair<int, std::string> p4 = ft::make_pair(4, "quatre");
	const ft::pair<int, std::string> p5 = ft::make_pair(5, "cinq");
	const ft::pair<int, std::string> p6 = ft::make_pair(6, "six");
	const ft::pair<int, std::string> p7 = ft::make_pair(7, "sept");
	const ft::pair<int, std::string> p8 = ft::make_pair(8, "huit");
	const ft::pair<int, std::string> p9 = ft::make_pair(9, "neuf");
	
	ft::map<int, std::string> Map;

	Map._root = Map.insert_node(p1, Map._root);
	Map._root = Map.insert_node(p2, Map._root);
	Map._root = Map.insert_node(p3, Map._root);
	Map._root = Map.insert_node(p4, Map._root);
	Map._root = Map.insert_node(p5, Map._root);
	Map._root = Map.insert_node(p6, Map._root);
	Map._root = Map.insert_node(p7, Map._root);
	Map._root = Map.insert_node(p8, Map._root);
	Map._root = Map.insert_node(p9, Map._root);

	Map.display(Map._root);

	Map.deleteNode(Map._root, 6);

	Map.display(Map._root);
//	Map.printTree(Map._root, "", true);

	return 0;
}

