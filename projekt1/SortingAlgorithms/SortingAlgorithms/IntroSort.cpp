#include "IntroSort.h"
#include "Utility.h"

void introSort(int* array, int size)
{
	buildMaxHeap(array, size);
	while (size > 0)
	{
		swapValues(array, 0, size - 1);
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
		swapValues(array, biggestNodeIndex, currentIndex);
		siftDown(array, size, biggestNodeIndex);
	}
}

void swapValues(int* array, const int firstIndex, const int SecondIndex)
{
	int temp = array[firstIndex];
	array[firstIndex] = array[SecondIndex];
	array[SecondIndex] = temp;
}