#include "QuickSort.h"

void quickSort(int* array, const int size)
{
	quickSort(array, size, 0, size - 1);
}

void quickSort(int* array, const int size, const int left, const int right)
{
	if (left < right)
	{
		int pivot = partition(array, size, left, right);
		quickSort(array, size, left, pivot - 1);
		quickSort(array, size, pivot + 1, right);
	}
}

int partition(int* array, const int size, const int left, const int right)
{
	int pivotIndex = choosePivot(left, right);
	int pivotValue = array[pivotIndex];
	int currentPosition = left;
	swap(array, pivotIndex, right);
	for (int i = left; i < right; i++)
	{
		if (array[i] < pivotValue)
		{
			swap(array, currentPosition, i);
			currentPosition++;
		}
	}
	swap(array, currentPosition, right);
	return currentPosition;
}

int choosePivot(const int left, const int right)
{
	return (left + (right - left) / 2);
}

void swap(int* array, const int firstIndex, const int SecondIndex)
{
	int temp = array[firstIndex];
	array[firstIndex] = array[SecondIndex];
	array[SecondIndex] = temp;
}

