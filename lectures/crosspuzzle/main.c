#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UL 1 // Up Left
#define US 2 // Up Straight
#define UR 3 // Up Right
#define RS 4 // Right Straight
#define DR 5 // Down Right
#define DS 6 // Down Straight
#define DL 7 // Down Left
#define LS 8 // Left Straight

#define MAX(a,b) (a > b) ? a : b

typedef struct
{
    char *word;
    int direction;

    // Coordinates
    int x;
    int y;
}
WORD;

int getWords(FILE *wordList, char ***words);
int isValid(char character);
int findWords(char **grid, int x, int y, char *word, WORD **found);

int main(void)
{
    FILE *inputFile = fopen("input.txt", "r");
    FILE *wordList = fopen("words.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if(inputFile == NULL || wordList == NULL || outputFile == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open files.\n");
        return -1;
    }

    // Dimensions of the matrix
    int x,y;
    fscanf(inputFile, "%d %d\n", &x, &y);

    // Grid allocation
    char **grid = (char **) malloc(y * sizeof(char *));
    for(int i = 0; i < y; ++i)
        grid[i] = (char *) malloc(x * sizeof(char));

    // Results grid allocation
    char **result = (char **) malloc(y * sizeof(char *));
    for(int i = 0; i < y; ++i)
        grid[i] = (char *) malloc(x * sizeof(char));

    for(int i = 0; i < y; ++i)
        for(int j = 0; j < x; ++j)
            result[i][j] = ' ';

    // Read the grid
    for(int i = 0; i < y; ++i)
    {
        // x characters, a newline and a terminator
        char line[x + 1 + 1];
        fgets(line, (x + 2), inputFile);

        for(int j = 0; j < x; ++j)
            grid[i][j] = line[j];
    }

    fclose(inputFile);

    char **words;
    int wordCount = getWords(wordList, &words);

    fclose(wordList);

    for(int i = 0; i < wordCount; i++)
    {
        WORD *found = NULL;
        int foundCount = 0;

        foundCount = findWords(grid, x, y, words[i], &found);

        for(int j = 0; j < foundCount; ++j)
        {
            int gx = found[j].x;
            int gy = found[j].y;

            if(found[i].direction == RS)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy][gx + k] = found[j].word[k];
            else if(found[i].direction == LS)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy][gx - k] = found[j].word[k];
            else if(found[i].direction == US)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy - k][gx] = found[j].word[k];
            else if(found[i].direction == DS)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy + k][gx] = found[j].word[k];
            else if(found[i].direction == UR)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy - k][gx + k] = found[j].word[k];
            else if(found[i].direction == UL)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy - k][gx - k] = found[j].word[k];
            else if(found[i].direction == DR)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy + k][gx + k] = found[j].word[k];
            else if(found[i].direction == DL)
                for(int k = 0; k < strlen(found[j].word); ++k)
                    result[gy + k][gx - k] = found[j].word[k];
        }

        free(found);
    }

    for(int i = 0; i < y; ++i)
    {
        for(int j = 0; j < x; ++j)
            fprintf(outputFile, "%c", result[i][j]);

        fprintf(outputFile, "\n");
    }

    fclose(outputFile);

    // Free all allocated memory
    for(int i = 0; i < y; ++i)
    {
        free(grid[i]);
        free(result[i]);
    }

    free(grid);
    free(result);

    for(int i = 0; i < wordCount; ++i)
        free(words[i]);
    
    free(words);
}

// Dynamically allocate a double array of strings
// Words can have any length and no marker whatsoever is needed
// There is no hard limit on how long words can be
// The result gets written to the double char pointer passed by reference
// Return value is the number of words read (similar to argc)
int getWords(FILE *wordList, char ***pointer)
{
    int wCount = 0;

    char **words = NULL;
    char nextChar;

    while((nextChar = fgetc(wordList)) != EOF)
    {
        int wLen = 0;

        words = (char **) realloc(words, ++wCount * sizeof(char *));
        words[wCount - 1] = (char *) malloc(++wLen * sizeof(char));
        words[wCount - 1][wLen - 1] = nextChar;

        while(isValid(nextChar = fgetc(wordList)))
        {
            words[wCount - 1] = (char *) realloc(words[wCount - 1], ++wLen * sizeof(char));
            words[wCount - 1][wLen - 1] = nextChar;
        }

        words[wCount - 1] = (char *) realloc(words[wCount - 1], ++wLen * sizeof(char));
        words[wCount - 1][wLen - 1] = 0;
    }

    *pointer = words;
    return wCount;
}

int isValid(char character)
{
    if(character != '\n' && character != EOF)
        return 1;
    else
        return 0;
}

int findWords(char **grid, int x, int y, char *word, WORD **found)
{
    int matches = 0;
    int length = strlen(word);

    WORD *pointer = NULL;

    // Find horizontal right-straight words
    for(int i = 0; i < y; ++i)
        for(int j = 0; j <= (x - length); ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i][j+k] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = LS;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    // Find left-straight words
    for(int i = 0; i < y; ++i)
        for(int j = (length - 1); j < x; ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i][j-k] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = LS;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    // Find up-straight words
    for(int i = (length - 1); i < y; ++i)
        for(int j = 0; j < x; ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i-k][j] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = US;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    // Find down-straight words
    for(int i = 0; i <= (y - length); ++i)
        for(int j = 0; j < x; ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i+k][j] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = DS;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    // Find up-right words
    for(int i = (length - 1); i < y; ++i)
        for(int j = 0; j <= (x - length); ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i-k][j+k] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = UR;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    // Find up-left words
    for(int i = (length - 1); i < y; ++i)
        for(int j = (length - 1); j < x; ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i-k][j-k] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = UL;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    // Find down-right words
    for(int i = 0; i < (y - length); ++i)
        for(int j = 0; j <= (x - length); ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i+k][j+k] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = DR;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    // Find down-left words
    for(int i = 0; i < (y - length); ++i)
        for(int j = (length - 1); j < x; ++j)
            if(grid[i][j] == word[0])
            {
                int found = 1;

                for(int k = 1; k < length && found; k++)
                    if(grid[i+k][j-k] != word[k])
                        found = 0;
                
                if(found)
                {
                    pointer = (WORD *) realloc(pointer, ++matches * sizeof(WORD));

                    pointer[matches - 1].direction = DL;
                    pointer[matches - 1].word = word;

                    pointer[matches - 1].x = j;
                    pointer[matches - 1].y = i;
                }
            }
    
    *found = pointer;
    return matches;
}