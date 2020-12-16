#include "treePrivate.h"

// Position 1: nodes with no child
// Position 2: nodes with one child
// Position 3: nodes with two children
void countNode(node_t *root, int *array)
{
    if(root == NULL)
        return;

    int children = 0;

    if(root->left != NULL)
    {
        ++children;
        countNode(root->left, array);
    }

    if(root->right != NULL)
    {
        ++children;
        countNode(root->right, array);
    }

    ++array[children];
}

void recurseLevel(node_t *root, int *array, int l, int count)
{
    if(count == l)
        return;

    ++array[count];

    if(root->left != NULL)
        recurseLevel(root->left, array, l, (count + 1));

    if(root->right != NULL)
        recurseLevel(root->right, array, l, (count + 1));
}

void countLevel(node_t *root, int *array, int l)
{
    recurseLevel(root, array, l, 0);
}

void recursePath(node_t *root, int *np, int *length, int count)
{
    if(root->left == NULL && root->right == NULL)
    {
        ++(*np);
        *(length) += count;

        return;
    }

    if(root->left != NULL)
        recursePath(root->left, np, length, (count + 1));

    if(root->right != NULL)
        recursePath(root->right, np, length, (count + 1));
}

void countPath(node_t *root, int *np, int *length)
{
    recursePath(root, np, length, 0);
}

node_t *recurSameSide(node_t *root, int key1, int key2, int count)
{
    if((key1 < root->val && key2 < root->val))
        return recurSameSide(root->left, key1, key2, (count + 1));

    if((key1 > root->val && key2 > root->val))
        return recurSameSide(root->right, key1, key2, (count + 1));

    return root;
}

int getDistance(node_t *root, int key, int count)
{
    if(root->val == key)
        return count;

    if(key < root->val)
        return getDistance(root->left, key, (count + 1));
    else
        return getDistance(root->right, key, (count + 1));
}

int visit(node_t *root, int key1, int key2)
{
    if(searchR(root, key1) == NULL || searchR(root, key2) == NULL)
        return -1;

    // First we recur until the point where the two keys are on two different sides of the root
    root = recurSameSide(root, key1, key2, 0);

    // Now calculating the distance between the two should be as easy as summin the two distances wrt new root.
    int distance1 = getDistance(root, key1, 0);
    int distance2 = getDistance(root, key2, 0);

    return distance1 + distance2;
}
