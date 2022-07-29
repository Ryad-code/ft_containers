#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

template <class T>
class MyClass
{
	private:
		T	_value;
	
	public:
		MyClass(void) {};
		MyClass(const T& val): _value(val) {};
		MyClass(const MyClass& obj): _value(obj._value) {};
		~MyClass(void) {};

		T&	getValue(void)
		{
			return _value;
		};

};

int main()
{
	MyClass<int> obj;
	MyClass<int> obj1(25);

	std::cout << obj1.getValue() << std::endl;

	return 0;
}

