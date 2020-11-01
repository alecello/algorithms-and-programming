#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (a > b) ? a : b
#define MIN(a,b) (a < b) ? a : b

typedef struct
{
    int headX;
    int headY;

    int len;
    int direction;
}
SNAKE;

void readField(FILE *input, char **map, int height, int width);
int getSnakes(SNAKE **pointer, char **map, int height, int width);
void getLengths(char **map, int heigth, int width, SNAKE *snakes, int count, int *min, int *max);
char getDirection(int x, int y, char **map, int heigth, int width);

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        fprintf(stderr, "Error while rading file.\n");
        exit(-1);
    }

    int height,width;
    fscanf(input, "%d %d\n", &height, &width);

    // Allocate map
    char **map = (char **) malloc(height * sizeof(char *));
    for(int i = 0; i < height; ++i)
        map[i] = (char *) malloc(width * sizeof(char));

    readField(input, map, height, width);

    SNAKE *snakes;
    int snakeCount = getSnakes(&snakes, map, height, width);

    int min, max;
    getLengths(map, height, width, snakes, snakeCount, &min, &max);

    printf("\nNumber of snakes: %d\nMinimum length: %d\nMaximum length: %d\n", snakeCount, min, max);
}

void readField(FILE *input, char **map, int height, int width)
{
    // Width for the characters in the line, plus a newline and a null terminator
    char *line = (char *) calloc((width + 1 + 1), sizeof(char));

    for(int i = 0; i < height; ++i)
    {
        fgets(line, (width + 1 + 1), input);
        for(int j = 0; j < width; ++j)
            map[i][j] = line[j];
    }

    // Optional, but useful in debugging
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
            putc(map[i][j], stdout);
        
        putc('\n', stdout);
    }
}

int getSnakes(SNAKE **pointer, char **map, int height, int width)
{
    SNAKE *result = NULL;
    int count = 0;

    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j)
            if(map[i][j] == '+')
            {
                // Could be replaced with a linked list for faster performance
                // Alternatively, one could scan two times to get a snake count first
                // But I don't know if it would be faster.
                result = (SNAKE *) realloc(result, (count + 1) * sizeof(SNAKE));

                result[count].headX = i;
                result[count].headY = j;

                ++count;
            }
    
    *pointer = result;
    return count;
}

void getLengths(char **map, int heigth, int width, SNAKE *snakes, int count, int *min, int *max)
{
    int minimum = MAX(width, heigth);
    int maximum = 0;

    for(int i = 0; i < count; ++i)
    {
        char direction = getDirection(snakes[i].headX, snakes[i].headY, map, heigth, width);
        int length = 1;

        int incrementX = 0;
        int incrementY = 0;

        if(direction & 4)
            incrementX = -1;
        else if(direction & 8)
            incrementX = 1;

        if(direction & 2)
            incrementY = 1;
        else if(direction & 1)
            incrementY = -1;

        while(incrementX || incrementY)
        {
            int x = snakes[i].headX + (incrementX * length);
            int y = snakes[i].headY + (incrementY * length);

            if(x < 0 || x >= heigth || y < 0 || y >= width || map[x][y] != '*')
                break;
            
            ++length;
        }

        snakes[i].len = length;
        minimum = MIN(minimum, length);
        maximum = MAX(maximum, length);
    }

    *min = minimum;
    *max = maximum;
}

char getDirection(int x, int y, char **map, int heigth, int width)
{
    int lowerX = MAX((x - 1), 0);
    int lowerY = MAX((y - 1), 0);

    int upperX = MIN((x + 1), heigth);
    int upperY = MIN((y + 1), width);

    int i,j;
    int flag = 1;
    char result = 0;

    for(i = lowerX; i <= upperX && flag; ++i)
        for(j = lowerY; j <= upperY && flag; ++j)
            if(map[i][j] == '*') flag  = 0;
    
    // We use a bit-field to store direction
    // Bit 0: LEFT  if 1
    // Bit 1: RIGHT if 1
    // Bit 2: UP    if 1
    // Bit 3: DOWN  if 1
    if(i < x)
        result |= 1;
    else if(i > x)
        result |= 2;
    
    if(j < y)
        result |= 4;
    else if(j > y)
        result |= 8;
        
    return result;
}