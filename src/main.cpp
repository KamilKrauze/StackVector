#include<iostream>
#include <string>

#include "stack_vector.hpp"

int main() {
	stack_vector<short> foo{ 1,2,3,4,5,6,7,8,9,10 };
	std::cout << foo.front() << " " << foo.back() << "\n";

	return 0;
}
