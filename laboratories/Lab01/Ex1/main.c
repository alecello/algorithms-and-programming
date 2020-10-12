#include <stdio.h>

#define DIM 10

int main(void)
{
    int vector[DIM];
    int start,length = 0;

    for(int i = 0; i < DIM; ++i)
    {
        printf("vector[%d]: ", i);
        scanf("%d", &vector[i]);
    }

    for(int i = 0; i < DIM; ++i)
    {
        int len = 1;
        int cont = 1;

        for(int j = (i + 1); (j < DIM) && cont; ++j)
        {
            if(vector[j] >= vector[j - 1])
                ++len;
            else
                cont = 0;
        }

        if(len > length)
        {
            start = i;
            length = len;
        }
    }

    printf("Longest ascending sequence:\n");

    for(int i = start; i < start + length; ++i)
        printf("%d\n", vector[i]);
    
    return 0;
}