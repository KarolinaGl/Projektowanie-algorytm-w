#pragma once
#include <iostream>
#include <random>

int* generateRandomArray(const int size, const int lowerBound = 1, const int upperBound = 10)
{
	int* array = new int[size];
	int range = upperBound - lowerBound + 1;
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, range);
	for (int i = 0; i < size; i++)
		array[i] = dist(rng) + lowerBound;
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
