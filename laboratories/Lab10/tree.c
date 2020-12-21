#include "treePrivate.h"

static node_t *myAlloc(void);

data_t getData(node_t *node)
{
  return (node->val);
}

node_t *createEmptyTree(void)
{
  return (NULL);
}

node_t *searchByName(node_t *rp, data_t data)
{
  if (rp==NULL || compareByName(rp->val, data)==0)
    return (rp);

  if (compareByName(data, rp->val) < 0)
    return (searchByName (rp->left_name, data));
  else
    return (searchByName (rp->right_name, data));
}

node_t *searchByNumber(node_t *rp, data_t data)
{
  if (rp==NULL || compareByNumber(rp->val, data)==0)
    return (rp);

  if (compareByNumber(data, rp->val) < 0)
    return (searchByNumber (rp->left_number, data));
  else
    return (searchByNumber (rp->right_number, data));
}

node_t *search(node_t*rp, data_t data, int mode)
{
  if(mode == BYNAME)
    return searchByName(rp, data);
  else
    return searchByNumber(rp, data);
}

node_t *insertByName(node_t *rp, node_t *to_insert)
{
  /* Empty Tree: Found Position */
  if (rp == NULL)
    return to_insert;

  /* Perform insertion by name */
  if (compareByName(to_insert->val, rp->val) < 0)
    rp->left_name = insertByName(rp->left_name, to_insert);
  else
    rp->right_name = insertByName(rp->right_name, to_insert);

  return (rp);
}

node_t *insertByNumber(node_t *rp, node_t *to_insert)
{
  /* Empty Tree: Found Position */
  if (rp == NULL)
    return to_insert;

  /* Perform insertion by number */
  if (compareByNumber(to_insert->val, rp->val) < 0)
    rp->left_number = insertByNumber(rp->left_number, to_insert);
  else
    rp->right_number = insertByNumber(rp->right_number, to_insert);

  return (rp);
}

node_t *insert(node_t *rp, data_t data)
{
  node_t *p;
  p = myAlloc();
  p->val = malloc(sizeof(*(p->val)));
  memcpy(p->val, data, sizeof(*data));
  p->left_name = p->left_number = p->right_name = p->right_number = NULL;

  insertByName(rp, p);
  return insertByNumber(rp, p);
}

node_t *readTree(FILE *fp)
{
  node_t *rp;
  data_t d = malloc(sizeof(*d));

  rp = createEmptyTree();

  while (readData(fp, d) != EOF)
  {
    rp = insert(rp, d);
    printf("Inserting %d\n", d->registerNumber);
  }

  return (rp);
}

void freeTree(node_t *rp)
{
  if (rp == NULL)
    return;

  freeTree(rp->left_number);
  freeTree(rp->right_number);
  free(rp);

  return;
}

void writeTree(FILE *fp, node_t *rp, int order, int mode)
{
  if(rp == NULL)
    return;

  if(order == PREORDER)
    writeData(fp, rp->val);

  writeTree(fp, (mode == BYRNUM) ? rp->left_number : rp->left_name, order, mode);

  if(order == INORDER)
    writeData(fp, rp->val);

  writeTree(fp, (mode == BYRNUM) ? rp->right_number : rp->right_name, order, mode);

  if(order == POSTORDER)
    writeData(fp, rp->val);

  return;
}

static node_t *myAlloc(void)
{
  node_t *p;

  p = (node_t *)malloc(sizeof(node_t));
  if(p == NULL)
  {
    printf("Allocation Error.\n");
    exit(1);
  }

  return(p);
}
