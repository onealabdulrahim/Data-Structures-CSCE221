/**
@Title A1: templated vector
@Author Oneal Abdulrahim
@Purpose To implement a vector class in C++
		 relative to the Array data structure
@Due Monday, September 12, 2016
@Files main.cpp	My_vec.cpp My_vec.h makefile
*/

#include <iostream>
using namespace std;

template <class T> class My_vec {
	
	//member variables
	int size, capacity;
	T *ptr;

public:	
	//member functions
	My_vec();
	~My_vec();
	My_vec(const My_vec<T>&);
	My_vec<T>& operator=(const My_vec<T>&);
	int get_size() const;
	int get_capacity() const;
	T& operator[](int) const;
	T& operator[](int);
	bool is_empty() const;
	T& elem_at_rank(int) const;
	void insert_at_rank(int, const T&);
	void replace_at_rank(int, const T&);
	void remove_at_rank(int);
	
};

/// overload <<
/**
Prints vector nicely :) I ♥ toString methods */
template <typename T>
std::ostream& operator<<(std::ostream& out, const My_vec<T>& vec) {
	if (!vec.is_empty()) {
		for (int i = 0; i < vec.get_size(); ++i) {
			std::cout << "\t[" << i << "] ► " << vec.elem_at_rank(i) << endl;
		}
	} else {
		cout << "My_vec is empty!" << endl;
	}
}

/// search max index
/**
Searches for the index of the greatest valued element, and in the case of T,
the greatest T value. This method relies on the validity of the < comparison

@param v	the My_vec to operate on
@param size	the size of My_vec
@return	maximum	the index of the maxmimum value */
template <typename T>
int find_max_index(const My_vec<T>& v, int size) {
	int maxmimum = 0; // we must start somewhere
	for (int i = 1; i < size; ++i) {
		if (v[maxmimum] < v[i]) { // is current index larger than our maximum?
			maxmimum = i;
		}
	}
	return maxmimum;
}

/// sort ascending
/**
Sorts the given My_vec object using an implementation of Selection Sort.
This sort is costly and sad. Hopefully we will learn more about Big-O and
other sorts.

@param v	the My_vec to operate on */
template <typename T>
void sort_max(My_vec<T>& vec) {
	// iterate through items, find the maximum (we've written this above)      
	for (int i = 0; i < vec.get_size() / 2; ++i) {
		int maximum = find_max_index(vec, vec.get_size() - i);

		// swap the max with its index & value at size
		T temp = vec[vec.get_size() - 1 - i];
		vec[vec.get_size() - 1 - i] = vec[maximum];
		vec[maximum] = temp;
	}
}
	