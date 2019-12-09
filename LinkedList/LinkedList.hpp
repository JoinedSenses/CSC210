#pragma once
#include <assert.h> /* assert() */
#include <initializer_list> /* std::initializer_list */
#include <cstdlib> /* size_t */

#define _MYLIB_BEGIN namespace mylib {
#define _MYLIB_END }

_MYLIB_BEGIN
template<class T>
class LinkedList {
	struct Node {
		T data;
		Node *next;
	};

	Node *m_front;
	Node *m_back;
	size_t m_count;
public:
/* Constructors */
	// Default
	LinkedList() : m_front(nullptr), m_back(nullptr), m_count(0) {};
	// Copy
	LinkedList(LinkedList<T> const &other);
	// Move
	LinkedList(LinkedList const &&other);
	// Init List
	LinkedList(std::initializer_list<T> const &list);

/* Destructor*/
	~LinkedList();

/* Operators*/
	// Access item at specified index.
	// Assumes index is valid.
	T &operator[](size_t idx);
	T &operator[](size_t idx) const;

	// Sets one list equal to another.
	LinkedList<T> &operator=(LinkedList<T> const &other);

/* Functions */
	// Pushes item to end of list.
	void push(T item);

	// Inserts item before specified index.
	// Specified index is valid.
	void insert(T item, size_t idx);

	// Removes item at specified index.
	// Assumes index is valid.
	void erase(size_t idx);

	// Removes all items from list and sets count to 0.
	void clear();

	// Returns if list is empty.
	bool empty();

	// Returns number of items in list.
	size_t length();
};

// Copy Constructor
template<class T>
inline LinkedList<T>::LinkedList(LinkedList<T> const &other) {
	m_count = other.m_count;
	m_front = nullptr;
	m_back = nullptr;

	// Loop through and copy contents from other list
	Node *current = other.m_front;
	Node *node;
	while (current != nullptr) {
		node = new Node();
		node->data = current->data;
		node->next = nullptr;

		if (m_back == nullptr) {
			m_front = node;
			m_back = node;
		}
		else {
			m_back->next = node;
			m_back = node;
		}

		current = current->next;
	}
}

// Move Constructor
template<class T>
inline LinkedList<T>::LinkedList(LinkedList const &&other) {
	// Take ownership of other list's items

	m_front = other.m_front;
	other.m_front = nullptr;

	m_back = other.m_back;
	other.m_back = nullptr;

	m_count = other.m_count;
	other.m_count = 0;
}

// Initialization List Constructor
template<class T>
inline LinkedList<T>::LinkedList(std::initializer_list<T> const &list) {
	m_count = 0;
	m_front = nullptr;
	m_back = nullptr;

	// Loop through list and push items to list
	for (auto const data : list) {
		push(data);
	}
}

// Desctructor
template<class T>
inline LinkedList<T>::~LinkedList() {
	Node *node;
	while (m_front != nullptr) {
		node = m_front;
		m_front = m_front->next;
		delete node;
	}
}

// Bracket Operator
template<class T>
inline T &LinkedList<T>::operator[](size_t idx) {
	assert(idx < m_count);

	// Loop through nodes until reaching index
	Node *node = m_front;
	for (size_t i = 0; i < idx; ++i) {
		node = node->next;
	}

	return node->data;
}

// Bracket Operator Const
template<class T>
inline T &LinkedList<T>::operator[](size_t idx) const {
	assert(idx < m_count);

	// Loop through nodes until reaching index
	Node *node = m_front;
	for (size_t i = 0; i < idx; ++i) {
		node = node->next;
	}

	return node->data;
}

// Assignment Operator
template<class T>
inline LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> const &other) {
	clear();

	m_count = other.m_count;
	m_front = nullptr;
	m_back = nullptr;

	// Loop through other list and copy contents
	Node *current = other.m_front;
	Node *node;
	while (current != nullptr) {
		node = new Node();
		node->data = current->data;
		node->next = nullptr;

		if (m_back == nullptr) {
			m_front = node;
			m_back = node;
		}
		else {
			m_back->next = node;
			m_back = node;
		}

		current = current->next;

	}

	return *this;
}

// Pushes item to end of list.
template<class T>
inline void LinkedList<T>::push(T item) {
	++m_count;

	Node *node = new Node();
	node->data = item;
	node->next = nullptr;

	if (m_front == nullptr) {
		m_front = node;
		m_back = node;
	}
	else {
		m_back->next = node;
		m_back = node;
	}
}

// Inserts item before specified index.
// Specified index is valid.
template<class T>
inline void LinkedList<T>::insert(T item, size_t idx) {
	assert(idx < m_count);

	Node *node = new Node();
	node->data = item;
	node->next = nullptr;

	Node *current = m_front;
	Node *previous = nullptr;

	// Loop through nodes until reaching index
	for (size_t i = 0; i < idx; ++i) {
		previous = current;
		current = current->next;
	}

	// Insert at beginning if previous node is null
	if (previous == nullptr) {
		node->next = m_front;
		m_front = node;
	}
	// otherwise, insert it after previous node
	else {
		node->next = current;
		previous->next = node;
	}

	++m_count;
}

// Removes item at specified index.
// Assumes index is valid.
template<class T>
inline void LinkedList<T>::erase(size_t idx) {
	assert(idx < m_count);

	Node *previous = nullptr;
	Node *current = m_front;

	// Loop through nodes until reaching index
	for (size_t i = 0; i < idx; ++i) {
		previous = current;
		current = current->next;
	}

	// If index is front, move front to next node
	if (current == m_front) {
		m_front = current->next;
	}
	// If index is back, move back to previous node
	if (current == m_back) {
		m_back = previous;
	}

	// Set previous link to next node
	if (previous != nullptr) {
		previous->next = current->next;
	}

	// Delete the node
	delete current;
	--m_count;
}

// Removes all items from list and sets count to 0.
template<class T>
inline void LinkedList<T>::clear() {
	Node *node;
	while (m_front != nullptr) {
		node = m_front;
		m_front = m_front->next;
		delete node;
	}

	m_back = nullptr;
	m_count = 0;
}

// Returns if list is empty.
template<class T>
inline bool LinkedList<T>::empty() {
	return !m_count;
}

// Returns number of items in list.
template<class T>
inline size_t LinkedList<T>::length() {
	return m_count;
}

_MYLIB_END
