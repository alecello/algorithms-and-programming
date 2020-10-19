#include <stdio.h>

#define MAX 10

int main(void)
{
    int r1,c1,r2,c2 = 0;

    printf("Rows of M1: ");
    scanf("%d", &r1);
    printf("Cols of M1: ");
    scanf("%d", &c1);

    printf("Rows of M2: ");
    scanf("%d", &r2);
    printf("Cols of M2: ");
    scanf("%d", &c2);

    if(r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX || r1 < 1 || c1 < 1 || r2 < 1 || c2 < 1 || c1 != r2)
    {
        printf("ERROR: Invalid matrix dimensions.\n");
        return -1;
    }

    double m1[r1][c1], m2[r2][c2];

    for(int i = 0; i < r1; ++i)
        for(int j = 0; j < c1; ++j)
        {
            printf("M1[%d][%d]: ", i, j);
            scanf("%lf", &m1[i][j]);
        }

    for(int i = 0; i < r2; ++i)
        for(int j = 0; j < c2; ++j)
        {
            printf("M2[%d][%d]: ", i, j);
            scanf("%lf", &m2[i][j]);
        }

    double m3[r1][c2];

    for(int i = 0; i < r1; ++i)
        for(int j = 0; j < c2; ++j)
        {
            double sum = 0.0;

            for(int k = 0; k < c1; ++k)
                sum += m1[i][k] * m2[k][j];
            
            m3[i][j] = sum;
        }
    
    for(int i = 0; i < r1; ++i)
    {
        for(int j = 0; j < c2; ++j)
            printf("%lf ", m3[i][j]);
        
        printf("\n");
    }

    return 0;
}