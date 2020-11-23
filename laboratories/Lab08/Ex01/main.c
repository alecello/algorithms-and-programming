#include <stdio.h>
#include <stdlib.h>

int validate(char **matrix, int n);
int generateMagic(int count, int n, char *flags, char **matrix);

int main(int argc, char **argv)
{
    char *filename;
    int size;

    if(argc == 3)
    {
        size = atoi(argv[1]);
        filename = argv[2];
    }
    else
    {
        filename = "output.txt";
        size = 3;
    }

    FILE *output = fopen(filename, "w");
    if(output == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file.\n");
        return -1;
    }
    
    char *flags = calloc((size * size), sizeof(char));

    char **matrix = malloc(size * sizeof(char *));
    for(int i = 0; i < size; ++i)
        matrix[i] = malloc(size * sizeof(char));

    generateMagic(0, size, flags, matrix);

    for(int r = 0; r < size; ++r)
    {
        fprintf(output, "%d", matrix[r][0]);

        for(int c = 1; c < size; ++c)
            fprintf(output, " %d", matrix[r][c]);
        
        fprintf(output, "\n");
    }

    for(int i = 0; i < size; i++)
        free(matrix[i]);
    
    free(matrix);
    free(flags);

    fclose(output);

    return 0;
}

// This is a permutation problem: we have to arrange nxn distinct values in nxn distinct cells
int generateMagic(int count, int n, char *flags, char **matrix)
{
    if(count == n * n)
        return validate(matrix, n);

    for(int i = 1; i <= (n * n); ++i)
    {
        if(flags[i] == 1)
            continue;

        flags[i] = 1;
        
        int r = count / n;
        int c = count % n;
        matrix[r][c] = i;
        
        if(generateMagic((count + 1), n, flags, matrix))
            return 1;
        else
            flags[i] = 0;
    }

    return 0;
}

int validate(char **matrix, int n)
{
    int row = -1;
    int col = -1;
    int lrd =  0; // Left-to-Right Diagonal
    int rld =  0; // Right-to-Left Diagonal
    for(int i = 0; i < n; ++i)
    {
        int currentRow = 0;
        int currentCol = 0;

        lrd += matrix[i][i];
        rld += matrix[n-1-i][i];

        for(int j = 0; j < n; ++j)
        {
            currentRow += matrix[i][j];
            currentCol += matrix[j][i];
        }

        if(row < 0)
            row = currentRow;
        else if(row != currentRow)
            return 0;

        if(col < 0)
            col = currentCol;
        else if(col != currentCol)
            return 0;
    }

    return (lrd == rld && rld == row && row == col);
}