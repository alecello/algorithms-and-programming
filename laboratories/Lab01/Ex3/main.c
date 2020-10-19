#include <stdio.h>
#include <math.h>

#define C 5
#define R 3

int power(int);
int factorial(int);

int main(void)
{
    int m1[R][C];
    int m2[R][C];

    for(int i = 0; i < R; ++i)
        for(int j = 0; j < C; ++j)
        {
            printf("m1[%d][%d]: ", i, j);
            scanf("%d", &m1[i][j]);
        }
    
    for(int i = 0; i < R; ++i)
        for(int j = 0; j < C; ++j)
            if(m1[i][j] == 0)
                m2[i][j] = 0;
            else if(m1[i][j] > 0)
                m2[i][j] = power(m1[i][j]);
            else
                m2[i][j] = factorial(m1[i][j]);
    
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < C; ++j)
            printf("%d ", m2[i][j]);
        
        printf("\n");
    }

    return 0;
}

int power(int input)
{
    int i = 1;

    while((int) pow(10, i) <= input)
        ++i;
    
    return pow(10, i);
}

int factorial(int input)
{
    int result = 1;

    for(int i = 2; i <= -input; ++i)
        result *= i;

    return result;
}