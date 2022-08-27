#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"

#include <map>
#include <iostream>
#include <iomanip>
#include <string>

std::map<int, std::string> Map;
std::map<int, std::string>::iterator it = Map.end();

ft::map<int, std::string> Map1;
ft::map<int, std::string>::iterator it1 = Map1.end();

void	ft_find1(int n, typename ft::map<int, std::string> map)
{
	ft::map<int, std::string>::iterator ret = map.find(n);

	if (ret != it1)
		std::cout << "oui\n";
	else
		std::cout << "map::find(" << n << ") returned end()" << std::endl;
}

void    ft_find(int n, typename std::map<int, std::string> map)
{
        std::map<int, std::string>::iterator ret = map.find(n);

        if (ret != it)
                std::cout << "oui\n";
        else
                std::cout << "map::find(" << n << ") returned end()" << std::endl;
}

int main()
{
//	ft::map<int, std::string> Map;
//	std::map<int, std::string> Map1;

	Map[42] = "fgzgxfn";
        Map[25] = "funny";
        Map[80] = "hey";
        Map[12] = "no";
        Map[27] = "bee";
        Map[90] = "8";

	Map1[42] = "fgzgxfn";
        Map1[25] = "funny";
        Map1[80] = "hey";
        Map1[12] = "no";
        Map1[27] = "bee";
        Map1[90] = "8";

	ft_find(3, Map);
	ft_find(35, Map);
	ft_find(100, Map);

	
	ft_find1(3, Map1);
	ft_find1(35, Map1);
	ft_find1(100, Map1);

	return 0;
}
