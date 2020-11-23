#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4

void generateCode(int count, int n, char **matrix);

int main(void)
{
    char **matrix = malloc(pow(2, N) * sizeof(char *));
    for(int i = 0; i < pow(2, N); ++i)
        matrix[i] = malloc(N * sizeof(char));
    
    matrix[0][0] = 0;
    matrix[1][0] = 1;

    generateCode(1, N, matrix);

    for(int i = 0; i < pow(2, N); ++i)
    {
        for(int b = (N - 1); b >= 0; --b)
            printf("%d", matrix[i][b]);
        
        printf("\n");
    }

    for(int i = 0; i < pow(2, N); ++i)
        free(matrix[i]);
    free(matrix);
}

void generateCode(int count, int n, char **matrix)
{
    if(count >= n)
        return;
    
    int base = pow(2, count);
    int last = base - 1;
    
    for(int i = 0; i < base; ++i)
    {
        for(int b = 0; b < count; ++b)
            matrix[base + i][b] = matrix[last - i][b];
        
        matrix[base + i][count] = 1;
        matrix[last - i][count] = 0;
    }

    generateCode((count + 1), n, matrix);
}