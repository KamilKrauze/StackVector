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
}; // !iterator<stack_vector<T>> class


// Regular iterator
template<typename stack_vector>
class iterator : public const_iterator<stack_vector> {
public:
	using ValueType = typename stack_vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	iterator() { m_ptr = nullptr; }
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

}; // !iterator<stack_vector<T>> class
namespace sad {
	// Dynamic stack allocated vector
	template<typename T>
	class stack_vector
	{
	public:
		using ValueType = T;
		using iterator = iterator<stack_vector<T>>;
		using const_iterator = const_iterator<stack_vector<T>>;

		/* Allocation / Deallocation */
	public:

		// Default constructor.
		inline stack_vector() noexcept
		{
			this->_reallocate(2);
		}

		// Fill constructor
		inline explicit stack_vector(size_t size)
		{
			this->_reallocate(size);
		}

		// Initializer constructor
		inline stack_vector(std::initializer_list<T> init_list)
		{
			const size_t new_size = init_list.size();
			this->_reallocate(new_size);
			std::copy(init_list.begin(), init_list.end(), m_data);
			m_size = new_size;
		}

		// Copy constructor
		inline stack_vector(const stack_vector<T>& vec)
		{
			const size_t new_size = vec.size();
			this->_reallocate(vec.capacity());

			for (size_t i = 0; i < new_size; i++)
				m_data[i] = vec.m_data[i];

			m_size = new_size;
		}

		// Move constructor
		inline stack_vector(stack_vector<T>&& vec) noexcept
		{
			const size_t new_size = vec.size();
			this->_reallocate(vec.capacity());

			for (size_t i = 0; i < new_size; i++)
				m_data[i] = vec.m_data[i];

			m_size = new_size;
		}

		// Range constructor
		stack_vector(iterator first, iterator last)
		{
			size_t size = last.m_ptr - first.m_ptr;
			this->_reallocate(size);
			m_size = size;
			std::copy(first.m_ptr, last.m_ptr, m_data);
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

		// Assign value of n amount
		inline void assign(size_t n, const T& val)
		{
			this->_reallocate(m_capacity + n + (m_capacity / 2));
			m_size = n;

			for (size_t i = 0; i < n; i++)
				m_data[i] = T(val);
		}

		// Assign values by initializer list.
		inline void assign(std::initializer_list<T> init_list)
		{
			const size_t size = init_list.size();
			this->_reallocate(m_capacity + size + (m_capacity / 2));
			m_size = size;

			std::copy(init_list.begin(), init_list.end(), m_data);
		}

		// Assign value of n amount, by iterators
		inline void assign(const_iterator first, const_iterator last)
		{
			const size_t size = last.m_ptr - first.m_ptr;
			this->_reallocate(m_capacity + size + (m_capacity / 2));
			m_size = size;

			for (size_t i = 0; i < m_size; i++)
				m_data[i] = T(*(first + i));

		}

		inline void push_back(const T& value)
		{
			if (m_size >= m_capacity)
				this->_reallocate(m_capacity + (m_capacity / 2));

			m_data[m_size] = value;
			m_size++;
		}

		inline void push_back(T&& value)
		{
			std::cout << &value << "\n";
			if (m_size >= m_capacity)
				this->_reallocate(m_capacity + (m_capacity / 2));

			m_data[m_size] = std::move(value);
			m_size++;
		}

		inline void pop_back() noexcept
		{
			if (m_size > 0) {
				m_size--;
				m_data[m_size].~T();
			}
		}

		// Insert element at position.
		inline iterator insert(const_iterator position, const T& val)
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

			m_data[index] = T(val);

			return iterator(m_data + index);
		}

		// Insert element n amount of times at defined position.
		inline iterator insert(const_iterator position, size_t n, const T& val)
		{
			// Calculate the index based on the pointer difference
			auto* loc = position.m_ptr;
			const size_t index = loc - m_data;

			if (m_size >= m_capacity) {
				this->_reallocate(m_capacity + n + (m_capacity / 2));
			}
			m_size += n;

			// Shift elements to make space for the new one
			for (size_t i = m_size; i > index; --i)
				m_data[i] = std::move(m_data[i - n]);

			// Add the values n amount of times.
			for (size_t i = index; i < index + n; ++i)
				m_data[i] = std::move(val);

			return iterator(m_data + index);
		}

		// Insert element n amount of times at defined position.
		inline iterator insert(const_iterator position, size_t n, const T&& val)
		{
			// Calculate the index based on the pointer difference
			auto* loc = position.m_ptr;
			const size_t index = loc - m_data;

			if (m_size >= m_capacity) {
				this->_reallocate(m_capacity + n + (m_capacity / 2));
			}
			m_size += n;

			// Shift elements to make space for the new one
			for (size_t i = m_size; i > index; --i)
				m_data[i] = std::move(m_data[i - n]);

			// Add the values n amount of times.
			for (size_t i = index; i < index + n; ++i)
				m_data[i] = std::move(val);

			return iterator(m_data + index);
		}

		// Insert element n amount of times at position, with iterators.
		inline iterator insert(const_iterator position, const_iterator first, const_iterator last)
		{
			auto* loc = position.m_ptr;
			const size_t index = loc - m_data;
			const size_t n = last.m_ptr - first.m_ptr;

			if (m_size >= m_capacity) {
				this->_reallocate(m_capacity + n + (m_capacity / 2));
			}
			m_size += n;

			// Shift elements by n-spaces, to make space for the new one
			for (size_t i = m_size; i > n; --i)
				m_data[i] = std::move(m_data[i - n]);

			// Add the values n-amount of times.
			for (size_t i = index + 1; i < index + n; ++i)
				m_data[i] = T(first.m_ptr[i]);

			return iterator(m_data + index);
		}

		inline iterator insert(const_iterator position, std::initializer_list<T> init_list)
		{
			auto* loc = position.m_ptr;
			const size_t index = loc - m_data;
			const size_t n = init_list.size();

			if (m_size >= m_capacity) {
				this->_reallocate(m_capacity + n + (m_capacity / 2));
			}
			m_size += n;

			// Shift elements by n-spaces, to make space for the new one
			for (size_t i = m_size; i > n; --i)
				m_data[i] = std::move(m_data[i - n]);

			// Add the values n-amount of times.
			auto it = init_list.begin();
			for (size_t i = 0; i < n; ++i, ++it)
				new (&m_data[index + i]) T(*it);

			return iterator(m_data + index);
		}

		inline iterator erase(const_iterator position) noexcept
		{
			// Calculate the index based on the pointer difference
			auto* loc = position.m_ptr;
			size_t index = loc - m_data;

			// Delete element at location
			m_data[index].~T();
			m_size--;

			// Shift elements to compensate for removed element
			for (size_t i = index; i < m_size; i++)
				m_data[i] = std::move(m_data[i + 1]);

			return iterator(m_data + index);
		}

		inline iterator erase(const_iterator first, const_iterator last) noexcept
		{
			// Ensure the range is valid
			assert(first.m_ptr >= m_data && first.m_ptr <= m_data + m_size);
			assert(last.m_ptr >= m_data && last.m_ptr <= m_data + m_size);
			assert(first.m_ptr <= last.m_ptr);

			const size_t start_index = first.m_ptr - m_data;
			const size_t end_index = last.m_ptr - m_data;
			const size_t n = last.m_ptr - first.m_ptr;

			// Destroy elements at these indices
			for (size_t i = start_index; i < end_index; ++i)
				m_data[i].~T();

			// Shift elements after the erased range to fill the gap
			for (size_t i = end_index; i < m_size; ++i)
				m_data[i - n] = std::move(m_data[i]);

			m_size -= n;

			return iterator(m_data + start_index);
		}

		inline void swap(stack_vector<T>& other) noexcept
		{
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
			std::swap(m_data, other.m_data);
		}

		inline void swap(stack_vector<T>&& other) noexcept
		{
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
			std::swap(m_data, other.m_data);
		}

		template<typename... Args>
		inline iterator emplace(const_iterator position, Args&&... args)
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

			return iterator(m_data + index);
		}

		template<typename... Args>
		void emplace_back(Args&&... args)
		{
			if (m_size >= m_capacity)
				this->_reallocate(m_capacity + (m_capacity / 2));

			new(&m_data[m_size]) T(std::forward<Args>(args)...);
			m_size++;
		}

		// Flip each boolean in list.
		template <typename U = T, typename std::enable_if<std::is_same<U, bool>::value, int>::type = 0>
		inline void flip() noexcept
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				m_data[i] = !m_data[i];
			}
		}

		/*----------------------------------------------------------*/
		/*						Element access						*/
		/*----------------------------------------------------------*/
		// Get the first element.

		// Get copy of element at this index.
		_NODISCARD inline T at(const size_t index)
		{
			assert((index >= 0 && index < m_capacity));
			return m_data[index];
		}

		// Get copy of element at this index as const.
		_NODISCARD inline const T at(const size_t index) const
		{
			assert((index >= 0 && index < m_capacity));
			return m_data[index];
		}

		// Get the first element.
		_NODISCARD inline T& front()
		{
			assert(m_size > 0);
			return m_data[0];
		}

		// Get the first element as const.
		_NODISCARD inline const T& front() const
		{
			assert(m_size > 0);
			return m_data[0];
		}

		// Get the last element.
		_NODISCARD inline T& back()
		{
			assert(m_size > 0);
			return m_data[m_size - 1];
		}

		// Get the last element as const.
		_NODISCARD inline const T& back() const
		{
			assert(m_size > 0);
			return m_data[m_size - 1];
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

		/* -------------------------------*/
		/*	    iterator iterators	      */
		/* -------------------------------*/

		// iterator pointing at the start.
		_NODISCARD inline iterator begin() noexcept
		{
			return iterator(m_data);
		}
		// iterator pointing at the end.
		_NODISCARD inline iterator end() noexcept
		{
			return iterator(m_data + (m_size));
		}
		// iterator pointing at the reversed start.
		_NODISCARD inline iterator rbegin() noexcept
		{
			return iterator(m_data + (m_size));
		}
		// iterator pointing at the reversed end.
		_NODISCARD inline iterator rend() noexcept
		{
			return iterator(m_data);
		}

		/* -------------------------------*/
		/*	  const_iterator iterators	  */
		/* -------------------------------*/

		// const_iterator pointing at the start.
		_NODISCARD inline const_iterator begin() const noexcept
		{
			return const_iterator(m_data);
		}

		// const_iterator pointing at the end.
		_NODISCARD inline const_iterator end() const noexcept
		{
			return const_iterator(m_data + (m_size));
		}

		// const_iterator pointing at the reversed start.
		_NODISCARD inline const_iterator rbegin() const noexcept
		{
			return const_iterator(m_data + (m_size));
		}

		// const_iterator pointing at the reversed end.
		_NODISCARD inline const_iterator rend() const noexcept
		{
			return const_iterator(m_data);
		}

		/* -------------------------------*/
		/* Const const_iterator iterators */
		/* -------------------------------*/

		//constant const_iterator pointing at the start.
		_NODISCARD inline const_iterator cbegin() const noexcept
		{
			return const_iterator(m_data);
		}
		//constant const_iterator pointing at the end.
		_NODISCARD inline const_iterator cend() const noexcept
		{
			return const_iterator(m_data + (m_size));
		}
		//constant const_iterator pointing at the reversed start.
		_NODISCARD inline const_iterator crbegin() const noexcept
		{
			return const_iterator(m_data + (m_size));
		}
		//constant const_iterator pointing at the reversed end.
		_NODISCARD inline const_iterator crend() const noexcept
		{
			return const_iterator(m_data);
		}

		/*----------------------------------------------------------*/
		/*						   Capacity						    */
		/*----------------------------------------------------------*/

		// Get amount of elements.
		_NODISCARD inline size_t size() const noexcept { return m_size; }

		_NODISCARD inline size_t max_size() const noexcept { return std::numeric_limits<size_t>::max() / sizeof(T); }

		// Get amount of elements that can fit.
		size_t capacity() const noexcept { return m_capacity; }

		// Destroy vector contents
		inline void clear() noexcept
		{
			for (size_t i = 0; i < m_size; i++)
				m_data[i].~T();
			m_size = 0;
		}

		// Change size
		inline void resize(size_t size, T value = T())
		{
			_reallocate(size);
			for (size_t i = m_size; i < size; i++)
				m_data[i] = value;

			m_size = size;
		}

		// Reserve some n-th space, resize array if needed.
		inline void reserve(size_t new_capacity)
		{
			bool resize = false;
			(new_capacity > m_capacity) ? (m_capacity = new_capacity) : (resize = true);

			if (resize)
				_reallocate(m_capacity);
		}

		// Check if empty
		_NODISCARD_EMPTY_MEMBER inline bool empty() const { return (this->m_size == 0); }

		void shrink_to_fit() { m_capacity = m_size; }

		/*----------------------------------------------------------*/
		/*						Operator Overload					*/
		/*----------------------------------------------------------*/
	public:
		void* operator new(size_t size); // Disable new
		void operator delete(void*); // Disable delete

		T& operator[](const size_t index) noexcept
		{
			assert((index >= 0 && index < m_capacity));
			return this->m_data[index];
		}

		const T& operator[](const size_t index) const noexcept
		{
			assert((index >= 0 && index < m_capacity));
			return this->m_data[index];
		}

		/* Assignment */
		inline stack_vector<T>& operator=(const stack_vector<T>& rhs) noexcept
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

		inline stack_vector<T>& operator= (stack_vector<T>&& rhs)
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

		/* Relational */
		inline bool operator== (const stack_vector<T> rhs)
		{
			bool same_size = (this->m_size == rhs.m_size); // Check if both vectors are of the same size.
			bool elem_check = false;

			for (size_t i = 0; i < this->m_size; i++)
			{
				elem_check = (this->m_data[i] == rhs.m_data[i]);
			}

			return (same_size && elem_check);
		}

		inline bool operator!=(const stack_vector<T> rhs)
		{
			bool same_size = (this->m_size != rhs.m_size); // Check if both vectors are not of the same size.
			bool elem_check = false;

			for (size_t i = 0; i < this->m_size; i++)
			{
				elem_check = (this->m_data[i] != rhs.m_data[i]);
			}

			return (same_size || elem_check);
		}

		inline bool operator<(const stack_vector<T> rhs)
		{
			bool same_size = (this->m_size < rhs.m_size); // Check if right vector is larger.
			bool elem_check = false;

			for (size_t i = 0; i < this->m_size; i++)
			{
				elem_check = (this->m_data[i] < rhs.m_data[i]);
			}

			return (same_size || elem_check);
		}

		inline bool operator<=(const stack_vector<T> rhs)
		{
			bool same_size = (this->m_size <= rhs.m_size); // Check if right vector is larger or equal.
			bool elem_check = false;

			for (size_t i = 0; i < this->m_size; i++)
			{
				elem_check = (this->m_data[i] <= rhs.m_data[i]);
			}

			return (same_size && elem_check);
		}

		inline bool operator>(const stack_vector<T> rhs)
		{
			bool same_size = (this->m_size > rhs.m_size); // Check if right vector is smaller.
			bool elem_check = false;

			for (size_t i = 0; i < this->m_size; i++)
			{
				elem_check = (this->m_data[i] > rhs.m_data[i]);
			}

			return (same_size || elem_check);
		}

		inline bool operator>=(const stack_vector<T> rhs)
		{
			bool same_size = (this->m_size >= rhs.m_size); // Check if right vector is smaller or equal.
			bool elem_check = false;

			for (size_t i = 0; i < this->m_size; i++)
			{
				elem_check = (this->m_data[i] >= rhs.m_data[i]);
			}

			return (same_size && elem_check);
		}


		/* Helper Functions */
	private:

		inline void stack_vector<T>::_reallocate(const size_t new_capacity)
		{

			T* new_data = static_cast<T*>(_alloca(new_capacity * sizeof(T)));
			//T* new_data = new T[new_capacity * sizeof(T)];

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

} // !namespace sad
#endif
