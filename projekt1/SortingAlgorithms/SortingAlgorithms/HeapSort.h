#pragma once
#include "Utility.h"

template <typename T>
void siftDown(T* array, int size, int currentIndex, const bool isAscending)
{
	int rightChildIndex = currentIndex * 2 + 2;
	int leftChildIndex = currentIndex * 2 + 1;
	int biggestNodeIndex = currentIndex;
	int smallestNodeIndex = currentIndex;
	if (isAscending)
	{
		if (rightChildIndex < size && array[rightChildIndex] > array[currentIndex])
			biggestNodeIndex = rightChildIndex;
		if (leftChildIndex < size && array[leftChildIndex] > array[biggestNodeIndex])
			biggestNodeIndex = leftChildIndex;
		if (biggestNodeIndex != currentIndex)
		{
			swap(array, biggestNodeIndex, currentIndex);
			siftDown(array, size, biggestNodeIndex, isAscending);
		}
	}
	else
	{
		if (rightChildIndex < size && array[rightChildIndex] < array[currentIndex])
			smallestNodeIndex = rightChildIndex;
		if (leftChildIndex < size && array[leftChildIndex] < array[smallestNodeIndex])
			smallestNodeIndex = leftChildIndex;
		if (smallestNodeIndex != currentIndex)
		{
			swap(array, smallestNodeIndex, currentIndex);
			siftDown(array, size, smallestNodeIndex, isAscending);
		}
	}
}

template <typename T>
void buildHeap(T* array, int size, const bool isAscending)
{
	int startIndex = size / 2 - 1;
	for (int currentNode = startIndex; currentNode >= 0; currentNode--)
		siftDown(array, size, currentNode, isAscending);
}

template <typename T>
void heapSort(T* array, int size, const bool isAscending)
{
	buildHeap(array, size, isAscending);
	while (size > 0)
	{
		swap(array, 0, size - 1);
		size--;
		siftDown(array, size, 0, isAscending);
	}
}
