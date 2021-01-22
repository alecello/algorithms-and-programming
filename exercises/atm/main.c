#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

typedef struct structRoad
{
    struct structCity *origin;
    struct structCity *destination;

    int length;

    struct structRoad *next;
}
road;

typedef struct structCity
{
    char id[MAX_NAME + 1];

    int *distances;
    int *isInfinite;

    int minimumDistance;

    int used;

    struct structRoad *roads;

    struct structCity *next;
}
city;

int relax(int index, city *cities)
{
    int dirty = 0;
    while(cities != NULL)
    {
        if(!(cities->isInfinite[index]))
        {
            road *r = cities->roads;
            while(r != NULL)
            {
                if(r->destination->isInfinite[index] || r->destination->distances[index] > cities->distances[index] + r->length)
                {
                    r->destination->distances[index] = cities->distances[index] + r->length;

                    r->destination->isInfinite[index] = 0;
                    dirty = 1;
                }

                r = r->next;
            }
        }

        cities = cities->next;
    }

    return dirty;
}

void resetGraph(city *cities, city *start, int ATMCount)
{
    while(cities != NULL)
    {
        for(int i = 0; i < ATMCount; ++i)
        {
            cities->distances[i] = 0;
            cities->isInfinite[i] = (cities == start) ? 0 : 1;
            cities->minimumDistance = -1;
        }

        cities = cities->next;
    }
}

void calculateMinimumDistance(city *cities, int ATMCount)
{
    while(cities != NULL)
    {
        for(int i = 0; i < ATMCount; ++i)
        {
            if(cities->minimumDistance < 0 || cities->minimumDistance > cities->distances[i])
                cities->minimumDistance = cities->distances[i];
        }

        cities = cities->next;
    }
}

int getMaximumDistance(city *cities)
{
    int maxDistance = cities->minimumDistance;
    cities = cities->next;

    while(cities != NULL)
    {
        if(cities->minimumDistance > maxDistance)
            maxDistance = cities->minimumDistance;

        cities = cities->next;
    }

    return maxDistance;
}

void calculateDistances(int index, city *cities, int count)
{
    int retval = 1;
    for(int i = 1; i < count && retval != 0; ++i)
        retval = relax(index, cities);

    if(relax(index, cities))
    {
        printf("ERROR: Negative loop cycle detected, solution impossible.\n");
        exit(1);
    }
}

void recurse(int iteration, int cityCount, int ATMCount, city *cities, city **ATMs, int *record, city **recordATMs)
{
    if(iteration >= ATMCount)
    {
        for(int i = 0; i < ATMCount; ++i)
        {
            resetGraph(cities, ATMs[i], ATMCount);
            calculateDistances(i, cities, cityCount);
        }

        calculateMinimumDistance(cities, ATMCount);
        int maxDistance = getMaximumDistance(cities);

        if(*record < 0 || maxDistance < *record)
        {
            for(int i = 0; i < ATMCount; ++i)
                recordATMs[i] = ATMs[i];

            *record = maxDistance;
        }

        return;
    }

    city *pointer = cities;
    while(pointer != NULL)
    {
        if(pointer->used == 0)
        {
            pointer->used = 1;
            ATMs[iteration] = pointer;
            recurse((iteration + 1), cityCount, ATMCount, cities, ATMs, record, recordATMs);
            pointer->used = 0;
        }

        pointer = pointer->next;
    }

    return;
}

city *findCity(city *list, char *id)
{
    while(list != NULL)
    {
        if(strcmp(list->id, id) == 0)
            return list;

        list = list->next;
    }

    return NULL;
}

city * insertCity(city **list, char *id, int ATMCount)
{
    city *pointer = findCity(*list, id);
    if(pointer == NULL)
    {
        city *new = malloc(sizeof(city));

        strcpy(new->id, id);

        new->distances = calloc(ATMCount, sizeof(int));
        new->isInfinite = calloc(ATMCount, sizeof(int));
        new->minimumDistance = -1;
        new->used = 0;
        new->roads = NULL;

        new->next = *list;
        *list = new;

        return new;
    }

    return pointer;
}

int getCityCount(city *list)
{
    int count = 0;
    while(list != NULL)
    {
        ++count;
        list = list->next;
    }

    return count;
}

int main(int argc, char **argv)
{
    int ATMCount;
    char *filename;

    if(argc == 1)
    {
        filename = "input.txt";
        ATMCount = 2;
    }
    else if(argc == 3)
    {
        filename = argv[1];
        ATMCount = atoi(argv[2]);
    }
    else
    {
        printf("Usage: %s <filename> <atm count>\nDefault values: filename=input.txt - atm count=2\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("ERROR: Failed to open file.\n");
        exit(1);
    }

    city *cities = NULL;

    int weight;
    char origin[MAX_NAME + 1], destination[MAX_NAME + 1];

    while(fscanf(file, " %s %s %d", origin, destination, &weight) != EOF)
    {
        city *o = insertCity(&cities, origin, ATMCount);
        city *d = insertCity(&cities, destination, ATMCount);

        // Forward edge
        road *f = malloc(sizeof(road));

        // Backward edge
        road *b = malloc(sizeof(road));

        f->length = weight;
        b->length = weight;

        f->origin = o;
        f->destination = d;

        b->origin = d;
        b->destination = o;

        f->next = o->roads;
        b->next = d->roads;

        o->roads = f;
        d->roads = b;
    }

    int record = -1;

    city **ATMs = malloc(ATMCount * sizeof(city *));
    city **recordATMs = malloc(ATMCount * sizeof(city *));

    int cityCount = getCityCount(cities);

    recurse(0, cityCount, ATMCount, cities, ATMs, &record, recordATMs);

    if(record == -1)
    {
        printf("No solution found!\n");
    }
    else
    {
        printf("You need %d bancomats in %s", ATMCount, recordATMs[0]->id);

        for(int i = 1; i < ATMCount; ++i)
            printf(", %s", recordATMs[i]->id);

        printf(" to minimize distance.\n");
    }

    fclose(file);

    free(ATMs);
    free(recordATMs);

    while(cities != NULL)
    {
        city *next = cities->next;

        free(cities->distances);
        free(cities->isInfinite);

        while(cities->roads != NULL)
        {
            road *next = cities->roads->next;
            free(cities->roads);

            cities->roads = next;
        }

        free(cities);

        cities = next;
    }

    return 0;
}
