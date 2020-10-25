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

    int sup = (SIZE - 1);   // Supremum of the array (last position to swap)
    int last = (SIZE - 1);  // Last unsorted element in the array (position of last swap)
    while(sup > 0)
    {
        for(int i = 0; i < sup; ++i)
            if(values[i] > values[i+1])
            {
                int tmp = values[i+1];
                values[i+1] = values[i];
                values[i] = tmp;

                last = i;
            }

        sup = last;
    }

    printf("\n\n");

    for(int i = 0; i < SIZE; ++i)
        printf("%d ", values[i]);

    printf("\n");
    return 0;
}