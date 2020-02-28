#include <iostream>
#include <random>
#include "MergeSort.h"

void printArray(const int* array, const int size)
{
	for (int i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

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

int main()
{
	const int lower = 1;
	const int upper = 200;
	const int arraySize = 100;
	const bool isAscending = true;
	int* array = generateRandomArray(arraySize, lower, upper);
	std::cout << "Original array: ";
	printArray(array, arraySize);
	mergeSort(array, arraySize, isAscending);
	mergeSort(array, arraySize, !isAscending);
	std::cout << "Array after merge sorting: ";
	printArray(array, arraySize);
	std::cout << "Array is " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted" << std::endl;
	delete[] array;
	return 0;
}
