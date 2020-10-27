#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 30

typedef struct
{
    // Name of the athlete. Maximum size known a priori.
    char name[MAX_NAME + 1];

    // ID of the athlete and number of laps.
    int id;
    int laps;

    // Times for each lap. Size not known a priori.
    float *times;
    float average;
}
CYCLIST;

int readData(FILE *input, CYCLIST **resultPointer);
int getIndex(char *name, CYCLIST *data, int dataSize);
int getBest(CYCLIST *data, int dataSize);

int main(void)
{
    CYCLIST *cyclists;
    FILE *input = fopen("input.txt", "r");

    if(input == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file.\n");
        return -1;
    }

    int cyclistsCount = readData(input, &cyclists);

    fclose(input);

    // Read-Eval-Execute loop
    int cont = 1;
    while(cont)
    {
        char line[6 + 1];
        scanf(" %6s", line);

        // I do not include the strlen check since none of the available commands share any subsequence of strings
        // Cool side effect is that the program also works if the user specifies a substring (even only one letter) of the command.
        if(!strcmp(line, "list"))
        {
            printf("There are %d athletes:", cyclistsCount);
            for(int i = 0; i < cyclistsCount; ++i)
                printf("\n\t'%s' (ID: %d, %d LAPS)", cyclists[i].name, cyclists[i].id, cyclists[i].laps);
            
            printf("\n");
        }
        if(!strcmp(line, "detail"))
        {
            char name[MAX_NAME + 1];
            scanf(" %30s", name);

            int i = getIndex(name, cyclists, cyclistsCount);

            if(i != -1)
            {
                printf("Printing details for athlete '%s' (ID %d)", cyclists[i].name, cyclists[i].id);

                for(int j = 0; j < cyclists[i].laps; ++j)
                    printf("\nLAP %d: %f", (j + 1), cyclists[i].times[j]);
                
                printf("\n");
            }
            else
            {
                printf("Athlete '%s' not found.\n", name);
            }
            
        }
        if(!strcmp(line, "best"))
        {
            int i = getBest(cyclists, cyclistsCount);
            
            printf("Printing details for athlete '%s' (ID %d)", cyclists[i].name, cyclists[i].id);

            for(int j = 0; j < cyclists[i].laps; ++j)
                printf("\nLAP %d: %f", (j + 1), cyclists[i].times[j]);
            
            printf("\n\nAVERAGE: %f\n", cyclists[i].average);
        }
        if(!strcmp(line, "stop"))
        {
            cont = 0;
        }
    }

    for(int i = 0; i < cyclistsCount; ++i)
        free(cyclists[i].times);

    free(cyclists);

    return 0;
}

// Read all cyclist data from file and returns the number of elements
int readData(FILE *input, CYCLIST **resultPointer)
{
    int count;
    fscanf(input, "%d", &count);

    CYCLIST *result = (CYCLIST *) malloc(count * sizeof(CYCLIST));

    for(int i = 0; i < count; ++i)
    {
        fscanf(input, " %s %d %d", result[i].name, &result[i].id, &result[i].laps);
        result[i].times = (float *) calloc(result[i].laps, sizeof(float));

        float sum = 0;

        for(int j = 0; j < result[i].laps; ++j)
        {
            float value;
            fscanf(input, " %f", &value);

            sum += value;
            result[i].times[j] = value;
        }

        result[i].average = (sum / result[i].laps);
    }

    *resultPointer = result;
    return count;
}

int getIndex(char *name, CYCLIST *data, int dataSize)
{
    for(int i = 0; i < dataSize; ++i)
        if(strlen(name) == strlen(data[i].name) && strcmp(name, data[i].name) == 0)
            return i;

    return -1;
}

int getBest(CYCLIST *data, int dataSize)
{
    float best = data[0].average;
    int index = 0;

    for(int i = 1; i < dataSize; ++i)
        if(data[i].average < best)
        {
            best = data[i].average;
            index = i;
        }

    return index;
}