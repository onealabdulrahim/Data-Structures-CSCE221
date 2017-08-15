/**
@Title A1: templated vector
@Author Oneal Abdulrahim
@Purpose To implement a vector class in C++
		 relative to the Array data structure
@Due Monday, September 12, 2016
@Files main.cpp	My_vec.cpp My_vec.h makefile
*/

#include "My_vec.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

/// default constructor
/**
Reserves memory for user data. */
template <typename T>
My_vec<T>::My_vec()
	: size(0), 
	  capacity(10),
	  ptr(new T[capacity]()) {}

/// destructor
/**
Deallocates element data when My_vec goes out of scope,
or when this method is called explicitly. */
template <typename T>
My_vec<T>::~My_vec() {
	delete[] ptr;
}

/// copy constructor
/**
Allocates new My_vec object to the properties of the
current one. Copies old data into new. Keeps both objects & data in memory. 
@param vec	the object to copy from */
template <typename T>
My_vec<T>::My_vec(const My_vec<T>& vec)
	: size {vec.get_size()},		// initialize to the new vector's values
	  capacity {vec.get_capacity()},
	  ptr{new T[vec.get_capacity()]}
	{
		for (int i = 0; i <= capacity; ++i) { // copy old elements to new vector
			ptr[i] = vec.ptr[i];	
		}
		
	}

/// copy-assignment
/**
Copy-assignment through operator "=" overload. The new elements are loaded
to a temporary object. The current pointer to elements is deleted, then set
to this temp object.

@param vec	the object to assign from */
template <typename T>
My_vec<T>& My_vec<T>::operator=(const My_vec<T>& vec) {
	size = vec.get_size();
	capacity = vec.get_capacity();
	
	// if it's an attempted self-assignment, return reference to this
	if (this == &vec) {
		return *this;
	}
	
	// If we have enough space, there is no need for new allocation
	if (vec.get_size() <= capacity) {
		for (int i = 0; i < vec.get_size(); ++i) {
			ptr[i] = vec.ptr[i]; // copy elements from vector
		}
		capacity += size - vec.get_size();
		size = vec.get_size();
		return *this;
	}
	
	T* temp = new T[vec.get_capacity()]; // new space for new elements
	
	for (int i = 0; i <= vec.get_capacity(); ++i) { // copy new elements
		temp[i] = vec.ptr[i];
	}
	
	delete[] ptr; // deallocate old space
	size = vec.get_size(); // set new size & capacity
	capacity = vec.get_capacity();
	ptr = temp; // set new element location
	
	return *this; // return self-reference
}

/// size getter
/**
Returns the current size of My_vec (how many elements it is holding)

@return size	The size data member */
template <typename T>
int My_vec<T>::get_size() const {
	return size;
}

/// capacity getter
/**
Returns the current capcaity of My_vec (how many elements it can hold)

@return capacity	The capacity data member */
template <typename T>
int My_vec<T>::get_capacity() const {
	return capacity;
}

/// access operator (const)
/**
Overloading the [] operator to ensure access to elements is direct

@param i	the index of the desired element	
@return elem_at_rank(i)	call to member function */
template <typename T>
T& My_vec<T>::operator[](int i) const {
	return elem_at_rank(i);
}

/// access operator
/**
Overloading the [] operator to ensure access to elements is direct

@param i	the index of the desired element	
@return elem_at_rank(i)	call to member function */
template <typename T>
T& My_vec<T>::operator[](int i) {
	return elem_at_rank(i);
}

/// is empty
/**
Verifies if the current My_vec has no elements in it

@return	true if size is 0 */
template <typename T>
bool My_vec<T>::is_empty() const {
	return size == 0;
}

/// access
/**
Finds the element of My_vec at index.

@param r	the index of the desired element
@return 	the element at index r */
template <typename T>
T& My_vec<T>::elem_at_rank(int r) const {
	return ptr[r]; // cheap & easy
}

/// insert element
/**
Places an element at given index. Moves all greater indexed elements by +1.
Generally, this is most costly if inserting near the beginning of My_vec

@param r	the index to insert at
@param elem	the element to insert */
template <typename T>
void My_vec<T>::insert_at_rank(int r, const T& elem) {
	if (r < 0) {
		throw std::out_of_range("The index must be positive!");
	} 
	
	if (r >= size) { // if we cannot fit, expand the vector
		for (int i = size; i <= r; ++i) {
			T* empty = new T();
			ptr[i] = *empty;
			delete empty;
		}
		size = r; 
		
		while (size > capacity) {
			capacity *= 2;	// if we're at capacity, double it
		}
		
		T* temp = new T[capacity];
		
		for (int i = 0; i < size; ++i) {
			if (i < size) {
				temp[i] = ptr[i];
			} else {
				T* empty = new T();
				temp[i] = *empty;
				delete empty;
			}
		}
		
		delete[] ptr; // deallocate old memory
		ptr = temp; // set new memory
	}
	
	for (int i = size; i > r; --i) { // push forward data to make room
		ptr[i] = ptr[i - 1];
	}
	
	++size;
	ptr[r] = elem; // finish insertion
}

/// replace element
/**
Replaces an element at given index. If an out of bounds index is provided,
this method simply inserts this element at given index using above method.

@param r	the index to replace at
@param elem	the element to insert */
template <typename T>
void My_vec<T>::replace_at_rank(int r, const T& elem) {
	if (r > size) {  // will throw error if cannot fit
		insert_at_rank(r, elem); // ...out of bounds indices
	} else {
		ptr[r] = elem; // if inbounds, simply reassign the value at that index
	}

}

/// remove element
/**
Removes element at given index by copying all elements starting by overriding r.

@param r	the index to remove */
template <typename T>
void My_vec<T>::remove_at_rank(int r) {
	if (r > capacity) {
		throw std::invalid_argument("Cannot remove outside of My_vec!");
	} else {
		for (int i = r; i < capacity; ++i) { // pushing all index down
			ptr[i] = ptr[i+1];
		}
		--size;
	}
}