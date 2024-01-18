#include <iostream>
#include <string>
#include <vector>

#include "stack_vector.hpp"

struct float3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float3() {}
	float3(float scalar) : x(scalar), y(scalar), z(scalar) {}
	float3(float x, float y, float z) : x(x), y(y), z(z) {}

	float3(const float3& other) : x(other.x), y(other.y), z(other.z) {
		std::cout << "Copy\n";
	}

	float3 (float3&& other) noexcept : x(other.x), y(other.y), z(other.z) {
		std::cout << "Move\n";
	}

	~float3() { std::cout << "Destroyed\n"; }

	float3& operator=(float3& other) {
		std::cout << "Copy on =\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	float3& operator=(float3&& other) {
		std::cout << "Move on =\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

template<typename T>
void print(const stack_vector<T>& vec) {
	std::cout << "Size: " << vec.size() << "\n";
	std::cout << "Capacity: " << vec.capacity() << "\n";


	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
	std::cout << "------------------------------" << std::endl;
}

void print(const stack_vector<float3>& vec) {
	std::cout << "Size: " << vec.size() << "\n";
	std::cout << "Capacity: " << vec.capacity() << "\n";

	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i].x << ", " << vec[i].y << ", " << vec[i].z << std::endl;
	}
	std::cout << "------------------------------" << std::endl;
}

int main() {

	//stack_vector<float3> foo;
	//foo.push_back(float3(1));
	//foo.push_back(float3( 1,2,3 ));
	//foo.emplace_back(float3(4.1f, 5.3f, 6.1f));
	//print(foo);

	//stack_vector<float3> bar;
	//for (int i = 1; i < 3; i++) bar.push_back(float3((float)i));
	//print(bar);
	//
	//bar.swap(foo);
	//print(foo);

	//stack_vector<bool> a = { true, false, true };
	//a.flip();
	//print(a);

	//stack_vector<bool> b = { false, false, true };
	//b.flip();
	//print(b);

	//a.swap(b);
	//print(b);


	stack_vector<int> glee = { 0,1,2,3,4,5,6,7,8,9 };
	auto it = glee.begin().m_ptr;

	glee.emplace(glee.begin() + 1, 100);
	glee.emplace(glee.begin() + 4, 100);
	glee.emplace(glee.begin()+9, 100);
	print(glee);

	std::cin.get();

	return 0;
}
