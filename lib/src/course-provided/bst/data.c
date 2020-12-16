#include "dataStruct.h"

static int (* compareCallback)(data_t one, data_t two) = NULL;
static int (* readCallback)(FILE *file, data_t *data) = NULL;
static void (* writeCallback)(FILE *file, data_t data) = NULL;

void BSTinitialzieCallbacks(int (* cmp)(data_t, data_t), int (* read)(FILE *, data_t *), void (* write)(FILE *, data_t))
{
    compareCallback = cmp;
    readCallback = read;
    writeCallback = write;
}

int readData (FILE *fp, data_t *data)
{
  if(readCallback != NULL)
    return readCallback(fp, data);
  else
  {
    fprintf(stderr, "ERROR: An attempt has been made to call an uninitialzed callback!\n");
    exit(1);
  }
}

void writeData (FILE *fp, data_t data)
{
  if(writeCallback != NULL)
    writeCallback(fp, data);
  else
  {
    fprintf(stderr, "ERROR: An attempt has been made to call an uninitialzed callback!\n");
    exit(1);
  }
}

int compare (data_t d1, data_t d2)
{
  if(compareCallback != NULL)
    return compareCallback(d1, d2);
  else
  {
    fprintf(stderr, "ERROR: An attempt has been made to call an uninitialzed callback!\n");
    exit(1);
  }
}
