#include <stdio.h>
#include <stdlib.h>

#define NUM 3

int *merge(int *a, int *b, int *c, int na, int nb, int nc);

int main(void)
{
    int na = 4;
    int nb = 3;
    int nc = 2;

    int a[] = {1, 3, 5, 7};
    int b[] = {0, 2, 4};
    int c[] = {6, 8};

    int *result = merge(a, b, c, na, nb, nc);
    int size = na + nb + nc;

    for(int i = 0; i < size; ++i)
        printf("%d ", result[i]);
    printf("\n");

    free(result);
    return 0;
}

int *merge(int *a, int *b, int *c, int na, int nb, int nc)
{
    int size = na + nb + nc;
    int *result = calloc(size, sizeof(int));

    // Store the arrays in an array of pointer to use iterative constructs
    int *arrays[NUM] = { a,  b,  c};
    int indexes[NUM] = { 0,  0,  0};
    int  maxima[NUM] = {na, nb, nc};

    int ir = 0;
    while(ir < size)
    {
        int selector = -1;

        for(int i = 0; i < NUM; ++i)
            if(indexes[i] < maxima[i] && (selector < 0 || arrays[i][indexes[i]] < arrays[selector][indexes[selector]]))
                selector = i;

        result[ir++] = arrays[selector][indexes[selector]++];
    }

    return result;
}
