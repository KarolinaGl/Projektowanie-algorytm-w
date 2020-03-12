#pragma once

int* generateRandomArray(const int size, const int lowerBound = 1, const int upperBound = 10);

void printArray(const int* array, const int size);

void swap(int* array, const int firstIndex, const int SecondIndex);

bool isSorted(const int* array, const int size, const bool isAscending = true);