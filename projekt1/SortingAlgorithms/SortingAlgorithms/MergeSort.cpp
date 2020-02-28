#include "MergeSort.h"
#include <iostream>

void mergeSort(int* array, const int size, const bool isAscending)
{
	mergeSort(array, 0, size - 1, isAscending);
}

void mergeSort(int* array, const int left, const int right, const bool isAscending)
{
	if (right > left)
	{
		int middle = (right + left) / 2;
		mergeSort(array, left, middle, isAscending);
		mergeSort(array, middle + 1, right, isAscending);
		merge(array, left, middle, right, isAscending);
	}
}

void merge(int* array, const int left, const int middle, const int right, const bool isAscending)
{
	int size = right - left + 1;
	int* tempArray = new int[size];
	int leftIndex = left;
	int rightIndex = middle + 1;
	for (int tempArrayIndex = 0; tempArrayIndex < size; tempArrayIndex++)
	{
		if (isAscending)
		{
			if (leftIndex > middle || (rightIndex <= right && array[leftIndex] >= array[rightIndex]))
				tempArray[tempArrayIndex] = array[rightIndex++];
			else
				tempArray[tempArrayIndex] = array[leftIndex++];
		}
		else
		{
			if (leftIndex > middle || (rightIndex <= right && array[leftIndex] <= array[rightIndex]))
				tempArray[tempArrayIndex] = array[rightIndex++];
			else
				tempArray[tempArrayIndex] = array[leftIndex++];
		}
	}
	for (int i = 0; i < size; i++)
		array[left + i] = tempArray[i];
	delete[] tempArray;
}
