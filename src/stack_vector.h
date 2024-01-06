#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include <initializer_list>
#include <optional>

// Dynamic stack allocated vector
template<typename T>
class stack_vector
{
/* Macros */
#define __DYN_STACK_ALLOC(Size) static_cast<T*>(_malloca(Size * sizeof(T)))

	/* Allocation / Deallocation */
public:
	stack_vector();
	stack_vector(size_t size);
	stack_vector(std::initializer_list<T> init_list);

	~stack_vector();

	/* Functions */
public:
	void push_back(T value);
	T pop_back();
	void append(stack_vector<T>& vec);

	T front();
	T back();
	T at(size_t index) const;
	
	size_t size() const { return m_size; }
	size_t capacity() const { return m_capacity; }

	// Total memory allocated of the whole object.
	size_t total_capacity() const { return (sizeof(m_size) + sizeof(m_capacity) + m_capacity); }

	void clear();
	void resize(size_t size);

	bool is_empty() const;

/* Operator overloads */
public:
	stack_vector<T>& operator= (const stack_vector<T>& rhs);
	T& operator[] (size_t index) { return m_values[index]; }
	
	/* Relational */
	bool operator== (const stack_vector<T> rhs);
	bool operator!= (const stack_vector<T> rhs);
	bool operator<  (const stack_vector<T> rhs);
	bool operator<= (const stack_vector<T> rhs);
	bool operator>  (const stack_vector<T> rhs);
	bool operator>= (const stack_vector<T> rhs);

/* Members */
private:
	T* m_values; // Points to an array of values. Will be stack allocated, so no manual deletion needed.
	size_t m_size; // Size of stack vector.
	size_t m_capacity; // Total memory allocated by m_values.

}; // !stack_vector<T> class


// Allocate array on stack.
template<typename T>
inline stack_vector<T>::stack_vector()
{	
	// Point to stack array.
	m_values = nullptr;
	m_size = 0;
}

// Allocate array on stack with size.
template<typename T>
inline stack_vector<T>::stack_vector(size_t size)
{
	// Point to stack array.
	m_values = __DYN_STACK_ALLOC(m_size-1);
	m_size = size;
}

template<typename T>
inline stack_vector<T>::stack_vector(std::initializer_list<T> init_list) : m_size(init_list.size()) {
	m_values = __DYN_STACK_ALLOC(init_list.size());
	std::copy(init_list.begin(), init_list.end(), m_values);
}

template<typename T>
inline stack_vector<T>::~stack_vector()
{
	m_size = NULL;
}

// Add new value to the end of the array.
template<typename T>
inline void stack_vector<T>::push_back(T value)
{
	size_t newsize = m_size + 1;

	T* temp_vals = new T[newsize];
	for (size_t i = 0; i < newsize - 1; i++) {
		temp_vals[i] = m_values[i];
	}
	temp_vals[newsize - 1] = value; // Add new value to the end

	// Create new stack array
	this->m_values = __DYN_STACK_ALLOC(newsize);
	
	// Re-calculate size and memory allocation size.
	this->m_size = newsize;
	this->m_capacity = sizeof(T) * this->m_size;

	// Copy values over
	// Avoids from pointing to heap allocated memory.
	for (size_t i = 0; i < newsize; i++) {
		m_values[i] = temp_vals[i];
	}
	delete temp_vals;
}

// Get and remove last value from vector.
template<typename T>
inline T stack_vector<T>::pop_back()
{
	if (m_size <= 0) { 
		throw std::out_of_range("stack_vector is empty!"); 
		return NULL;
	}
	
	// Copy last value.
	T val = m_values[m_size - 1];

	// Copy all values but last 
	T* new_values = new T[m_size-1];
	for (size_t i = 0; i < m_size-1; i++) {
		new_values[i] = m_values[i];
	}

	for (size_t i = 0; i < m_size - 1; i++) {
		m_values[i] = new_values[i];
	}
	delete new_values;

	m_size--;

	return val;
}

// Appends values from passed in vector to the end of this vector.
template<typename T>
inline void stack_vector<T>::append(stack_vector<T>& vec)
{	
	const size_t vec_size = vec.size();
	const size_t newsize = m_size + vec_size;
	T* temp = __DYN_STACK_ALLOC(newsize);

	for (size_t i = 0; i < this->m_size; i++)
	{
		temp[i] = m_values[i];	
	}

	for (size_t i = 0; i < vec_size; i++)
	{
		temp[this->m_size + i] = vec[i];
	}

	this->m_values = __DYN_STACK_ALLOC(newsize);
	std::copy(temp, temp + newsize, m_values);

	m_size = newsize;
	m_capacity = sizeof(T) * m_size;
}

// Get copy of first value.
template<typename T>
inline T stack_vector<T>::front()
{
	return m_values[0];
}

// Get copy of last value.
template<typename T>
inline T stack_vector<T>::back()
{
	return m_values[m_size-1];
}

// Get copy of value at this position.
template<typename T>
inline T stack_vector<T>::at(size_t index) const
{
	return m_values[index];
}

template<typename T>
inline void stack_vector<T>::clear()
{
	this->m_size = 0;
	this->m_values = __DYN_STACK_ALLOC(this->m_size);
}

template<typename T>
inline void stack_vector<T>::resize(size_t size)
{
	std::cout << size << "\n";

	// Copy values to temporary variable
	T* temp_vals = __DYN_STACK_ALLOC(m_size);
	for (size_t i = 0; i < m_size; i++)
	{
		temp_vals[i] = m_values[i];
	}

	// Reconstruct stack array
	m_values = __DYN_STACK_ALLOC(size);
	std::cout << sizeof(m_values) << "\n";
	for (size_t i = 0; i < m_size; i++)
	{
		m_values[i] = temp_vals[i];
	}

	this->m_size = size;
	this->m_capacity = sizeof(T) * size;

	_freea(temp_vals);
}

	// Is the array empty?
template<typename T>
inline bool stack_vector<T>::is_empty() const
{
	return (this->m_values == nullptr);
}

/*------------------------------------------*/
/* Operator overloads						*/
/*------------------------------------------*/


template<typename T>
inline stack_vector<T>& stack_vector<T>::operator=(const stack_vector<T>& rhs)
{
	// Resize array
	this->m_values = __DYN_STACK_ALLOC(rhs.m_size);
	this->m_size = rhs.m_size;
	this->m_capacity = (sizeof(T) * this->m_size);

	// Move values over
	for (size_t i = 0; i < this->m_size; i++)
	{
		this->m_values[i] = rhs.m_values[i];
	}

	return *this;
}

template<typename T>
inline bool stack_vector<T>::operator== (const stack_vector<T> rhs)
{
	bool same_size = (this->m_size == rhs.m_size); // Check if both vectors are of the same size.
	bool elem_check = false;

	for (size_t i = 0; i < this->m_size; i++)
	{
		elem_check = (this->m_values[i] == rhs.m_values[i]);
	}

	return (same_size && elem_check);
}

template<typename T>
inline bool stack_vector<T>::operator!=(const stack_vector<T> rhs)
{
	bool same_size = (this->m_size != rhs.m_size); // Check if both vectors are not of the same size.
	bool elem_check = false;

	for (size_t i = 0; i < this->m_size; i++)
	{
		elem_check = (this->m_values[i] != rhs.m_values[i]);
	}

	return (same_size || elem_check);
}

template<typename T>
inline bool stack_vector<T>::operator<(const stack_vector<T> rhs)
{
	bool same_size = (this->m_size < rhs.m_size); // Check if right vector is larger.
	bool elem_check = false;

	for (size_t i = 0; i < this->m_size; i++)
	{
		elem_check = (this->m_values[i] < rhs.m_values[i]);
	}

	return (same_size || elem_check);
}

template<typename T>
inline bool stack_vector<T>::operator<=(const stack_vector<T> rhs)
{
	bool same_size = (this->m_size <= rhs.m_size); // Check if right vector is larger or equal.
	bool elem_check = false;

	for (size_t i = 0; i < this->m_size; i++)
	{
		elem_check = (this->m_values[i] <= rhs.m_values[i]);
	}

	return (same_size && elem_check);
}

template<typename T>
inline bool stack_vector<T>::operator>(const stack_vector<T> rhs)
{
	bool same_size = (this->m_size > rhs.m_size); // Check if right vector is smaller.
	bool elem_check = false;

	for (size_t i = 0; i < this->m_size; i++)
	{
		elem_check = (this->m_values[i] > rhs.m_values[i]);
	}

	return (same_size || elem_check);
}

template<typename T>
inline bool stack_vector<T>::operator>=(const stack_vector<T> rhs)
{
	bool same_size = (this->m_size >= rhs.m_size); // Check if right vector is smaller or equal.
	bool elem_check = false;

	for (size_t i = 0; i < this->m_size; i++)
	{
		elem_check = (this->m_values[i] >= rhs.m_values[i]);
	}

	return (same_size && elem_check);
}

#endif