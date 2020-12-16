#include <stdio.h>
#include <stdlib.h>

#define R 0
#define C 1
#define D 4

typedef struct element
{
    int r;
    int c;

    struct element *next;
}
element;

void copyStack(element *source, element **destination);
void destroyStack(element **stack);
element *popMove(element *stack);
element *pushMove(element *stack, int r, int c);
void printPath(element *stack);
void solveMaze(int count, int r, int c, int pr, int pc, char **maze, char **visited, int *shortest, element **shortestPath, element *stack);
void readMaze(FILE *input, char **maze, int rows, int cols);
void findStart(int *rr, int *cc, int rows, int cols, char **maze);

int directions[][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open input.txt\n");
        exit(-1);
    }

    int rows, cols;
    fscanf(input, "%d %d\n", &rows, &cols);

    char **maze = malloc(rows * sizeof(char *));
    for(int i = 0; i < rows; ++i)
        maze[i] = malloc(cols * sizeof(char));

    char **visited = malloc(rows * sizeof(char *));
    for(int i = 0; i < rows; ++i)
        visited[i] = calloc(cols, sizeof(char));

    readMaze(input, maze, rows, cols);

    int shortest = -1;

    element *stack = NULL;
    element *shortestPath = NULL;

    int r,c;

    findStart(&r, &c, rows, cols, maze);
    solveMaze(0, r, c, -1, -1, maze, visited, &shortest, &shortestPath, stack);

    printf("\nShortest path (%d elements):\n", shortest);
    printPath(shortestPath);
}

void readMaze(FILE *input, char **maze, int rows, int cols)
{
    char line[cols + 1 + 1];
    for(int r = 0; r < rows; ++r)
    {
        fgets(line, cols + 1 + 1, input);
        for(int c = 0; c < cols; ++c)
            maze[r][c] = line[c];
    }
}

void findStart(int *rr, int *cc, int rows, int cols, char **maze)
{
    for(int r = 0; r < rows; ++r)
        for(int c = 0; c < cols; ++c)
            if(maze[r][c] == '@')
            {
                *rr = r;
                *cc = c;
                return;
            }

    *rr = -1;
    *cc = -1;
}

void solveMaze(int count, int r, int c, int pr, int pc, char **maze, char **visited, int *shortest, element **shortestPath, element *stack)
{
    if(maze[r][c] == '#')
    {
        if(*shortest < 0 || count < *shortest)
        {
            destroyStack(shortestPath);
            copyStack(stack, shortestPath);

            *shortest = count;
        }

        printPath(stack);
        return;
    }

    for(int i = 0; i < D; ++i)
    {
        int nr = (r + directions[i][R]);
        int nc = (c + directions[i][C]);

        if(visited[nr][nc] == 1 || (nr == pr && nc == pc) || maze[nr][nc] == '*' || maze[nc][nr] == '@')
            continue;

        stack = pushMove(stack, nr, nc);
        visited[nr][nc] = 1;
        solveMaze((count + 1), nr, nc, r, c, maze, visited, shortest, shortestPath, stack);
        visited[nr][nc] = 0;
        stack = popMove(stack);
    }
}

void printPath(element *stack)
{
    while(stack != NULL)
    {
        printf("[%d,%d] ", stack->r, stack->c);
        stack = stack->next;
    }

    putchar('\n');
}

element *pushMove(element *stack, int r, int c)
{
    element *e = malloc(sizeof(element));

    e->r = r;
    e->c = c;

    e->next = stack;
    return e;
}

element *popMove(element *stack)
{
    element *new = stack->next;
    free(stack);

    return new;
}

void destroyStack(element **stack)
{
    element *e;

    while(*stack != NULL)
    {
        e = (*stack)->next;
        free(*stack);
        *stack = e;
    }
}

void copyStack(element *source, element **destination)
{
    while(source != NULL)
    {
        element *e = malloc(sizeof(element));

        e->r = source->r;
        e->c = source->c;

        e->next = *destination;
        *destination = e;

        source = source->next;
    }
}
