#include<iostream>
#include <string>

#include "stack_vector.h"

int main() {
	stack_vector<short> foo;
	size_t counter = 0;
	while (bool run = true) {
		foo.push_back(counter);
		counter++;
		printf("%d\n", counter);
	}

	return 0;
}