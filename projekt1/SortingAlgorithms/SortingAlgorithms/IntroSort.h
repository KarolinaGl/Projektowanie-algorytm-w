#pragma once
#include "Utility.h"
#include "HeapSort.h"

template <typename T>
void introSort(T* array, const int size, const int left, const int right, const bool isAscending)
{
	if ((right - left + 1) >= 16)
	{
		T pivot = partition(array, size, left, right, isAscending);
		introSort(array, size, left, pivot - 1, isAscending);
		introSort(array, size, pivot + 1, right, isAscending);
	}
	else
		heapSort(array + left, right - left + 1, isAscending);
}

template <typename T>
void introSort(T* array, int size, const bool isAscending = true)
{
	introSort(array, size, 0, size - 1, isAscending);
}
