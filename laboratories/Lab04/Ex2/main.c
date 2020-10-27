#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 4
#define RECT_MAX 100

#define AREA 1
#define PERIMETER 2

typedef struct
{
    // First pair of coordinates
    float x1;
    float y1;

    // Second pair of coordinates
    float x2;
    float y2;

    // Number of coordinates already read
    int coordsRead;

    // Sizes of the rectangle
    float x;
    float y;

    // Area and perimeter
    float area;
    float perimeter;

    // Name of the rectangle
    char name[NAME_LEN + 1];
} RECTANGLE;

int readRectangles(FILE *inputFile, RECTANGLE **rectangles);
int getIndex(char *name, int count, RECTANGLE *rectangles);
void computeValues(RECTANGLE *rectangles, int count);
float max(float a, float b);
float min(float a, float b);
void printStats(RECTANGLE *rectangles, int rectanglesNum);
RECTANGLE **orderBy(RECTANGLE *rectangles, int count, int parameter);

int main(int argc, char **argv)
{
    RECTANGLE *rectangles;
    char *inputFilePath, *areaFilePath, *perimeterFilePath;
    int rectanglesNum = 0;

    if(argc != 4)
    {
        // Normally I should error out, however to ease debugging I'm going to assume default values instead.
        // This way I can launch the program from the editor without modifying launch configuration.
        inputFilePath = "input.txt";
        areaFilePath = "area.txt";
        perimeterFilePath = "perimeter.txt";
    }
    else
    {
        inputFilePath = argv[1];
        areaFilePath = argv[2];
        perimeterFilePath = argv[3];
    }

    FILE *inputFile = fopen(inputFilePath, "r");
    FILE *areaFile = fopen(areaFilePath, "w");
    FILE *perimeterFile = fopen(perimeterFilePath, "w");

    if(inputFile == NULL || areaFile == NULL || perimeterFile == NULL)
    {
        printf("ERROR while opening files.\n");
        return -1;
    }

    rectanglesNum = readRectangles(inputFile, &rectangles);
    computeValues(rectangles, rectanglesNum);

    printStats(rectangles, rectanglesNum);

    RECTANGLE **orderedByArea = orderBy(rectangles, rectanglesNum, AREA);
    RECTANGLE **orderedByPerimeter = orderBy(rectangles, rectanglesNum, PERIMETER);

    for(int i = 0; i < rectanglesNum; ++i)
    {
        fprintf(areaFile, "%s (%.2f)\n", orderedByArea[i]->name, orderedByArea[i]->area);
        fprintf(perimeterFile, "%s (%.2f)\n",orderedByPerimeter[i]->name,orderedByPerimeter[i]->perimeter);
    }

    fclose(areaFile);
    fclose(perimeterFile);

    // These are arrays of pointers, however the pointers within the array are just pointers to memory previously
    // statically allocated (rectangles array), so I don't have to recursively free().
    free(orderedByArea);
    free(orderedByPerimeter);

    return 0;
}

int readRectangles(FILE *inputFile, RECTANGLE **rectangles)
{
    int count;
    fscanf(inputFile, "%d\n", &count);

    RECTANGLE *result = (RECTANGLE *) malloc(count * sizeof(RECTANGLE));

    // Initialize rectangles
    for(int i = 0; i < count; ++i)
        result[i].coordsRead = 0;

    float x,y;
    char name[NAME_LEN + 1];

    int i = 0;
    for(int read = 0; read < (count * 2); ++read)
    {
        fscanf(inputFile, "%s %f %f\n", name, &x, &y);
        int index = getIndex(name, i, result);

        if(result[index].coordsRead == 0)
        {
            result[index].x1 = x;
            result[index].y1 = y;
            ++result[index].coordsRead;
        }
        else
        {
            result[index].x2 = x;
            result[index].y2 = y;
            ++result[index].coordsRead;
        }

        // If index == i we're initializing the rectangle for the first time
        // So we also need to copy the name
        if(index == i)
        {
            strncpy(result[index].name, name, NAME_LEN + 1);
            ++i;
        }
    }

    *rectangles = result;
    return count;
}

// Get the index of the rectangle with the given name.
// If such an index does not exist, return count.
int getIndex(char *name, int count, RECTANGLE *rectangles)
{
    for(int i = 0; i < count; ++i)
    {
        char *n = rectangles[i].name;

        if(strlen(name) == strlen(n) && strcmp(name, n) == 0)
            return i;
    }

    return count;
}

void computeValues(RECTANGLE *rectangles, int count)
{
    for(int i = 0; i < count; ++i)
    {
        rectangles[i].x = max(rectangles[i].x1,rectangles[i].x2) - min(rectangles[i].x1,rectangles[i].x2);
        rectangles[i].y = max(rectangles[i].y1,rectangles[i].y2) - min(rectangles[i].y1,rectangles[i].y2);

        rectangles[i].area = rectangles[i].x * rectangles[i].y;
        rectangles[i].perimeter = (2 * rectangles[i].x) + (2 * rectangles[i].y);
    }
}

float max(float a, float b)
{
    if(a > b)
        return a;
    else
        return b;
}

float min(float a, float b)
{
    if(a < b)
        return a;
    else
        return b;
}

void printStats(RECTANGLE *rectangles, int rectanglesNum)
{
    printf("You have inserted %d rectangles.\n\n", rectanglesNum);

    for(int i = 0; i < rectanglesNum; ++i)
        printf("Rectangle '%s'\n\tVertex 1: (%+.2f, %+.2f)\n\tVertex 2: (%+.2f, %+.2f)\n", rectangles[i].name, rectangles[i].x1, rectangles[i].y1, rectangles[i].x2, rectangles[i].y2);
}

RECTANGLE **orderBy(RECTANGLE *rectangles, int count, int parameter)
{
    RECTANGLE **result = (RECTANGLE **) malloc(count * sizeof(RECTANGLE *));

    // Initialize an array of pointers to structures.
    // Moving around pointers is quicker than moving around the entire structure.
    for(int i = 0; i < count; ++i)
        result[i] = &rectangles[i];

    // Sort using insertion sort
    for(int i = (count - 2); i >= 0; --i)
    {
        int j = (i + 1);
        RECTANGLE *t = result[i];

        if(parameter == AREA)
            while(j < count && result[j]->area > t->area)
            {
                result[j - 1] = result[j];
                ++j;
            }
        else
            while(j < count && result[j]->perimeter > t->perimeter)
            {
                result[j - 1] = result[j];
                ++j;
            }

        result[j - 1] = t;
    }

    return result;
}