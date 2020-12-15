#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "item.h"

struct item {
  char *name;
  data_t value;
};

static void (* itemShowCallback)(Item data) = NULL;
static Item (* itemScanCallback)() = NULL;
static Key (* keyScanCallback)() = NULL;

void STInitializeCallback(void (* show)(Item), Item (* itemScan)(void), Key (* keyScan)(void))
{
  itemShowCallback = show;
  itemScanCallback = itemScan;
  keyScanCallback = keyScan;
}

Item ITEMcreate(char *key, data_t value)
{
  if(strlen(key) > (MAXST - 1))
    return NULL;

  Item tmp = (Item) malloc(sizeof(struct item));
  if(tmp != NULL)
  {
    tmp->name = strdup(key);
    tmp->value = value;
  }

  return tmp;
}

Item ITEMscan ()
{
  if(itemScanCallback != NULL)
    return itemScanCallback();
  else
  {
    fprintf(stderr, "ERROR: An attempt has been made to call an uninitialzed callback!\n");
    exit(1);
  }
}

void ITEMshow (Item data)
{
  if(itemShowCallback != NULL)
    itemShowCallback(data);
  else
  {
    fprintf(stderr, "ERROR: An attempt has been made to call an uninitialzed callback!\n");
    exit(1);
  }
}

int ITEMcheckvoid(Item data) {
  Key k1, k2 = "";

  k1 = KEYget(data);
  if (KEYcompare(k1,k2)==0)
    return 1;
  else
    return 0;
}

Item ITEMsetvoid() {
  char name[MAXST] = "";

  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp != NULL) {
    tmp->name = strdup(name);
    tmp->value = NULL;
  }
  return tmp;
}

Key KEYscan() {
  if(keyScanCallback != NULL)
    return keyScanCallback();
  else
  {
    fprintf(stderr, "ERROR: An attempt has been made to call an uninitialzed callback!\n");
    exit(1);
  }
}

int  KEYcompare(Key k1, Key k2) {
  return strcmp(k1,k2);
}

Key KEYget(Item data) {
  return data->name;
}

data_t ITEMGetValue(Item i)
{
  return i->value;
}
