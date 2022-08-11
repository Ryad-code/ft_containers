#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "utils.cpp"

int main()
{
	node *start = NULL;

	add(&start, 10);
	add(&start, 9);
	add(&start, 5);
	add(&start, 100);
	add(&start, 90);
	add(&start, 50);

	display(start);

	node *obj = search(start, 50);

	n_delete(&start, obj);

	display(start);

	delete(start);
	return 0;
}


