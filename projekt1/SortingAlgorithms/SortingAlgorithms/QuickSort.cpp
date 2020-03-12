#include "QuickSort.h"
#include "Utility.h"

void quickSort(int* array, const int size, const bool isAscending)
{
	quickSort(array, size, 0, size - 1, isAscending);
}

void quickSort(int* array, const int size, const int left, const int right, const bool isAscending)
{
	if (left < right)
	{
		int pivot = partition(array, size, left, right, isAscending);
		quickSort(array, size, left, pivot - 1, isAscending);
		quickSort(array, size, pivot + 1, right, isAscending);
	}
}

int partition(int* array, const int size, const int left, const int right, const bool isAscending)
{
	int pivotIndex = choosePivot(left, right);
	int pivotValue = array[pivotIndex];
	int currentPosition = left;
	swap(array, pivotIndex, right);
	for (int i = left; i < right; i++)
	{
		if (isAscending)
		{
			if (array[i] <= pivotValue)
			{
				swap(array, currentPosition, i);
				currentPosition++;
			}
		}
		else
		{
			if (array[i] > pivotValue)
			{
				swap(array, currentPosition, i);
				currentPosition++;
			}
		}
	}
	swap(array, currentPosition, right);
	return currentPosition;
}

int choosePivot(const int left, const int right)
{
	return (left + (right - left) / 2);
}
