#pragma once
#include <iostream>
#include <random>

void randomFill(int* array, const int size, const int lowerBound = -100000000, const int upperBound = 100000000)
{
	int range = upperBound - lowerBound + 1;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(0, range);
	for (int i = 0; i < size; i++)
		array[i] = distribution(generator) + lowerBound;
}

int* generateRandomArray(const int size, const int lowerBound = -100000000, const int upperBound = 100000000)
{
	int* array = new int[size];
	randomFill(array, size, lowerBound, upperBound);
	return array;
}

template <typename T>
void printArray(const T* array, const int size)
{
	for (int i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void swap(T* array, const int firstIndex, const int SecondIndex)
{
	T temp = array[firstIndex];
	array[firstIndex] = array[SecondIndex];
	array[SecondIndex] = temp;
}

template <typename T>
bool isSorted(const T* array, const int size, const bool isAscending = true)
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

template<typename T>
void sortInPercent(T* array, const int size, double percent)
{
	if (percent == 100)
		std::sort(array, array + size, std::greater<T>());
	else
		std::sort(array, array + (int)((size * percent) / 100));
}
