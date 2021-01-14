#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

void swap(int *arr, int index1, int index2) {
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}

int partition(int *arr, int pivot, int left, int right) {
  int leftIndex = left;
  int rightIndex = right;
  while (leftIndex < rightIndex) {
    while (arr[leftIndex] < pivot)
      leftIndex++;
    while (arr[rightIndex] > pivot)
      rightIndex--;
    if (arr[leftIndex] > arr[rightIndex])
      swap(arr, leftIndex, rightIndex);
  }

  return leftIndex;
}

void quickSortRecursive(int *arr, int left, int right) {
  if (left >= right)
    return;
  int pivot = arr[(right - left) / 2 + left]; // using middle as pivot
  int middle = partition(arr, pivot, left, right);
  quickSortRecursive(arr, left, middle);
  quickSortRecursive(arr, middle + 1, right);
}

void quickSort(int *arr, int size) { quickSortRecursive(arr, 0, size - 1); }

int main() {
  int arr[SIZE] = {8, 6, 7, 5, 1, 9, 3, 2, 4};

  quickSort(arr, SIZE);

  for (int i = 0; i < SIZE; ++i) {
    printf("%d ", arr[i]);
  }

  return 0;
}
