#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) (a > b) ? a : b

void findWords(char **grid, char **result, int x, int y, FILE *input);

int main(void)
{
    FILE *inputFile = fopen("input.txt", "r");
    FILE *wordsFile = fopen("words.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if(inputFile == NULL || wordsFile == NULL || outputFile == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open files.\n");
        return -1;
    }

    // Dimensions of the matrix
    int x,y;
    fscanf(inputFile, "%d %d\n", &y, &x);

    // Grid allocation
    char **grid = (char **) malloc(y * sizeof(char *));
    for(int i = 0; i < y; ++i)
        grid[i] = (char *) malloc(x * sizeof(char));

    // Results grid allocation
    char **result = (char **) malloc(y * sizeof(char *));
    for(int i = 0; i < y; ++i)
    {
        result[i] = (char *) malloc(x * sizeof(char));
        for(int j = 0; j < x; ++j)
            result[i][j] = ' ';
    }

    // Read the grid
    for(int i = 0; i < y; ++i)
    {
        // x characters, a newline and a terminator
        char line[x + 1 + 1];
        fgets(line, (x + 2), inputFile);

        for(int j = 0; j < x; ++j)
            grid[i][j] = line[j];
    }

    findWords(grid, result, x, y, wordsFile);

    for(int i = 0; i < y; ++i)
    {
        for(int j = 0; j < x; ++j)
            fprintf(outputFile, "%c", result[i][j]);

        fprintf(outputFile, "\n");
    }

    // Free all allocated memory
    for(int i = 0; i < y; ++i)
    {
        free(grid[i]);
        free(result[i]);
    }

    free(grid);
    free(result);

    fclose(inputFile);
    fclose(wordsFile);
    fclose(outputFile);
}

void findWords(char **grid, char **result, int x, int y, FILE *input)
{
    // Maximum acceptable word length is the maximum between width and height of puzzle
    char word[MAX(x, y) + 1];
    while(fscanf(input, "%s", word) != EOF)
    {
        int length = strlen(word);

        // UP, UP-RIGHT , RIGHT, DOWN-RIGHT, DOWN, DOWN-LEFT, LEFT, UP-LEFT
        int versors[2][8] = {{-1, -1, 0, 1, 1, 1, 0, -1}, {0, 1, 1, 1, 0, -1, -1, -1}};

        for(int d = 0; d < 8; ++d)
        {
            for(int i = 0; i < y; ++i)
                for(int j = 0; j < x; ++j)
                {
                    int flag = 1;

                    for(int k = 0; k < length && flag; ++k)
                    {
                        int r = i + (versors[0][d] * k);
                        int c = j + (versors[1][d] * k);

                        if(r < 0 || c < 0 || r >= y || c >= x || grid[r][c] != word[k])
                            flag = 0;
                    }

                    if(flag)
                        for(int k = 0; k < length; ++k)
                            result[i + (versors[0][d] * k)][j + (versors[1][d] * k)] = word[k];
                }
        }
    }
}