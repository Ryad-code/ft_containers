#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <list>
#include <vector>
#include <deque>

template<typename T>
void	printStack(std::stack<T> s) 
{
    while (!s.empty()) {
	    std::cout << s.top() << "; ";
        s.pop();
    }
    std::cout << std::endl;
}

int main()
{
	std::stack<int> obj;

	obj.push(10);
	obj.push(20);
	obj.push(30);
	obj.push(40);
	obj.push(50);

//	std::stack<int> obj1 = obj;
//	std::cout << obj.top() << std::endl;
//	std::cout << obj.back() << std::endl;
//	std::cout << obj1.top() << std::endl;

	printStack(obj);
	std::cout << obj.size() << std::endl;
	std::cout << obj.top() << std::endl;

	return 0;
}
