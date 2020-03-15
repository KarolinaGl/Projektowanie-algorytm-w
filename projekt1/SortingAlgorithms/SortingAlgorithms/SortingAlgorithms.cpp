#include <iostream>
#include "MergeSort.h"
#include "QuickSort.h"
#include "IntroSort.h"
#include "Utility.h"

const int lower = -20;
const int upper = 20;
const int arraySize = 20;
const bool isAscending = true;
int* array = generateRandomArray(arraySize, lower, upper);

void testMergeSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	mergeSort(array, arraySize, isAscending);
	std::cout << "Array after merge sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testQuickSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	quickSort(array, arraySize, isAscending);
	std::cout << "Array after quick sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testHeapSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	std::cout << "Array after heap sorting: ";
	heapSort(array, arraySize);
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

void testIntroSort(int* array, const int arraySize, const bool isAscending = true)
{
	std::cout << "Original array: ";
	printArray(array, arraySize);
	introSort(array, arraySize);
	std::cout << "Array after intro sorting: ";
	printArray(array, arraySize);
	std::cout << "Array was " << (isSorted(array, arraySize, isAscending) ? "" : "not ") << "sorted successfully" << std::endl;
	delete[] array;
}

int main()
{
	return 0;
}
