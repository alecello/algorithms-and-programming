#include <stdio.h>

#define DIM 10

int main(void)
{
    int vector[DIM];

    for(int i = 0; i < DIM; ++i)
    {
        printf("vector[%d]: ", i);
        scanf("%d", &vector[i]);
    }

    int length = 1;
    int maxLength = 0;
    int index = 0;

    for(int i = 1; i <= DIM; ++i)
    {
        if(i < DIM && vector[i] >= vector[i-1])
            ++length;
        else
        {
            if(length > maxLength)
            {
                maxLength = length;
                index = i - maxLength;
            }

            length = 0;
        }
    }

    printf("Longest ascending sequence (dimension = %d, index = %d):\n", maxLength, index);

    for(int i = index; i < index + maxLength; ++i)
        printf("%d\n", vector[i]);
    
    return 0;
}