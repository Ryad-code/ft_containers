#include <iostream>
#include <iomanip>
#include <stack>
#include <list>
#include "Stack.hpp"

int main()
{
	ft::stack<int> obj;
	
	obj.push(25);
	obj.push(35);
	obj.push(45);
	obj.push(55);
	obj.push(65);

	ft::stack<int> obj1 = obj;
	obj1.push (100);
//	std::cout << obj.empty() << std::endl;
//	std::cout << obj.size() << std::endl;

	obj1.swap(obj);
	std::cout << obj.top() << std::endl;
	std::cout << obj1.top() << std::endl;

	if (obj == obj1)
		std::cout << "oui" << std::endl;
	else
		std::cout << "non" << std::endl;

	return 0;
}
