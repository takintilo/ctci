#include <stdio.h>
#include <stdlib.h>

struct Node {
  struct Node *left;
  struct Node *right;
  int data;
};

struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)(malloc(sizeof(struct Node)));
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->data = data;

  return newNode;
}

void insert(struct Node *root, int data) {

  if (data < root->data) {
    if (root->left == NULL) {
      struct Node *newNode = createNode(data);
      root->left = newNode;
    } else {
      insert(root->left, data);
    }
  } else {
    if (root->right == NULL) {
      struct Node *newNode = createNode(data);
      root->right = newNode;
    } else {
      insert(root->right, data);
    }
  }
}

struct Node *find(struct Node *root, int value) {
  if (root->data == value) {
    return root;
  }
  if (value < root->data) { // search left subtree
    if (root->left == NULL) {
      return NULL;
    } else {
      return find(root->left, value);
    }
  } else {
    if (root->right == NULL) {
      return NULL;
    } else {
      return find(root->right, value);
    }
  }
}

struct Node *getMin(struct Node *root) {
  struct Node *minNode = root;
  while (minNode->left != NULL) {
    minNode = minNode->left;
  }

  return minNode;
}

struct Node *getMax(struct Node *root) {
  struct Node *maxNode = root;
  while (maxNode->right != NULL) {
    maxNode = maxNode->right;
  }

  return maxNode;
}

struct Node *getSuccessor(struct Node *root, struct Node *node) {
  // case 1: node has right child
  // then successor is min of right subtree
  if (node->right != NULL) {
    return getMin(node->right);
  }
  // case 2: node has no right child
  // then need to return closest ancestor that has node in
  // left subtree
  struct Node *ancestor = root;
  struct Node *successor = NULL;

  while (ancestor != node) {
    if (node->data < ancestor->data) {
      successor = ancestor;
      ancestor = ancestor->left; // take one step down towards node
    } else {
      ancestor = ancestor->right;
    }
  }

  return successor;
}

struct Node *deleteData(struct Node *root, int data) {
  if (root == NULL) { // data not found or empty tree
    return NULL;
  } else if (data < root->data) {
    root->left = deleteData(root->left, data);
  } else if (data > root->data) {
    root->right = deleteData(root->right, data);
  } else {
    // case 1: node has 0 or 1 children
    if (root->left == NULL) {
      struct Node *newRoot = root->right;
      free(root);
      return (newRoot);
    } else if (root->right == NULL) {
      struct Node *newRoot = root->left;
      free(root);
      return (newRoot);
    }

    // case 2: node has 2 children
    struct Node *successor = getSuccessor(root, root);
    // copy successor's data to root (successor guaranteed to be
    // min of right subtree)
    root->data = successor->data;
    // delete original successor as it is now a duplicate
    root->right = deleteData(root->right, successor->data);
  }

  return root;
}

void printInOrder(struct Node *root) {
  if (root->left != NULL) {
    printInOrder(root->left);
  }
  if (root != NULL) { // in case of empty tree
    printf("%d ", root->data);
  }
  if (root->right != NULL) {
    printInOrder(root->right);
  }
}

int main() {
  struct Node *root = createNode(10);
  printInOrder(root);
  printf("\n");

  insert(root, 5);
  insert(root, 6);
  insert(root, 11);
  insert(root, 15);
  insert(root, 14);
  printInOrder(root);
  printf("\n");

  printf("%d\n", find(root, 14)->data);

  root = deleteData(root, 10);
  printInOrder(root);
  printf("\n");

  root = deleteData(root, 14);
  printInOrder(root);
  printf("\n");

  return 0;
}
