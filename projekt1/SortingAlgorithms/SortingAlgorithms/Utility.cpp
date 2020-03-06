#include "Utility.h"
#include <iostream>

void printArray(const int* array, const int size)
{
	for (int i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}