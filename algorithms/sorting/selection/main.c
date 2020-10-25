#include <stdio.h>

#define SIZE 10

int selectLowestValue(int *values, int from);

int main(void)
{
    int values[SIZE];

    for(int i = 0; i < SIZE; ++i)
    {
        printf("values[%d]: ", i);
        scanf("%d", &values[i]);
    }

    int sorted = 0;
    while(sorted < SIZE)
    {
        int index = selectLowestValue(values, sorted);
        int temp;

        temp = values[sorted];
        values[sorted] = values[index];
        values[index] = temp;

        ++sorted;

    }

    printf("\n\n");

    for(int i = 0; i < SIZE; ++i)
        printf("%d ", values[i]);

    printf("\n");
    return 0;
}

int selectLowestValue(int *values, int from)
{
    int minimum = values[from];
    int index = from;

    for(int i = from; i < SIZE; ++i)
        if(values[i] < minimum)
        {
            index = i;
            minimum = values[i];
        }

    return index;
}