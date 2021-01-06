#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  Node *next;
  int data;
};

Node *head = NULL;

bool isEmpty() { return head == NULL; }

void push(int data) {
  // create new node
  Node *newNode = (Node *)(malloc(sizeof(Node)));
  newNode->next = head;
  newNode->data = data;
  // update head
  head = newNode;
}

int pop(int *result) {
  if (head) {
    Node *oldHead = head;
    *result = head->data;
    // update head
    head = head->next;
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

void printStack() {
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
  printStack();

  int topOfStack;
  if (!peek(&topOfStack)) {
    printf("Top of stack: %d\n", topOfStack);
  }

  int arr[6];
  // populate arr and print stack
  for (int i = 0; i < 6; ++i) {
    pop(&arr[i]);
    printStack();
  }
  // print contents of arr
  for (int i = 0; i < 6; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // assert stack empty
  if (isEmpty()) {
    printf("Stack is empty\n");
  }

  return 0;
}
