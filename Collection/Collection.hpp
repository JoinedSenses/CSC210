#pragma once
/* Collection
 * Template for a container class that attempts to resemble a vector */

#define _MYLIB_BEGIN namespace mylib {
#define _MYLIB_END }

#include <assert.h> /* assert() */
#include <utility> /* std::move */
#include <initializer_list> /* std::initializer_list */
#include <cstdlib> /* size_t */

_MYLIB_BEGIN
template <class T>
class Collection {
public:
	/* Iterators */
	using iterator = T *;
	using const_iterator = T const *;

	iterator begin() { return base(); } // Returns iterator to beginning
	const_iterator begin() const { return base(); } // Returns const iterator to beginning

	iterator end() { return base() + size(); } // Returns iterator to end
	const_iterator end() const { return base() + size(); } // Returns const iterator to end

	/* Constuctors */
	Collection() : m_pData(nullptr), m_size(0), m_allocated(0) {}; // Default constructor
	Collection(size_t count); // Preallocation constructor
	Collection(Collection<T> const &toCopy); // Copy contructor;
	Collection(Collection<T> &&toMove) noexcept; // Move constructor
	Collection(const_iterator begin, const_iterator end); // Range constructor
	Collection(std::initializer_list<T> const &list); // Variadic parameter constructor

	/* Deconstructor - deallocates data pointer */
	~Collection();

	/* Function members */
	size_t size() const; // Returns collection size
	bool empty() const; // Checks if collection is empty

	void push(T t); // Adds a new item to collection
	void erase(size_t idx); // Removes item from collection at specified index
	void insert(size_t idx, T); // Inserts item into collection at specified index
	void clear(); // Clears the collection of all items
	void swap(size_t idx1, size_t idx2); // Swaps two items in the collection
	void swap(Collection<T> &c); // Swap two Collections

	/* Operators */
	T &operator[](size_t idx); // Overload [] for accessing index
	T const &operator[](size_t idx) const; // Const overload for accessing index

	Collection<T> &operator=(Collection<T> const &toCopy); // Copies values from another collection
	Collection<T> &operator=(Collection<T> &&toMove) noexcept; // Moves values from another collection
	Collection<T> &operator=(std::initializer_list<T> const &list); // Variadic parameter assignment

private:
	/* Storage members */
	T *m_pData; // Array of items
	size_t m_size; // Count of items in collection
	size_t m_allocated; // Allocated size of collection

	/* Support functions */
	void shiftLeft(size_t idx); // Shifts items right of index to the left, thus overwriting the index.
	void shiftRight(size_t idx); // Shifts index and following indexes to the right by one
	bool growIfNeed(size_t count); // Grows the array if more space is needed.

	/* Returns the base address of data (Can change when adding elements!) */
	T *base() { return m_pData; }
	T const *base() const { return m_pData; }
};

// ------
// Public
// ------

// Preallocation constructor - Presets allocation
// for efficiency if expected to be a large size.
template<class T>
inline Collection<T>::Collection(size_t preAllocSize) {
	assert(preAllocSize > 0);

	m_size = 0;
	m_allocated = preAllocSize;
	m_pData = new T[m_allocated];
}

// Move constructor
template<class T>
inline Collection<T>::Collection(Collection<T> &&toMove) noexcept {
	// Take all of toMove's values
	m_pData = toMove.m_pData;
	m_allocated = toMove.m_allocated;
	m_size = toMove.m_size;

	// Set toMove to default
	toMove.m_pData = nullptr;
	toMove.m_allocated = 0;
	toMove.m_size = 0;
}

// Copy constructor
template<class T>
inline Collection<T>::Collection(Collection<T> const &toCopy) {
	// Copy values and allocate
	m_size = toCopy.m_size;

	// If copied collection is empty
	if (m_size == 0) {
		// initialize values
		m_allocated = 0;
		m_pData = nullptr;
	}
	else { // otherwise
		// allocate memory
		m_allocated = toCopy.m_allocated;
		m_pData = new T[m_size];

		// and loop through array to copy values
		for (size_t i = 0; i < m_size; ++i) {
			m_pData[i] = toCopy.m_pData[i];
		}
	}
}

// Variadic parameter constructor
template<class T>
inline Collection<T>::Collection(std::initializer_list<T> const &list) {
	m_size = 0;

	// If list isnt empty
	if (m_allocated = list.size()) {
		m_pData = new T[m_allocated];

		// Loop through each item in the list and copy it to collection
		for (auto it = list.begin(); it != list.end(); ++it) {
			m_pData[m_size++] = *it;
		}
	}
	else {
		m_pData = nullptr;
	}
}

// Range/Iterator constructor
template<class T>
inline Collection<T>::Collection(const_iterator begin, const_iterator end) : Collection() {
	assert(begin < end);

	// Loop between range and add to collection
	for (; begin != end; ++begin) {
		push(*begin);
	}
}

// Deconstructor, which deallocates memory
template<class T>
inline Collection<T>::~Collection() {
	delete[] m_pData;
}

// Returns current size of collection
template<class T>
inline size_t Collection<T>::size() const {
	return m_size;
}

// Checks if the collection is empty
template<class T>
inline bool Collection<T>::empty() const {
	return !m_size;
}

// Adds a new item to collection
template<class T>
inline void Collection<T>::push(T newItem) {
	if (!growIfNeed(1)) {
		return;
	}

	// Add new item to the next index and increment size
	m_pData[m_size++] = newItem;
}

// Removes item from collection, decreases size, and shifts array left
template<class T>
inline void Collection<T>::erase(size_t idx) {
	// Check if the index is valid
	if (idx >= m_size) {
		return;
	}

	// Shift everything to the left starting from index and decrease size
	shiftLeft(idx);
	--m_size;
}

// Inserts item into collection at specified index and shifts array right
template<class T>
inline void Collection<T>::insert(size_t idx, T item) {
	// Check if the index is valid
	assert(idx <= m_size);

	// Check if array needs to grow
	if (!growIfNeed(1)) {
		return;
	}

	// Shift everything to the right and insert new item
	++m_size;
	shiftRight(idx);
	m_pData[idx] = item;
}

// Sets size to 0,
template<class T>
inline void Collection<T>::clear() {
	m_size = 0;
}

// Swaps two items by index
template<class T>
inline void Collection<T>::swap(size_t idx1, size_t idx2) {
	// Ensure indexes are valid
	assert(idx1 < m_size && idx2 < m_size);

	// Move instead of copying.
	T temp(std::move(m_pData[idx1]));
	m_pData[idx1] = std::move(m_pData[idx2]);
	m_pData[idx2] = std::move(temp);
}

// Swaps two collection
template<class T>
inline void Collection<T>::swap(Collection<T> &c) {
	// Move contents between collections
	Collection<T> temp(std::move(*this));
	*this = std::move(c);
	c = std::move(temp);
}

// Bracket operator to access specified index
template<class T>
inline T &Collection<T>::operator[](size_t idx) {
	assert(idx < m_size);

	return m_pData[idx];
}

// Const bracket operator to access specified index
template<class T>
inline const T &Collection<T>::operator[](size_t idx) const {
	assert(idx < m_size);

	return m_pData[idx];
}

// Copies valies from another collection
template<class T>
inline Collection<T> &Collection<T>::operator=(Collection<T> const &toCopy) {
	if (this != &toCopy) {
		delete[] m_pData; // Deallocate memory
		m_pData = nullptr;
		m_size = toCopy.m_size; // Get size of collection
		m_allocated = m_size;

		// if new collection contains items
		if (m_size) {
			m_pData = new T[m_size]; // Allocate memory with size

			// Loop through array and copy values
			for (size_t i = 0; i < m_size; ++i) {
				m_pData[i] = toCopy.m_pData[i];
			}
		}
	}

	return *this;
}

// Move assignment
template<class T>
inline Collection<T> &Collection<T>::operator=(Collection<T> &&toMove) noexcept {
	if (this != &toMove) {
		delete[] m_pData;

		// Take toMove's values
		m_pData = toMove.m_pData;
		m_allocated = toMove.m_allocated;
		m_size = toMove.m_size;

		// Set toMove to default
		toMove.m_pData = nullptr;
		toMove.m_allocated = 0;
		toMove.m_size = 0;
	}

	return *this;
}

// Variadic params assignment
template<class T>
inline Collection<T> &Collection<T>::operator=(std::initializer_list<T> const &list) {
	m_size = 0;
	delete[] m_pData;

	// If list isnt empty
	if (m_allocated = list.size()) {
		m_pData = new T[m_allocated];

		// Loop through contents and copy to collection
		for (auto it = list.begin(); it != list.end(); ++it) {
			m_pData[m_size++] = *it;
		}
	}
	else {
		m_pData = nullptr;
	}

	return *this;
}


// -------
// Private
// -------

// Shifts items right of index to the left, thus overwriting the index.
template<class T>
inline void Collection<T>::shiftLeft(size_t idx) {
	for (size_t i = idx; i < m_size - 1; ++i) {
		m_pData[i] = std::move(m_pData[i + 1]);
	}
}

// Shifts index and following indexes to the right by one
// Only to be used following growth check
template<class T>
inline void Collection<T>::shiftRight(size_t idx) {
	for (size_t i = m_size - 1; i > idx; --i) {
		m_pData[i] = std::move(m_pData[i - 1]);
	}
}

// Checks if the allocated memory needs to expand to
// account for new items
template<class T>
inline bool Collection<T>::growIfNeed(size_t count) {
	// Check if the array has space
	if (m_size + count <= m_allocated) {
		return true;
	}

	// Create a default array size of 8
	if (m_allocated < 8) {
		m_allocated = 8;
	}

	// Grow exponentially if there isn't enough space
	while (m_size + count > m_allocated) {
		m_allocated *= 2;
	}

	// If data has not been initialized
	if (m_pData == nullptr) {
		// allocate memory
		m_pData = new T[m_allocated];
	}
	else { //otherwise
		// allocate new memory
		T *pData = new T[m_allocated];

		// check if allocation was successful
		if (pData == nullptr) {
			return false;
		}

		// loop through data and copy to new array
		for (size_t i = 0; i < m_size; ++i) {
			pData[i] = std::move(m_pData[i]);
		}

		// free old array and set it equal to new
		delete[] m_pData;
		m_pData = pData;
	}

	return m_pData != nullptr;
}
_MYLIB_END
