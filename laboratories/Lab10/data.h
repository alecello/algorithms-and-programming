#ifndef _DATA_INCLUDED
#define _DATA_INCLUDED
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    #define MAXN 30
    #define MAXD 10
    #define MAXP  5

    struct student
    {
      char name[MAXN + 1];
      char surname[MAXN + 1];
      char bdate[MAXD + 1];
      char program[MAXP + 1];

      int enrollmentYear;
      int registerNumber;
    };

    typedef struct student * data_t;

    int readData (FILE *, data_t);
    void writeData (FILE *, data_t);

    int compareByName(data_t d1, data_t d2);
    int compareByNumber(data_t d1, data_t d2);
#endif
