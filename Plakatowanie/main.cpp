#include "Classes.h"
#include <iostream>

int main()
{
	vector<int> h{ 2, 4, 3, 4, 2, 3, 3, 2};
	Street s(8, h);
	std::cout << countPosters(s);
}