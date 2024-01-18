#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include <initializer_list>
#include <cassert>

// Constant iterator
template<typename stack_vector>
class const_iterator {
public:
	using ValueType = typename stack_vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	inline const_iterator() noexcept : m_ptr() {}
	inline const_iterator(PointerType ptr) noexcept : m_ptr(ptr) { }

	_NODISCARD inline ReferenceType operator[](const size_t index) const noexcept { return *(m_ptr[index]); }
	_NODISCARD inline PointerType operator->() const noexcept { return m_ptr; }
	_NODISCARD inline ReferenceType operator*() const noexcept { return *m_ptr; }

	/* Increment / Decrement */

	inline const_iterator& operator++() noexcept
	{
		m_ptr++;
		return *this;
	}
	inline const_iterator operator++(int) noexcept
	{
		const_iterator temp = *this;
		++(*this);
		return temp;
	}
	inline const_iterator& operator--() noexcept
	{
		m_ptr--;
		return *this;
	}
	inline const_iterator operator--(int) noexcept
	{
		const_iterator temp = *this;
		--(*this);
		return temp;
	}

	/* Addition / Subtraction */

	inline const_iterator& operator+=(const size_t val) noexcept
	{
		m_ptr += val;
		return *this;
	}

	_NODISCARD inline const_iterator operator+(const size_t val) const noexcept {
		const_iterator temp = *this;
		temp += val;
		return temp;
	}

	inline const_iterator& operator-=(const size_t val) noexcept
	{
		m_ptr -= val;
		return *this;
	}

	_NODISCARD inline const_iterator operator-(const size_t val) const noexcept {
		const_iterator temp = *this;
		temp -= val;
		return temp;
	}

	/* RELATIONAL OPERATORS */

	bool operator==(const const_iterator& other) const noexcept
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const const_iterator& other) const noexcept
	{
		return !(*this == other);
	}

	bool operator>=(const const_iterator& other) const noexcept
	{
		return m_ptr >= other.m_ptr;
	}

	bool operator<=(const const_iterator& other) const noexcept
	{
		return m_ptr <= other.m_ptr;
	}

	bool operator>(const const_iterator& other) const noexcept
	{
		return m_ptr > other.m_ptr;
	}

	bool operator<(const const_iterator& other) const noexcept
	{
		return m_ptr < other.m_ptr;
	}

/* Data */
public:
	PointerType m_ptr;
};

// Regular iterator
template<typename stack_vector>
class iterator : public const_iterator<stack_vector> {
public:
	using ValueType = typename stack_vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	iterator() : m_ptr() {}
	iterator(PointerType ptr) { this->m_ptr = ptr; }

	ReferenceType operator[](const size_t index) const noexcept { return *(m_ptr[index]); }
	PointerType operator->() { return m_ptr; }
	ReferenceType operator*() { return *m_ptr; }

	/* Addition / Subtraction */

	inline iterator& operator++() noexcept
	{
		m_ptr++;
		return *this;
	}

	inline iterator operator++(int) noexcept
	{
		iterator temp = *this;
		++(*this);
		return temp;
	}

	inline iterator& operator--() noexcept
	{
		m_ptr--;
		return *this;
	}

	inline iterator operator--(int) noexcept
	{
		iterator temp = *this;
		--(*this);
		return temp;
	}

	inline iterator& operator+=(const size_t val) noexcept
	{
		m_ptr += val;
		return *this;
	}

	_NODISCARD inline iterator& operator+(const size_t val) const noexcept
	{
		iterator temp = *this;
		temp += val;
		return temp;
	}

	inline iterator& operator-=(const size_t val)
	{
		m_ptr -= val;
		return *this;
	}

	_NODISCARD inline iterator& operator-(const size_t val) const noexcept
	{
		iterator temp = *this;
		temp -= val;
		return temp;
	}

	/* RELATIONAL OPERATORS */

	bool operator==(const iterator& other) const
	{
		return m_ptr == other.m_ptr;
	}

	bool operator!=(const iterator& other) const
	{
		return !(*this == other);
	}

	bool operator>=(const iterator& other) const
	{
		return m_ptr >= other.m_ptr;
	}

	bool operator<=(const iterator& other) const
	{
		return m_ptr <= other.m_ptr;
	}

	bool operator>(const iterator& other) const
	{
		return m_ptr > other.m_ptr;
	}

	bool operator<(const iterator& other) const
	{
		return m_ptr < other.m_ptr;
	}

};

// Dynamic stack allocated vector
template<typename T>
class stack_vector
{
public:
	using ValueType = T;
	using Iterator = iterator<stack_vector<T>>;
	using ConstIterator = const_iterator<stack_vector<T>>;

	/* Allocation / Deallocation */
public:

	// Allocate array on stack.
	stack_vector()
	{
		this->_reallocate(2);
	}

	// Allocate array on stack with size.
	stack_vector(size_t size)
	{
		this->_reallocate(size);
	}

	// Allocate array on stack with a given set of values
	stack_vector(std::initializer_list<T> init_list)
	{
		this->_reallocate(init_list.size());
		std::copy(init_list.begin(), init_list.end(), m_data);
		m_size = init_list.size();
	}

	// DESTROY!
	~stack_vector()
	{
		this->clear();

		_freea(m_data);
		m_size = NULL;
		m_capacity = NULL;
	}

public:

	/*----------------------------------------------------------*/
	/*						  Modifiers						    */
	/*----------------------------------------------------------*/

	void push_back(const T& value)
	{
		if (m_size >= m_capacity)
			this->_reallocate(m_capacity + (m_capacity / 2));

		m_data[m_size] = value;
		m_size++;
	}
	
	void push_back(T&& value)
	{
		if (m_size >= m_capacity)
			this->_reallocate(m_capacity + (m_capacity / 2));

		m_data[m_size] = std::move(value);
		m_size++;
	}

	void pop_back()
	{
		if (m_size > 0) {
			m_size--;
			m_data[m_size].~T();
		}
	}

	void swap(stack_vector<T>& other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_data, other.m_data);
	}

	void swap(stack_vector<T>&& other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_data, other.m_data);
	}

	template<typename... Args>
	Iterator emplace(ConstIterator position, Args&&... args)
	{
		// Calculate the index based on the pointer difference
		auto* loc = position.m_ptr;
		size_t index = loc - m_data;

		if (m_size >= m_capacity) {
			this->_reallocate(m_capacity + (m_capacity / 2));
		}
		m_size++;

		// Shift elements to make space for the new one
		for (size_t i = m_size; i > index; --i)
			m_data[i] = std::move(m_data[i - 1]);

		m_data[index] = T(std::forward<Args>(args)...);

		return Iterator(m_data + index);
	}

	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		if (m_size >= m_capacity)
			this->_reallocate(m_capacity + (m_capacity / 2));

		new(&m_data[m_size]) T(std::forward<Args>(args)...);
		m_size++;
	}

	template <typename U = T, typename std::enable_if<std::is_same<U, bool>::value, int>::type = 0>
	void flip() noexcept
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i] = !m_data[i];  // Flip each boolean
		}
	}

	/*----------------------------------------------------------*/
	/*						Element access						*/
	/*----------------------------------------------------------*/
	// Get the first element.
	T front() const {
		assert(m_size > 0);
		return m_data[0];
	}


	// Get the last element.
	T back() const {
		assert(m_size > 0);
		return m_data[m_size - 1];
	}
	
	// Get copy of element at this index.
	T at(size_t index) const
	{
		assert((index >= 0 && index < m_capacity));
		return m_data[index];
	}

	// Get array
	T* data() noexcept
	{
		return this->m_data;
	}

	// Get array copy
	const T* data() const noexcept
	{
		return this->m_data;
	}

	/*----------------------------------------------------------*/
	/*						Iterators							*/
	/*----------------------------------------------------------*/

	Iterator begin()
	{
		return Iterator(m_data);
	}

	Iterator end()
	{
		return Iterator(m_data + (m_size));
	}

	Iterator rbegin()
	{
		return Iterator(m_data + (m_size));
	}

	Iterator rend()
	{
		return Iterator(m_data);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_data);
	}

	ConstIterator end() const
	{
		return ConstIterator(m_data + (m_size));
	}

	ConstIterator rbegin() const
	{
		return ConstIterator(m_data + (m_size));
	}

	ConstIterator rend() const
	{
		return ConstIterator(m_data);
	}

	/*----------------------------------------------------------*/
	/*						   Capacity						    */
	/*----------------------------------------------------------*/

	// Get amount of elements.
	size_t size() const { return m_size; }

	// Get amount of elements that can fit.
	size_t capacity() const { return m_capacity; }

	// Destroy vector contents
	void clear()
	{
		for (size_t i = 0; i < m_size; i++) {
			m_data[i].~T();
		}
		m_size = 0;
	}

	// Change size
	void resize(size_t size, T value = T())
	{
		_reallocate(size);
		for (size_t i = m_size; i < size; i++)
			m_data[i] = value;

		m_size = size;
	}

	void reserve(size_t new_capacity)
	{
		bool resize = false;
		(new_capacity > m_capacity) ? (m_capacity = new_capacity) : (resize = true);
		
		if (resize) {
			_reallocate(m_capacity);
		}

	}
	
	// Check if empty
	bool empty() const { return (this->m_size == 0); }

	/*----------------------------------------------------------*/
	/*						Operator Overload					*/
	/*----------------------------------------------------------*/
public:
	void* operator new(size_t size);
	void operator delete(void*);

	const T& operator[](const size_t index) const
	{
		assert((index >= 0 && index < m_capacity));
		return this->m_data[index];
	}

	T& operator[](const size_t index)
	{
		assert((index >= 0 && index < m_capacity));
		return this->m_data[index];
	}

	stack_vector<T>& operator= (const stack_vector<T>& rhs);
	stack_vector<T>& operator= (stack_vector<T>&& rhs);
	
	/* Relational */
	_NODISCARD bool operator== (const stack_vector<T> rhs);
	_NODISCARD bool operator!= (const stack_vector<T> rhs);
	_NODISCARD bool operator<  (const stack_vector<T> rhs);
	_NODISCARD bool operator<= (const stack_vector<T> rhs);
	_NODISCARD bool operator>  (const stack_vector<T> rhs);
	_NODISCARD bool operator>= (const stack_vector<T> rhs);


	/* Helper Functions */
private: 

	inline void stack_vector<T>::_reallocate(const size_t new_capacity)
	{

		T* new_data = static_cast<T*>(_alloca(new_capacity * sizeof(T)));

		if (new_capacity < m_size)
			m_size = new_capacity;

		for (size_t i = 0; i < m_size; i++)
			new (&new_data[i]) T(std::move(m_data[i]));

		for (size_t i = 0; i < m_size; i++) {
			m_data[i].~T();
		}

		m_data = new_data;
		m_capacity = new_capacity;
	}


/* Members */
protected:
	T* m_data = nullptr; // Points to an array of values.
	size_t m_size = 0; // Size of stack vector.
	size_t m_capacity = 0; // Total memory allocated by m_data.

}; // !stack_vector<T> class


/*------------------------------------------*/
/*            Operator overloads			*/
/*------------------------------------------*/
template<typename T>
inline stack_vector<T>& stack_vector<T>::operator=(const stack_vector<T>& rhs)
{
	// Resize array
	this->_reallocate(rhs.m_size);
	this->m_size = rhs.m_size;

	// Move values over
	for (size_t i = 0; i < this->m_size; i++)
	{
		this->m_data[i] = rhs.m_data[i];
	}

	return *this;
}

template<typename T>
inline stack_vector<T>& stack_vector<T>::operator= (stack_vector<T>&& rhs)
{
	// Resize array
	this->_reallocate(rhs.m_size);
	this->m_size = rhs.m_size;

	// Move values over
	for (size_t i = 0; i < this->m_size; i++)
	{
		this->m_data[i] = std::move(rhs.m_data[i]);
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
		elem_check = (this->m_data[i] == rhs.m_data[i]);
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
		elem_check = (this->m_data[i] != rhs.m_data[i]);
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
		elem_check = (this->m_data[i] < rhs.m_data[i]);
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
		elem_check = (this->m_data[i] <= rhs.m_data[i]);
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
		elem_check = (this->m_data[i] > rhs.m_data[i]);
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
		elem_check = (this->m_data[i] >= rhs.m_data[i]);
	}

	return (same_size && elem_check);
}

#endif
