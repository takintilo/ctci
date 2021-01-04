#include <stdio.h>
#include <stdlib.h>

struct Node {
  struct Node *prev;
  struct Node *next;
  int data;
};

struct Node *head = NULL;
struct Node *tail = NULL;

void printList() {
  struct Node *curr = head;

  printf("HEAD --> ");
  while (curr != NULL) {
    printf("%d --> ", curr->data);
    curr = curr->next;
  }
  printf("TAIL\n");
}

void prepend(int data) {
  // create new node
  struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));

  newNode->prev = NULL;
  newNode->next = head;
  newNode->data = data;

  // set tail if this is first node being added
  if (tail == NULL) {
    tail = newNode;
  } else {
    // update old head's prev
    head->prev = newNode;
  }

  // update head ptr
  head = newNode;
}

void append(int data) {
  // create new node
  struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));

  newNode->prev = tail;
  newNode->next = NULL;
  newNode->data = data;

  // set head if this is first node being added
  if (head == NULL) {
    head = newNode;
  } else {
    // update old tail's next
    tail->next = newNode;
  }

  // update tail ptr
  tail = newNode;
}

int popFront(int *result) {
  if (head != NULL) {
    *result = head->data;
    struct Node *oldHead = head;
    // if only one node in list need to change tail too
    if (head == tail) {
      tail = NULL;
      head = NULL;
    } else {
      head = head->next;
      head->prev = NULL;
    }
    free(oldHead);
    return 0;
  } else {
    return 1;
  }
}

int popBack(int *result) {
  if (head != NULL) {
    *result = tail->data;
    struct Node *oldTail = tail;
    // if only one node in list need to change head too
    if (head == tail) {
      tail = NULL;
      head = NULL;
    } else {
      tail = tail->prev;
      tail->next = NULL;
    }
    free(oldTail);
    return 0;
  } else {
    return 1;
  }
}

int getFront(int *result) {
  if (head != NULL) {
    *result = head->data;
    return 0;
  } else {
    return 1;
  }
}

int getBack(int *result) {
  if (tail != NULL) {
    *result = tail->data;
    return 0;
  } else {
    return 1;
  }
}

struct Node *getNode(int data) {
  if (head == NULL) {
    return NULL;
  }
  struct Node *curr = head;
  while (curr != NULL) {
    if (curr->data == data) {
      return curr;
    }
    curr = curr->next;
  }
}

void deleteData(int data) {
  if (head != NULL) { // only proceed if list non-empty
    // special cases if data at head or tail (must update head and/or tail)
    // only one node in list and it contains data
    if (head->data == data && head == tail) {
      free(head);
      head = NULL;
      tail = NULL;
    } else if (head->data == data) { // data stored in head
      struct Node *oldHead = head;   // store old head so we can free it
      head = head->next;             // update head
      // update new head's prev
      head->prev = NULL;
      free(oldHead);
    } else if (tail->data == data) { // data stored in tail
      struct Node *oldTail = tail;   // store old tail so we can free it
      tail = tail->prev;             // update tail
      tail->next = NULL;             // update new tail's next
      free(oldTail);
    } else {
      // work from head to tail
      struct Node *curr = head;
      while (curr != NULL) {
        if (curr->data == data) {
          struct Node *prevNode = curr->prev;
          struct Node *nextNode = curr->next;
          // excise curr
          prevNode->next = nextNode;
          nextNode->prev = prevNode;
          free(curr);
          break;
        }
        curr = curr->next;
      }
    }
  }
}

void deleteNode(struct Node *node) {
  if (head == node && head == tail) { // node is only node in list
    free(head);
    head = NULL;
    tail = NULL;
  } else if (head == node) { // node is head
    struct Node *newHead = head->next;
    newHead->prev = NULL;
    head = newHead;
    free(node);
  } else if (tail == node) { // node is tail
    struct Node *newTail = tail->prev;
    newTail->next = NULL;
    tail = newTail;
    free(node);
  } else {
    struct Node *prevNode = node->prev;
    struct Node *nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    free(node);
  }
}

int main() {
  append(4);
  append(6);
  append(8);
  printList();
  prepend(2);
  prepend(0);
  printList();

  printf("Getting front and back data\n");
  int front;
  int back;
  getFront(&front);
  getBack(&back);
  printf("Front: %d\n", front);
  printf("Back:  %d\n", back);
  printList();

  printf("Popping front and back\n");
  front = -1;
  back = -1;
  popFront(&front);
  popBack(&back);
  printf("Front: %d\n", front);
  printf("Back:  %d\n", back);
  printList();

  printf("Adding 8 and 10\n");
  append(8);
  append(10);
  printList();

  printf("Deleting 2, 6, 10\n");
  deleteData(2);
  deleteData(6);
  deleteData(10);
  printList();

  printf("Adding 12, 14, 16\n");
  append(12);
  append(14);
  append(16);
  printList();

  printf("Deleting head, tail, and node containing 12\n");
  struct Node *toDelete = getNode(12);
  deleteNode(head);
  deleteNode(tail);
  deleteNode(toDelete);
  printList();

  return 0;
}
