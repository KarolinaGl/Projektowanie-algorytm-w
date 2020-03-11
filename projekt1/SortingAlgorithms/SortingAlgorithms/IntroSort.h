#pragma once

void introSort(int* array, int size);

void introSort(int* array, const int size, const int left, const int right, const bool isAscending);

void heapSort(int* array, int size);

void buildMaxHeap(int* array, int size);

void siftDown(int* array, int size, int currentIndex);
