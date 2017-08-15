//============================================================================
// Name        : bubble-sort.cpp
// Author      : Oneal Abdulrahim
// Date        : 14 September 2016
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(int A[], int size) {			// main entry point
	/* Complete this function with the implementation of bubble sort algorithm 
	 Record number of comparisons in variable num_cmps of class Sort
	*/
	while (!testIfSorted(A, size)) { // as long as we are not sorted
		for (int i = 0; i < size; ++i) { // loop through the array
			if (A[i] > A[i + 1]) { // find the larger element
				
				// fancy way to swap integers
				// muh efficiency
				A[i] = A[i] ^ A[i + 1];
				A[i + 1] = A[i] ^ A[i + 1];
				A[i] = A[i] ^ A[i + 1];
			}
			
			num_cmps++; // we do only one comparison per interation
		}
	}
}
