#ifndef _TREE_PUBLIC_INCLUDED
  #define _TREE_PUBLIC_INCLUDED

  #include "data.h"

  #define PREORDER  -1
  #define INORDER    0
  #define POSTORDER  1

  #define CONTINUE_TRAVERSAL 1
  #define STOP_TRAVERSAL 0

  typedef struct node node_t;

  data_t getData (node_t *);
  node_t *createEmptyTree ();
  node_t *readTree(FILE *);
  node_t *searchI (node_t *, data_t);
  node_t *searchR (node_t *, data_t);
  node_t *treeMinI (node_t *);
  node_t *treeMinR (node_t *);
  node_t *treeMaxI (node_t *);
  node_t *treeMaxR (node_t *);
  node_t *insert(node_t *, data_t);
  node_t *delete(node_t *, data_t);
  void writeTree(FILE *, node_t *, int);
  int visitTree (node_t *tree, int mode, int callback(node_t *node));
  void freeTree(node_t *);

  int getDistanceFromRoot(node_t *root, data_t key);
  int getRelativeDistance(node_t *root, data_t key1, data_t key2);

  // Accepts a tree and an array of three integers as argument. In the first element of the array it will place the count
  // of nodes that have no children. In the second slot the count of nodes that have one children. In the third the count
  // of nodes that have two children.
  void countNode(node_t *root, int *array);

  // Accepts an array. Will recurse up to the l-th level of the tree and save in the array the number of nodes for each
  // level.
  void countLevel(node_t *root, int *array, int l);

  // Will count total number of distinct paths leading to a leaf and the sum of all their lengths
  void countPath(node_t *root, int *np, int *length);
#endif