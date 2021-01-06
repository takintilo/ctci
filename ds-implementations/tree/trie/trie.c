#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Node {
  struct Node *children[ALPHABET_SIZE];
  bool isCompleteWord;
};

int char_to_index(char c) { return (int)c - (int)'a'; }

struct Node *createNode() {
  struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));
  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    newNode->children[i] = NULL;
  }
  newNode->isCompleteWord = false;

  return newNode;
}

void insert(struct Node *root, char *word) {
  int i;
  struct Node *curr = root;
  int length = strlen(word);
  int letterIndex;
  for (i = 0; i < length; ++i) {
    letterIndex = char_to_index(word[i]);
    if (curr->children[letterIndex] == NULL) {
      curr->children[letterIndex] = createNode();
    }
    curr = curr->children[letterIndex];
  }
  curr->isCompleteWord = true;
}

bool search(struct Node *root, char *word) {
  int i;
  struct Node *curr = root;
  int length = strlen(word);
  int letterIndex;
  for (i = 0; i < length; ++i) {
    // if curr is null word doesn't exist
    if (curr == NULL) {
      return false;
    }
    letterIndex = char_to_index(word[i]);
    curr = curr->children[letterIndex];
  }

  return (curr != NULL && curr->isCompleteWord);
}

bool startsWith(struct Node *root, char *prefix) {
  int i;
  struct Node *curr = root;
  int length = strlen(prefix);
  int letterIndex;
  for (i = 0; i < length; ++i) {
    if (curr == NULL) {
      return false;
    }
    letterIndex = char_to_index(prefix[i]);
    curr = curr->children[letterIndex];
  }

  return curr != NULL;
}

void trieFree(struct Node *root) {
  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (root->children[i]) {
      trieFree(root->children[i]);
    }
  }
  free(root);
}

int main() {
  struct Node *root = createNode();

  insert(root, "hello");
  insert(root, "he");
  insert(root, "hell");
  insert(root, "trie");
  insert(root, "tries");
  insert(root, "they");
  insert(root, "them");
  insert(root, "their");
  insert(root, "there");

  printf("Is \"hello\" in trie?\n");
  printf("%d\n\n", search(root, "hello"));

  printf("Is \"them\" in trie?\n");
  printf("%d\n\n", search(root, "them"));

  printf("Is \"the\" in trie?\n");
  printf("%d\n\n", search(root, "the"));

  printf("Is there a word beginning with \"the\" in trie?\n");
  printf("%d\n\n", startsWith(root, "the"));

  printf("Freeing trie\n");
  trieFree(root);

  return 0;
}
