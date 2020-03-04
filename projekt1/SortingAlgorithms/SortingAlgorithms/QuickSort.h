#pragma once

void quickSort(int* array, const int size);

void quickSort(int* array, const int size, const int left, const int right);

int partition(int* array, const int size, const int left, const int right);

int choosePivot(const int left, const int right);

void swap(int* array, const int firstIndex, const int SecondIndex);