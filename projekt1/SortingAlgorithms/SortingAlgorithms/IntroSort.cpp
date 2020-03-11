#include "IntroSort.h"
#include "QuickSort.h"
#include "Utility.h"

void introSort(int* array, int size)
{
	introSort(array, size, 0, size - 1, true);
}

void introSort(int* array, const int size, const int left, const int right, const bool isAscending)
{
	if ((right - left + 1) >= 9)
	{
		int pivot = partition(array, size, left, right, isAscending);
		introSort(array, size, left, pivot - 1, isAscending);
		introSort(array, size, pivot + 1, right, isAscending);
	}
	else
		heapSort(array + left, right - left + 1);
}

void heapSort(int* array, int size)
{
	buildMaxHeap(array, size);
	while (size > 0)
	{
		swap(array, 0, size - 1);
		size--;
		siftDown(array, size, 0);
	}
}

void buildMaxHeap(int* array, int size)
{
	int startIndex = size / 2 - 1;
	for (int currentNode = startIndex; currentNode >= 0; currentNode--)
		siftDown(array, size, currentNode);
}

void siftDown(int* array, int size, int currentIndex)
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
