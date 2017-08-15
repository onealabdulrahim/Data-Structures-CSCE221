/*
@Title		CSCE221 Homework 1
@Author		Oneal Abdulrahim
@Purpose 	To implement a binary search in C++ and test it for
				correctness, efficiency, and speed.
@Due 		23 September, 2016
@Files 		binary_search.cpp
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int comparisons = 0;

/// Sorted int vector checker
/**
Returns 1 if the vector is sorted in ascending, 0 in descending
and -1 if not sorted at all.
@param v	The vector to be checked */
int is_sorted(vector<int> v) {
	int result = 1;
	for (int i = 1; i < v.size(); ++i) { // check for ascending
		if (v[i] < v[i - 1]) {
			result = -1;
		}
	}
	
	if (result == -1) { // if previous check failed,
		for (int i = 1; i < v.size(); ++i) { // check for descending
			if (v[i] > v[i - 1]) {
				return -1; // if failed, the vector is not sorted
			}
		}
		result = 0; // if reached, not ascending, but it is descending
	}
	
	return result; // 0 or 1, -1 has already been returned if not sorted
}

/// Input file creation
/**
Creates a vector of ordered integers from 0 to size - 1
@param size	The number of ints to generate
@return result	The filled vector */
vector<int> read_ints(int size, int direction) {
	
	vector<int> result;
	
	if (direction == 1) {
		for (int i = 0; i <= size; ++i) { // load vector of sorted ints
			result.push_back(i);
		}
	} else {
		for (int i = size; i >= 0; --i) { // load vector of sorted ints
			result.push_back(i);
		}
	}
	
	return result;
}

/// Binary search implementation
/**
A recursive implementation of the binary search.
@param v		The vector to search
@param first	The minimum index to search from
@param last		The maximum index to search to
@param item		The key that is being searched for
@return			The index of item */
int my_binary_search(vector<int> const &v, int first, int last, int item) {
	
	if (is_sorted(v) == -1) {
		cout << "The array is unsorted!! \n\n\n" << endl;
		return -1;
	}
	
	if (is_sorted(v) == 1) { // IF WE ARE ASCENDING ORDER
		if (v[(first + last) / 2] < item) { // if the middle index is less
			comparisons++;
			my_binary_search(v, (first + last) / 2, last, item);
		} else if (v[(first + last) / 2] > item) { // if the middle index is greater
			comparisons++;
			my_binary_search(v, first, (first + last) / 2, item);
		} else { // if we did not pass either condition above, the integer matches
			return (first + last) / 2;
		}
	} else { // IF WE ARE DESCENDING ORDER
		if (v[(first + last) / 2] < item) { // if the middle index is less
			comparisons++;
			my_binary_search(v, first, (first + last) / 2, item);
		} else if (v[(first + last) / 2] > item) { // if the middle index is greater
			comparisons++;
			my_binary_search(v, (first + last) / 2, last, item);
		} else { // if we did not pass either condition above, the integer matches
			return (first + last) / 2;
		}
	}
	
}

int main() {
	int choice;
	cout << "Ascending (1) or descending? (0)" << endl;
	cin >> choice;
	vector<int> ints = read_ints(2048, choice);
	
	cout << "Pick an integer item to search for [1, 2048]: ";
	cin >> choice;
	
	while (choice != -1) {
		if (choice < 0 || choice > ints.size()) {
			cout << "*****Please try again within the given range*****\n\n\n" << endl;
			choice = -1;
		}
		cout << "We can find the number " << choice << " at index "
			 << my_binary_search(ints, 0, ints.size(), choice)
			 << ". #comps:\t" << comparisons << "\n" << endl;
		comparisons = 0;
		cout << "Pick an integer item to search for [1, 2048]: ";
		cin >> choice;
	}
	
	cout << "Thanks!" << endl;
	
	return 0;
}