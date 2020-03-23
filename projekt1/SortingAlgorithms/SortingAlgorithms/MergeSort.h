#pragma once

template <typename T>
void merge(T* array, const int left, const int middle, const int right, const bool isAscending)
{
	int size = right - left + 1;
	T* tempArray = new T[size];
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

template <typename T>
void mergeSort(T* array, const int left, const int right, const bool isAscending)
{
	if (right > left)
	{
		int middle = (right + left) / 2;
		mergeSort(array, left, middle, isAscending);
		mergeSort(array, middle + 1, right, isAscending);
		merge(array, left, middle, right, isAscending);
	}
}

template <typename T>
void mergeSort(T* array, const int size, const bool isAscending = true)
{
	mergeSort(array, 0, size - 1, isAscending);
}
