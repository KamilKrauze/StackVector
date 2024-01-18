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
		x = std::move(other.x);
		y = std::move(other.y);
		z = std::move(other.z);
		return *this;
	}
};

template<typename T>
void print(const stack_vector<T>& vec) {
	std::cout << "Size: " << vec.size() << "\n";
	std::cout << "Capacity: " << vec.capacity() << "\n";


	for (auto& v : vec) {
		std::cout << v << std::endl;
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

	stack_vector<float3> foo;
	foo.assign(3, float3(100));
	print(foo);
	
}
