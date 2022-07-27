#include <iostream>
#include <iomanip>
#include <string>
#include "Vector.hpp"

int main()
{
	ft::vector<int> vec(3, 10);
//	std::vector<int> vec1(3, 10);

	vec.push_back(25);
//	vec1.insert(vec1.begin(), 250);
	std::cout << vec.front() << std::endl;
	std::cout << vec.back() << std::endl;
	vec.push_back(250);
	std::cout << vec.back() << std::endl;

	vec.pop_back();
	std::cout << vec.back() << std::endl;

/*	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "capacity = " << vec.capacity() << std::endl;
	vec.reserve(10);
	std::cout << "new size = " << vec.size() << std::endl;
	std::cout << "new capacity = " << vec.capacity() << std::endl;
*/
/*	std::allocator<int> alloc;		//Allocator for int values
	int	*array = alloc.allocate(5);	//Allocate memory for 5 ints
	alloc.construct(array, 100);		//Construct array[0]
	alloc.construct(array + 1, 100);	//Construct array[1]
	array[3] = 10;
	std::cout << array[0] << std::endl;
	std::cout << array[1] << std::endl;
	std::cout << array[2] << std::endl;
	std::cout << array[3] << std::endl;
	std::cout << array[4] << std::endl;
	alloc.deallocate(array, 5);		//Deallocate memory for 5 ints
*/

	return (0);
}
