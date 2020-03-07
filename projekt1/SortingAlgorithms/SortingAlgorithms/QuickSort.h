#pragma once

void quickSort(int* array, const int size, const bool isAscending = true);

void quickSort(int* array, const int size, const int left, const int right, const bool isAscending = true);

int partition(int* array, const int size, const int left, const int right, const bool isAscending = true);

int choosePivot(const int left, const int right);
