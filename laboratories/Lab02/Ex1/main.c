#include <stdio.h>

#define MAX 10

void readDim(int *row, int *col)
{
    printf("Rows: ");
    scanf("%d", row);
    printf("Cols: ");
    scanf("%d", col);
}

int checkDim(int r1, int c1, int r2, int c2)
{
    if(r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX || r1 < 1 || c1 < 1 || r2 < 1 || c2 < 1 || c1 != r2)
        return -1;
    else
        return 0;
}

void readMatrix(int r, int c, double matrix[][MAX])
{
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
        {
            printf("[%d][%d]: ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
}

void computeProduct(int r1, int c1, double m1[][MAX], int r2, int c2, double m2[][MAX], int r3, int c3, double m3[][MAX])
{
    for(int i = 0; i < r1; ++i)
        for(int j = 0; j < c2; ++j)
        {
            double sum = 0.0;

            for(int k = 0; k < c1; ++k)
                sum += m1[i][k] * m2[k][j];
            
            m3[i][j] = sum;
        }
}

void writeMatrix(int r1, int c1, double m1[][MAX])
{
    printf("\n\n");

    for(int i = 0; i < r1; ++i)
    {
        for(int j = 0; j < c1; ++j)
            printf("%lf ", m1[i][j]);
        
        printf("\n");
    }
}

int main(void)
{
    int r1,c1,r2,c2 = 0;

    printf("Please insert dimensions of M1\n");
    readDim(&r1, &c1);
    printf("Please insert dimensions of M2\n");
    readDim(&r2, &c2);

    if(checkDim(r1, c1, r2, c2) == -1)
    {
        printf("ERROR: Invalid matrix dimensions.\n");
        return -1;
    }

    double m1[MAX][MAX], m2[MAX][MAX];

    printf("Please insert M1\n");
    readMatrix(r1, c1, m1);

    printf("Please insert M2\n");
    readMatrix(r2, c2, m2);

    double m3[MAX][MAX];

    computeProduct(r1, c1, m1, r2, c2, m2, r1, c2, m3);
    
    writeMatrix(r1, c1, m1);
    writeMatrix(r2, c2, m2);
    writeMatrix(r1, c2, m3);

    return 0;
}