#pragma once
#include "Utility.h"
#include "HeapSort.h"
#include <math.h>

template <typename T>
void introSort(T* array, const int size, const int left, const int right, const bool isAscending, int maxDepth)
{
	if (maxDepth == 0)
		heapSort(array + left, right - left + 1, isAscending);
	else if (left < right)
	{
		maxDepth--;
		T pivot = partition(array, size, left, right, isAscending);
		introSort(array, size, left, pivot - 1, isAscending, maxDepth);
		introSort(array, size, pivot + 1, right, isAscending, maxDepth);
	}
}

template <typename T>
void introSort(T* array, int size, const bool isAscending = true)
{
	int maxDepth = (int)(2 * log2(size));
	introSort(array, size, 0, size - 1, isAscending, maxDepth);
}
