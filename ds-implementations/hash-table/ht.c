#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
  char *string;
  int key;
} Node;

Node **createTable() {
  Node **tableArray = (Node **)(malloc(sizeof(Node *) * SIZE));
  for (int i = 0; i < SIZE; ++i) {
    tableArray[i] = NULL;
  }

  return tableArray;
}

int keyToIndex(int key) { return key % SIZE; }

void insert(Node **table, int key, char *string) {
  int index = keyToIndex(key);
  bool overwrite = false;
  for (int i = 0; i < SIZE; ++i) {
    if (table[index]) {
      // if this key is already in table, we'll overwrite it
      if (table[index]->key == key) {
        overwrite = true;
        break;
      } else {
        index = (index + 1) % SIZE;
      }
    } else {
      break;
    }
  }
  if (overwrite || !table[index]) {
    if (overwrite) {
      free(table[index]);
    }
    Node *newNode = (Node *)(malloc(sizeof(Node)));
    newNode->key = key;
    newNode->string = strdup(string);
    table[index] = newNode;
  } else {
    printf("cannot insert, table is full\n");
  }
}

char *search(Node **table, int key) {
  int index = keyToIndex(key);
  for (int i = 0; i < SIZE; ++i) {
    if (table[index] && table[index]->key == key) {
      return table[index]->string;
    }
    index = (index + 1) % SIZE;
  }

  return NULL;
}

void delete (Node **table, int key) {
  int index = keyToIndex(key);
  bool foundKey = false;
  for (int i = 0; i < SIZE; ++i) {
    if (table[index] && table[index]->key == key) {
      foundKey = true;
      break;
    }
    index = (index + 1) % SIZE;
  }
  if (foundKey) {
    free(table[index]);
    table[index] = NULL;
  }
}

int main() {
  Node **table = createTable();
  insert(table, 0, "apple");
  insert(table, 1, "banana");
  insert(table, 2, "orange");
  insert(table, 3, "tomato");
  insert(table, 4, "corn");
  insert(table, 5, "pomegranate");
  insert(table, 6, "plantain");
  insert(table, 7, "clementine");
  insert(table, 8, "grapefruit");
  insert(table, 9, "lemon");

  printf("item 0: %s\n", search(table, 0));
  printf("item 4: %s\n", search(table, 4));

  insert(table, 0, "lime");
  insert(table, 11, "mango");
  printf("new item 0: %s\n", search(table, 0));

  delete (table, 0);
  delete (table, 0);
  delete (table, 4);
  printf("item 4: %s\n", search(table, 4));

  return 0;
}
