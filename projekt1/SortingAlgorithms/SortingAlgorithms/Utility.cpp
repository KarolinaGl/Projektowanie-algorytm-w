#include "Utility.h"
#include <iostream>
#include <random>

int* generateRandomArray(const int size, const int lowerBound, const int upperBound)
{
	int* array = new int[size];
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lowerBound, upperBound);
	for (int i = 0; i < size; i++)
		array[i] = dist(rng);
	return array;
}

void printArray(const int* array, const int size)
{
	for (int i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

void swap(int* array, const int firstIndex, const int SecondIndex)
{
	int temp = array[firstIndex];
	array[firstIndex] = array[SecondIndex];
	array[SecondIndex] = temp;
}


bool isSorted(const int* array, const int size, const bool isAscending)
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
