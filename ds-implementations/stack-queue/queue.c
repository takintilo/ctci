#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  Node *next;
  int data;
};

Node *head = NULL;
Node *tail = NULL;

bool isEmpty() { return (head == NULL); }

void push(int data) {
  // create new node
  Node *newNode = (Node *)(malloc(sizeof(Node)));
  newNode->next = NULL;
  newNode->data = data;
  // update tail
  // if list nonempty must update old tail's next
  if (head) {
    tail->next = newNode;
  } else { // otherwise, must update head
    head = newNode;
  }
  tail = newNode;
}

int pop(int *result) {
  if (head) {
    Node *oldHead = head;
    *result = head->data;
    // update head
    head = head->next;
    // if only one item in list, must update tail
    if (oldHead == tail) {
      tail = head; // = NULL
    }
    free(oldHead);

    return 0;
  }

  return 1;
}

int peek(int *result) {
  if (head) {
    *result = head->data;

    return 0;
  }

  return 1;
}

void printQueue() {
  Node *curr = head;
  while (curr) {
    printf("%d ", curr->data);
    curr = curr->next;
  }
  printf("\n");
}

int main() {
  push(5);
  push(6);
  push(7);
  push(8);
  push(9);
  push(10);
  printQueue();

  int frontOfQueue;
  if (!peek(&frontOfQueue)) {
    printf("Front of queue: %d\n", frontOfQueue);
  }

  int arr[6];
  // populate arr and print stack
  for (int i = 0; i < 6; ++i) {
    pop(&arr[i]);
    printQueue();
  }
  // print contents of arr
  for (int i = 0; i < 6; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // assert stack empty
  if (isEmpty()) {
    printf("Queue is empty\n");
  }

  return 0;
}
