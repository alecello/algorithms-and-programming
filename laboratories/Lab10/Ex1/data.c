#include "data.h"

int readData (FILE *fp, data_t data)
{
  int r = fscanf (fp, "%d %s %s %s %s %d", &(data->registerNumber), data->surname, data->name, data->bdate, data->program, &(data->enrollmentYear));

  return r;
}

void writeData (FILE *fp, data_t data)
{
  fprintf(fp, "%d %s %s %s %s %d\n", data->registerNumber, data->surname, data->name, data->bdate, data->program, data->enrollmentYear);
}

int compareByName(data_t d1, data_t d2)
{
  int s = strcmp(d1->surname, d2->surname);
  int n = strcmp(d1->name, d2->name);

  if(s != 0) return s; else return n;
}

int compareByNumber(data_t d1, data_t d2)
{
  return d1->registerNumber - d2->registerNumber;
}
