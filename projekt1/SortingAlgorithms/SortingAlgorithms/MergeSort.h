#pragma once

void mergeSort(int* array, const int size, const bool isAscending = true);

void mergeSort(int* array, const int left, const int right, const bool isAscending);

void merge(int* array, const int left, const int middle, const int right, const bool isAscending);