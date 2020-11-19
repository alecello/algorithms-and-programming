#include <stdio.h>
#include <stdlib.h>

#define R 0
#define C 1

void solve(int count, int start, int **grid, int size, int **solution, int **stack, int *best);
int complete(int **grid, int size);
void apply(int **grid, int **solution, int count);
void print(int **grid, int size);

/* ===========================================================================
 *                  Alternative form using supersets
 * ===========================================================================
 */
int main(void)
{
    // Open file
    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file.\n");
        exit(1);
    }

    // Get size of problem
    int size;
    fscanf(input, "%d", &size);

    // Create and read grid
    int **grid = (int **) malloc(size * sizeof(int *));
    for(int i = 0; i < size; ++i)
        grid[i] = (int *) malloc(size * sizeof(int));

    int read;
    for(int r = 0; r < size; ++r)
        for(int c = 0; c < size; ++c)
        {
            fscanf(input, "%d", &read);
            grid[r][c] = read;
        }

    fclose(input);

    // Allocate solution vector and temporary vector
    int **solution = (int **) malloc((size * size) * sizeof(int *));
    for(int i = 0; i < (size * size); ++i)
        solution[i] = (int *) malloc(2 * sizeof(int));

    int **stack = (int **) malloc((size * size) * sizeof(int *));
    for(int i = 0; i < (size * size); ++i)
        stack[i] = (int *) malloc(2 * sizeof(int));
    
    // Solve problem
    int counter = ((size * size) + 1);
    solve(0, 0, grid, size, solution, stack, &counter);

    // Print results
    printf("We need to eliminate %d entries:\n", counter);
    apply(grid, solution, counter);
    print(grid, size);
    
    // Free allocated memory and exit
    for(int i = 0; i < size; ++i)
        free(grid[i]);
    free(grid);

    return 0;
}

void solve(int count, int start, int **grid, int size, int **solution, int **stack, int *best)
{
    // Skip recursion if we're already at a worse point than best
    if(count >= *best)
        return;

    // Termination condition
    if(start >= (size * size))
    {
        if(complete(grid, size))
        {
            if(count < *best)
            {
                *best = count;

                for(int i = 0; i < count; ++i)
                {
                    solution[i][R] = stack[i][R];
                    solution[i][C] = stack[i][C];
                }
            }
        }

        return;
    }

    for(int i = start; i < (size * size); ++i)
    {
        int r = i / size;
        int c = i % size;

        if(grid[r][c] == -1)
            continue;

        int pop = grid[r][c];
        grid[r][c] = -1;

        stack[count][R] = r;
        stack[count][C] = c;
        solve((count + 1), i, grid, size, solution, stack, best);

        grid[r][c] = pop;
    }

    solve(count, (size * size), grid, size, solution, stack, best);
}

int complete(int **grid, int size)
{
    for(int r = 0; r < size; ++r)
        for(int c = 0; c < size; ++c)
        {
            for(int rr = 0; rr < size; ++rr)
                if(rr != r && grid[r][c] != -1 && grid[rr][c] == grid[r][c])
                    return 0;
            
            for(int cc = 0; cc < size; ++cc)
                if(cc != c && grid[r][c] != -1 && grid[r][cc] == grid[r][c])
                    return 0;
        }
    
    return 1;
}

void apply(int **grid, int **solution, int count)
{
    for(int i = 0; i < count; ++i)
        grid[solution[i][R]][solution[i][C]] = -1;
}

void print(int **grid, int size)
{
    putchar('\n');

    for(int r = 0; r < size; ++r)
    {
        putchar('\t');

        for(int c = 0; c < size; ++c)
            printf("%c ", (grid[r][c] != -1) ? '0' + grid[r][c] : ' ');
        
        putchar('\n');
    }
}