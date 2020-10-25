#include <stdio.h>

#define SIZE 10

int main(void)
{
    int values[SIZE];

    for(int i = 0; i < SIZE; ++i)
    {
        printf("values[%d]: ", i);
        scanf("%d", &values[i]);
    }

    for(int i = 1; i < SIZE; ++i)
    {
        int j = (i - 1);
        int t = values[i];

        while(j >= 0 && values[j] > t)
        {
            values[j + 1] = values[j];
            --j;
        }

        values[j + 1] = t;
    }

    printf("\n\n");

    for(int i = 0; i < SIZE; ++i)
        printf("%d ", values[i]);
    
    printf("\n");
    return 0;
}