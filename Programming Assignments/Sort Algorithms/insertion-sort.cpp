//============================================================================
// Name        : insertion-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"



void
InsertionSort::sort(int A[], int size)				// main entry point
{
	
	int j = 0;
	int temp;
	for (int i = 0; i < size; i++){
		j = i;
		num_cmps++;
		while (j > 0 && A[j-1] > A[j]) {
			temp = A[j];
			A[j] = A[j - 1];
			A[j - 1] = temp;
			j--;
		}

	}
	

  /* Complete this function with the implementation of insertion sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
}

