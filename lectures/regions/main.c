#include <stdio.h>

#define COLS 15
#define ROWS 14

void findRegion(int r, int c, char map[][COLS], int counter);

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    char map[ROWS][COLS];

    int r = 0;
    int c = 0;

    char v;
    while((v = fgetc(input)) != EOF)
    {
        if(v == '\n')
        {
            c = 0;
            ++r;
        }
        else
        {
            map[r][c] = v;
            ++c;
        }
    }

    int counter = 1;
    for(int i = 0; i < ROWS; ++i)
        for(int j = 0; j < COLS; ++j)
            if(map[i][j] == '.')
                findRegion(i, j, map, counter++);
    
    for(int i = 0; i < ROWS; ++i)
    {
        for(int j = 0; j < COLS; ++j)
            fprintf(output, "%c", map[i][j]);
        
        putc('\n', output);
    }

    fclose(input);
    fclose(output);
    return 0;
}

void findRegion(int r, int c, char map[][COLS], int counter)
{
    // If this is a star, then we don't do anything.
    if(map[r][c] == '*')
        return;

    // If a particular cell is a dot, assign the group number to it and it's associated direction
    int up = (map[(r-1)][c] == '.') ? (map[(r-1)][c] = '0' + counter) : 0;
    int dn = (map[(r+1)][c] == '.') ? (map[(r+1)][c] = '0' + counter) : 0;
    int lt = (map[r][(c-1)] == '.') ? (map[r][(c-1)] = '0' + counter) : 0;
    int rt = (map[r][(c+1)] == '.') ? (map[r][(c+1)] = '0' + counter) : 0;

    // If all the associated directions are zero, then we're done.
    if(!(up || dn || lt || rt))
        return;

    // Recurse
    // We could skip the first conditional and only recurse to cells that are not stars, but it would no longer be a
    // tail recursive function.
    findRegion(r-1, c, map, counter);
    findRegion(r+1, c, map, counter);
    findRegion(r, c-1, map, counter);
    findRegion(r, c+1, map, counter);
}