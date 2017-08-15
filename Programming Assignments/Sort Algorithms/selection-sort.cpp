//============================================================================
// Name        : selection-sort.cpp
// Author      : Garret Sifuentez
// Date        :9/14/16
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)				// main entry point
{
	for (int k = 0; k < size-1; k++) {
		int index = k;
		for (int i = k+1; i < size; i++) {
			num_cmps++;
			if (A[i] < A[index]) {
				index = i;
			}
		}
		int tmp = A[k]; 
		A[k] = A[index];
		A[index] = tmp;
	}
}
