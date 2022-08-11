#include "Node.hpp"
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
	ft::pair<int, std::string> pair1;
	ft::pair<int, std::string> pair2;

	pair1 = ft::make_pair(5, "cinq");
	pair2 = ft::make_pair(6, "six");
	
	ft::Node<int, std::string> root1;
	ft::Node<int, std::string> root2(pair2);

	root1.value = pair1;

	std::cout << root2.value.first << std::endl; 
	std::cout << root2.value.second << std::endl; 

	return 0;
}

