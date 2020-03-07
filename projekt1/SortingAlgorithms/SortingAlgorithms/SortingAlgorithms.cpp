#include <iostream>
#include <random>
#include "MergeSort.h"
#include "QuickSort.h"
#include "IntroSort.h"
#include "Utility.h"

int* generateRandomArray(const int size, const int lowerBound = 1, const int upperBound = 10)
{
	int* array = new int[size];
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lowerBound, upperBound);
	for (int i = 0; i < size; i++)
		array[i] = dist(rng);
	return array;
}

bool isSorted(const int* array, const int size, const bool isAscending = true)
{
	if (isAscending)
	{
		for (int i = 0; i < size - 1; i++)
			if (array[i] > array[i + 1])
				return false;
		return true;
	}
	else
	{
		for (int i = 0; i < size - 1; i++)
			if (array[i] < array[i + 1])
				return false;
		return true;
	}
}

void testMergeSort()
{
	const int lower = 0;
	const int upper = 100;
	const int arraySize = 15;
	const bool isAscending = true;
	int* array = generateRandomArray(arraySize, lower, upper);
	std::cout << "Original array: ";
	printArray(array, arraySize);
	mergeSort(array, arraySize, isAscending);
	std::cout << "Array after merge sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testQuickSort()
{
	const int lower = 0;
	const int upper = 100;
	const int arraySize = 15;
	const bool isAscending = true;
	int* array = generateRandomArray(arraySize, lower, upper);
	std::cout << "Original array: ";
	printArray(array, arraySize);
	quickSort(array, arraySize, isAscending);
	std::cout << "Array after quick sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testHeapSort()
{
	const int lower = 0;
	const int upper = 100;
	const int arraySize = 15;
	const bool isAscending = true;
	int* array = generateRandomArray(arraySize, lower, upper);
	std::cout << "Original array: ";
	printArray(array, arraySize);
	std::cout << "Array after heapify: ";
	introSort(array, arraySize);
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

int main()
{
	return 0;
}
