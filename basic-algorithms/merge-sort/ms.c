#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

void mergeRemainder(int destIndex, int sourceIndex, int sourceEnd, int *arr,
                    int *tempArr) {
  while (sourceIndex <= sourceEnd) {
    tempArr[destIndex++] = arr[sourceIndex++];
  }
}

void mergeHalves(int leftStart, int leftEnd, int rightStart, int rightEnd,
                 int *arr, int *tempArr) {
  int leftIndex = leftStart;
  int rightIndex = rightStart;
  int tempIndex = leftStart;
  while (leftIndex <= leftEnd && rightIndex <= rightEnd) {
    if (arr[leftIndex] < arr[rightIndex]) {
      tempArr[tempIndex++] = arr[leftIndex++];
    } else {
      tempArr[tempIndex++] = arr[rightIndex++];
    }
  }

  // copy over remaining elements. only one of these will do anything
  mergeRemainder(tempIndex, leftIndex, leftEnd, arr, tempArr);
  mergeRemainder(tempIndex, rightIndex, rightEnd, arr, tempArr);
  // copy temp to arr
  tempIndex = leftStart;
  while (tempIndex <= rightEnd) {
    arr[tempIndex] = tempArr[tempIndex];
    tempIndex++;
  }
}

void mergeSortRecursive(int start, int end, int *arr, int *tempArr) {
  if (start >= end)
    return;

  int leftStart = start;
  int leftEnd = (end - start) / 2 + start;
  int rightStart = leftEnd + 1;
  int rightEnd = end;

  mergeSortRecursive(leftStart, leftEnd, arr, tempArr);
  mergeSortRecursive(rightStart, rightEnd, arr, tempArr);
  mergeHalves(leftStart, leftEnd, rightStart, rightEnd, arr, tempArr);
}

void mergeSort(int *arr, int size) {
  int tempArr[size];

  mergeSortRecursive(0, size - 1, arr, tempArr);
}

int main() {
  int arr[SIZE] = {8, 6, 7, 5, 1, 9, 3, 2, 4};

  mergeSort(arr, SIZE);

  for (int i = 0; i < SIZE; ++i) {
    printf("%d ", arr[i]);
  }

  return 0;
}
