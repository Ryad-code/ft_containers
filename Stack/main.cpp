#include <iostream>
#include <iomanip>
#include <stack>
#include <list>
#include "Stack.hpp"

int main()
{
	ft::Stack<int> obj;
	
	std::cout << obj.empty() << std::endl;
	std::cout << obj.size() << std::endl << std::endl;

	obj.push(25);
	obj.push(35);
	obj.push(45);
	obj.push(55);
	obj.push(65);
	
	std::cout << obj.empty() << std::endl;
	std::cout << obj.size() << std::endl;

	std::cout << obj.top() << std::endl;

	return 0;
}
