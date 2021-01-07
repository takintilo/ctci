#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct Heap Heap;
struct Heap {
  int *data;
  int capacity;
  int size;
};

Heap *createHeap() {
  Heap *newHeap = (Heap *)(malloc(sizeof(Heap)));
  int *heapData = (int *)(malloc(sizeof(int) * INITIAL_CAPACITY));
  newHeap->data = heapData;
  newHeap->capacity = INITIAL_CAPACITY;
  newHeap->size = 0;

  return newHeap;
}

void ensureExtraCapacity(Heap *heap) {
  if (heap->size == heap->capacity) {
    int newCapacity = heap->capacity * 2;
    int *newHeapData = (int *)(malloc(sizeof(int) * newCapacity));
    // copy old data to new array
    for (int i = 0; i < heap->capacity; ++i) {
      newHeapData[i] = heap->data[i];
    }
    // update heap data reference
    free(heap->data);
    heap->data = newHeapData;
    // update capacity
    heap->capacity = newCapacity;
  }
}

void swap(Heap *heap, int ind1, int ind2) {
  int temp = heap->data[ind1];
  heap->data[ind1] = heap->data[ind2];
  heap->data[ind2] = temp;
}

int getParentIndex(int index) { return (int)(index - 1) / 2; }

int getLeftChildIndex(int index) { return index * 2 + 1; }

int getRightChildIndex(int index) { return index * 2 + 2; }

bool hasLeftChild(Heap *heap, int index) { return index * 2 + 1 < heap->size; }

bool hasRightChild(Heap *heap, int index) { return index * 2 + 2 < heap->size; }

int getParent(Heap *heap, int index) {
  return heap->data[getParentIndex(index)];
}

int getLeftChild(Heap *heap, int index) {
  return heap->data[getLeftChildIndex(index)];
}

int getRightChild(Heap *heap, int index) {
  return heap->data[getRightChildIndex(index)];
}

void percolateUp(Heap *heap) {
  int currentIndex = heap->size - 1; // start with last element
  while (currentIndex > 0) {         // if we reach root, we're done
    int parentIndex = getParentIndex(currentIndex);
    if (getParent(heap, currentIndex) > heap->data[currentIndex]) {
      swap(heap, parentIndex, currentIndex);
      currentIndex = parentIndex;
    } else {
      break;
    }
  }
}

void percolateDown(Heap *heap) {
  int currentIndex = 0; // start at root of tree
  while (hasLeftChild(heap, currentIndex)) {
    int swapIndex;
    int lesserChild;
    int leftChild = getLeftChild(heap, currentIndex);
    if (hasRightChild(heap, currentIndex)) {
      int rightChild = getRightChild(heap, currentIndex);
      if (leftChild < rightChild) {
        lesserChild = leftChild;
        swapIndex = getLeftChildIndex(currentIndex);
      } else {
        lesserChild = rightChild;
        swapIndex = getRightChildIndex(currentIndex);
      }
    } else {
      lesserChild = leftChild;
      swapIndex = getLeftChildIndex(currentIndex);
    }
    if (heap->data[currentIndex] > lesserChild) {
      swap(heap, currentIndex, swapIndex);
      currentIndex = swapIndex;
    } else {
      break;
    }
  }
}

void insert(Heap *heap, int data) {
  ensureExtraCapacity(heap);
  heap->data[heap->size] = data;
  heap->size++;
  percolateUp(heap);
}

int peek(Heap *heap, int *result) {
  if (heap->size > 0) {
    *result = heap->data[0];
    return 0;
  }
  return 1;
}

int poll(Heap *heap, int *result) {
  if (heap->size > 0) {
    *result = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--; // decrementing size is enough to "delete"
    percolateDown(heap);
    return 0;
  }
  return 1;
}

int main() {
  Heap *heap = createHeap();
  insert(heap, 1);
  insert(heap, 10);
  insert(heap, 3);
  insert(heap, 2);
  insert(heap, 6);
  insert(heap, 8);
  insert(heap, 9);
  insert(heap, 7);
  insert(heap, 4);
  insert(heap, 5);

  int result;
  for (int i = 0; i < 10; ++i) {
    poll(heap, &result);
    printf("%d ", result);
  }

  return 0;
}
