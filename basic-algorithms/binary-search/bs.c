#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

int bs_iter(int *array, int length, int target, int *result) {
  int bottom = 0;
  int top = length - 1;
  int mid;

  while (bottom <= top) {
    mid = (top - bottom) / 2 + bottom;
    if (array[mid] == target) {
      *result = mid;
      return 0;
    } else if (array[mid] < target) {
      bottom = mid + 1;
    } else {
      top = mid - 1;
    }
  }

  return 1;
}

int bs_recur(int *array, int bottom, int top, int target, int *result) {
  int mid = (top - bottom) / 2 + bottom;
  if (array[mid] == target) {
    *result = mid;
    return 0;
  } else if (array[mid] < target) {
    bottom = mid + 1;
  } else {
    top = mid - 1;
  }
  if (bottom <= top) {
    return bs_recur(array, bottom, top, target, result);
  }

  return 1;
}

int bs(int *array, int length, int target, int *result) {
  int bottom = 0;
  int top = length - 1;
  if (top > 0) {
    return bs_recur(array, bottom, top, target, result);
  }
  return 1;
}

int main() {
  int arr[LENGTH] = {0, 3, 4, 6, 7, 9, 10, 11, 15, 20};
  int result;
  int result_iter;

  bs(arr, LENGTH, 3, &result);
  printf("3 is located at index %d\n\n", result);

  bs_iter(arr, LENGTH, 20, &result_iter);
  printf("20 is located at index %d\n\n", result_iter);

  int failure = bs(arr, LENGTH, 5, &result);
  if (failure) {
    printf("5 is not in array\n\n");
  }

  return 0;
}
