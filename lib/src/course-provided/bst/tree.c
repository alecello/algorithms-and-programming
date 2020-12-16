#include "treePrivate.h"

#define FIND 0

static node_t *myAlloc (void);

#if FIND
  static data_t findDeleteMax1 (node_t **);
#else
  static node_t *findDeleteMax2 (data_t *, node_t *);
#endif

data_t getData (node_t *node)
{
  return (node->val);
}

node_t *createEmptyTree (void)
{
  return (NULL);
}

node_t *treeMinI (node_t *rp)
{
  if (rp == NULL)
    return (rp);

  while (rp->left != NULL) {
    rp = rp->left;
  }

  return (rp);
}

node_t *treeMinR (node_t *rp)
{
  if (rp == NULL || rp->left==NULL)
    return (rp);

  return (treeMinR (rp->left));
}

node_t *treeMaxI (node_t *rp)
{
  if (rp == NULL)
    return (rp);

  while (rp->right != NULL) {
    rp = rp->right;
  }

  return (rp);
}

node_t *treeMaxR (node_t *rp)
{
  if (rp == NULL || rp->right==NULL)
    return (rp);

  return (treeMaxR (rp->right));
}

node_t *searchI (node_t *rp, data_t data)
{
  while (rp != NULL) {
    if (compare(rp->val, data) == 0)
      return (rp);

    if (compare(data, rp->val) < 0)
      rp = rp->left;
    else
      rp = rp->right;
  }

  return (NULL);
}

node_t *searchR (node_t *rp, data_t data)
{
  if (rp==NULL || compare(rp->val, data)==0)
    return (rp);

  if (compare(data, rp->val) < 0)
    return (searchR (rp->left, data));
  else
    return (searchR (rp->right, data));
}

node_t *insert (node_t *rp, data_t data)
{
  node_t *p;

  /* Empty Tree: Found Position */
  if (rp == NULL) {
    p = myAlloc();
    p->val = data;
    p->left = p->right = NULL;
    return (p);
  }

  /* Duplicated Element */
  if (compare(data, rp->val) == 0) {
    return (rp);
  }

  if (compare(data, rp->val) < 0) {
    /* Insert on the left */
    rp->left = insert (rp->left, data);
  } else {
    /* Insert on the right */
    rp->right = insert (rp->right, data);
  }

  return (rp);
}


node_t *readTree (FILE *fp)
{
  node_t *rp;
  data_t d;

  rp = createEmptyTree ();

  while (readData (fp, &d) != EOF) {
    rp = insert (rp, d);
  }

  return (rp);
}

void freeTree (node_t *rp)
{
  if (rp == NULL) {
    return;
  }

  freeTree (rp->left);
  freeTree (rp->right);
  free (rp);

  return;
}

void writeTree (FILE *fp, node_t *rp, int modo)
{
  if (rp == NULL) {
    return;
  }

  if (modo == PREORDER) {
    writeData (fp, rp->val);
  }

  writeTree (fp, rp->left, modo);

  if (modo == INORDER) {
    writeData(fp, rp->val);
  }

  writeTree (fp, rp->right, modo);

  if (modo == POSTORDER) {
    writeData(fp, rp->val);
  }

  return;
}

int visitTree(node_t *tree, int mode, int callback(node_t *node))
{
  if (tree == NULL)
    return CONTINUE_TRAVERSAL;

  if (mode == PREORDER)
    if(callback(tree) == STOP_TRAVERSAL)
      return STOP_TRAVERSAL;

  if(visitTree(tree->left, mode, callback) == STOP_TRAVERSAL)
    return STOP_TRAVERSAL;

  if (mode == INORDER)
    if(callback(tree) == STOP_TRAVERSAL)
      return STOP_TRAVERSAL;

  if(visitTree(tree->right, mode, callback) == STOP_TRAVERSAL)
    return STOP_TRAVERSAL;

  if (mode == POSTORDER)
    if(callback(tree) == STOP_TRAVERSAL)
      return STOP_TRAVERSAL;

  return CONTINUE_TRAVERSAL;
}


node_t *delete (node_t *rp, data_t data)
{
  node_t *p;

  /* Empty Tree */
  if (rp == NULL) {
    printf("Error: Unknown Data\n");
    return (rp);
  }

  if (compare (data, rp->val) < 0) {
    /* Delete on the left sub-treee Recursively */
    rp->left = delete (rp->left, data);
    return (rp);
  }

  if (compare(data, rp->val)> 0) {
    /* Delete on the rigth sub-treee Recursively */
    rp->right = delete (rp->right, data);
    return (rp);
  }

  /* Delete Current Note rp */
  p = rp;
  if (rp->right == NULL) {
    /* Empty Right Sub-Tree: Return Left Sub-Tree */
    rp = rp->left;
    free (p);
    return (rp);
  }

  if (rp->left == NULL) {
    /* Empty Left Sub-Tree: Return Right Sub-Tree */
    rp = rp->right;
    free (p);
    return rp;
  }

  /* Find Predecessor and Substitute */
  #if FIND
    rp->val = findDeleteMax1 (&(rp->left));
  #else
    {
      data_t val;

      rp->left = findDeleteMax2 (&val, rp->left);
      rp->val = val;
    }
  #endif

  return (rp);
}

static node_t *myAlloc (void)
{
  node_t *p;

  p = (node_t *)malloc(sizeof(node_t));
  if (p == NULL) {
    printf ("Allocation Error.\n");
    exit (1);
  }

  return (p);
}

#if FIND
  static data_t findDeleteMax1 (node_t **rpp)
  {
    node_t *p;
    data_t d;

    /* Find The Rigth-Most Node (max value) */
    while ((*rpp)->right != NULL)
      rpp = &((*rpp)->right);

    p = *rpp;
    d = p->val;
    *rpp = (*rpp)->left;
    free (p);

    return (d);
  }
#else
  static node_t *findDeleteMax2 (data_t *d, node_t *rp)
  {
    node_t *tmp;

    if (rp->right == NULL) {
      *d = rp->val;
      tmp = rp->left;
      free (rp);
      return (tmp);
    }

    rp->right = findDeleteMax2 (d, rp->right);
    return (rp);
  }
#endif

int recurseDistance(node_t *root, data_t key, int count)
{
  if(compare(root->val, key) == 0)
      return count;

  if(compare(root->val, key) > 0)
      return recurseDistance(root->left, key, (count + 1));
  else
      return recurseDistance(root->right, key, (count + 1));
}

int getDistanceFromRoot(node_t *root, data_t key)
{
  return recurseDistance(root, key, 0);
}

node_t *recurSameSide(node_t *root, data_t key1, data_t key2, int count)
{
    if((compare(key1, root->val) < 0 && compare(key2, root->val) < 0))
        return recurSameSide(root->left, key1, key2, (count + 1));

    if((compare(key1, root->val) > 0 && compare(key2, root->val) > 0))
        return recurSameSide(root->right, key1, key2, (count + 1));

    return root;
}

int getRelativeDistance(node_t *root, data_t key1, data_t key2)
{
    if(searchR(root, key1) == NULL || searchR(root, key2) == NULL)
        return -1;

    // First we recur until the point where the two keys are on two different sides of the root
    root = recurSameSide(root, key1, key2, 0);

    // Now calculating the distance between the two should be as easy as summin the two distances wrt new root.
    int distance1 = recurseDistance(root, key1, 0);
    int distance2 = recurseDistance(root, key2, 0);

    return distance1 + distance2;
}

// Accepts a tree and an array of three integers as argument. In the first element of the array it will place the count
// of nodes that have no children. In the second slot the count of nodes that have one children. In the third the count
// of nodes that have two children.
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

// Accepts an array. Will recurse up to the l-th level of the tree and save in the array the number of nodes for each
// level.
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

// Will count total number of distinct paths leading to a leaf and the sum of all their lengths
void countPath(node_t *root, int *np, int *length)
{
    recursePath(root, np, length, 0);
}
