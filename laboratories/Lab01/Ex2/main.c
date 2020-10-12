#include <stdio.h>

#define DIM 10

int main(void)
{
    int N1,N2 = 0;

    do
    {
        printf("Insert N1: ");
        scanf("%d", &N1);
    }
    while (N1 > DIM || N1 < 1);
    
    do
    {
        printf("Insert N2: ");
        scanf("%d", &N2);
    }
    while (N2 > DIM || N2 < 1);

    int V1[N1];
    float V2[N1];
    
    for(int i = 0; i < N1; ++i)
    {
        printf("V1[%d]: ", i);
        scanf("%d", &V1[i]);
    }

    for(int i = 0; i < N1; ++i)
    {
        int sum = 0;
        int count = 0;

        int min = (i - N2) >= 0 ? (i - N2) : 0;
        int max = (i + N2) < N1 ? (i + N2) : (N1 - 1);

        for(int j = min; j <= max; ++j)
        {
            sum += V1[j];
            ++count;
        }

        V2[i] = ((float) sum) / ((float) count);
    }

    printf("\n\n");

    for(int i = 0; i < N1; ++i)
    {
        printf("V2[%d]: %.2f\n", i, V2[i]);
    }

    return 0;
    
}