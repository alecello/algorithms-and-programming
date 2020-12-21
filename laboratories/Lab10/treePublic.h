#ifndef _TREE_PUBLIC_INCLUDED
  #define _TREE_PUBLIC_INCLUDED

  #include "data.h"

  #define PREORDER  -1
  #define INORDER    0
  #define POSTORDER  1

  #define BYNAME 0
  #define BYRNUM 1

  typedef struct node node_t;

  data_t   getData (node_t *);
  node_t * createEmptyTree ();
  node_t * readTree(FILE *);
  node_t * search(node_t *, data_t, int);
  void     writeTree(FILE *, node_t *, int, int);
  void     freeTree(node_t *);
#endif

