#include <stdio.h>

#define SIZE 20

void insertionSort(int start, int step, int *values, int dataSize);
int calculateNextCoefficient(int previous, int dataSize);

int main(void)
{
    int values[SIZE];

    for(int i = 0; i < SIZE; ++i)
    {
        printf("values[%d]: ", i);
        scanf("%d", &values[i]);
    }

    int h = -1;

    while((h = calculateNextCoefficient(h, SIZE)) != -1)
        for(int i = 0; i < h; ++i)
            insertionSort(i, h, values, SIZE);

    printf("\n\n");

    for(int i = 0; i < SIZE; ++i)
        printf("%d ", values[i]);

    printf("\n");
    return 0;
}

void insertionSort(int start, int step, int *values, int dataSize)
{    
    for(int i = (start + step); i < dataSize; i += step)
    {
        int j = (i - step);
        int t = values[i];

        while(j >= 0 && values[j] > t)
        {
            values[j + step] = values[j];
            j -= step;
        }
        
        values[j + step] = t;
    }
}

int calculateNextCoefficient(int previous, int dataSize)
{
    // If the previous coefficient was 1 we reached the end of the sequence
    if(previous == 1)
        return -1;

    int h = 1;

    while((3*h + 1) <= dataSize && (3*h + 1) != previous)
        h = (3*h + 1);

    printf("Using value of h: %d\n", h);
    return h;
}