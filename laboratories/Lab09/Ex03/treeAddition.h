#ifndef _TREE_ADDITION_INCLUDED
    #define _TREE_ADDITION_INCLUDED
    #include "treePublic.h"

    // Count nodes with 0, 1, 2 children respectively in the 0th, 1st and 2nd element of the array
    void countNode(node_t *root, int *array);

    // Stores number of nodes in one tree level up to level (l - 1) in the i-th element of the array
    void countLevel(node_t *root, int *array, int l);

    // Count total number of paths from root to leaf and sum of lenghts for all those paths
    void countPath(node_t *root, int *np, int *length);

    // Calculates total distance between key1 and key2 in the tree
    int visit(node_t *root, int key1, int key2);
#endif