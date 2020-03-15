#pragma once
#include "Utility.h"

template <typename T>
void siftDown(T* array, int size, int currentIndex)
{
	int rightChildIndex = currentIndex * 2 + 2;
	int leftChildIndex = currentIndex * 2 + 1;
	int biggestNodeIndex = currentIndex;
	if (rightChildIndex < size && array[rightChildIndex] > array[currentIndex])
		biggestNodeIndex = rightChildIndex;
	if (leftChildIndex < size && array[leftChildIndex] > array[biggestNodeIndex])
		biggestNodeIndex = leftChildIndex;
	if (biggestNodeIndex != currentIndex)
	{
		swap(array, biggestNodeIndex, currentIndex);
		siftDown(array, size, biggestNodeIndex);
	}
}

template <typename T>
void buildMaxHeap(T* array, int size)
{
	int startIndex = size / 2 - 1;
	for (int currentNode = startIndex; currentNode >= 0; currentNode--)
		siftDown(array, size, currentNode);
}

template <typename T>
void heapSort(T* array, int size)
{
	buildMaxHeap(array, size);
	while (size > 0)
	{
		swap(array, 0, size - 1);
		size--;
		siftDown(array, size, 0);
	}
}

template <typename T>
void introSort(T* array, const int size, const int left, const int right, const bool isAscending)
{
	if ((right - left + 1) >= 9)
	{
		T pivot = partition(array, size, left, right, isAscending);
		introSort(array, size, left, pivot - 1, isAscending);
		introSort(array, size, pivot + 1, right, isAscending);
	}
	else
		heapSort(array + left, right - left + 1);
}

template <typename T>
void introSort(T* array, int size, const bool isAscending = true)
{
	introSort(array, size, 0, size - 1, true);
}

