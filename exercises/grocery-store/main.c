#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 50

typedef struct structItem
{
    char name[MAX_NAME + 1];

    int weight;
    int value;
    int availability;

    int used;
}
item;

void recurse(int typeCount, int itemCount, int index, int weight, int maxWeight, int minWeight, int *record, item *items, item **solution, item **temp);

int main(int argc, char **argv)
{
    char *filename;
    int maxWeight;

    if(argc != 3)
    {
        // For convenience during debugging, i just assume a default value
        //     fprintf(stderr, "Usage: %s <filename> <max weight>\n", argv[0]);
        //     exit(1);

        filename = "input.txt";
        maxWeight = 400;
    }
    else
    {
        filename = argv[1];
        maxWeight = atoi(argv[2]);
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    int listCount;
    fscanf(file, " %d\n", &listCount);

    item *items = malloc(listCount * sizeof(item));

    int totalItems = 0;
    int minWeight = -1;

    for(int i = 0; i < listCount; ++i)
    {
        fscanf(file, " %s %d %d %d\n", items[i].name, &(items[i].weight), &(items[i].value), &(items[i].availability));
        items[i].used = 0;

        totalItems += items[i].availability;

        if(minWeight < 0 || items[i].weight < minWeight)
            minWeight = items[i].weight;
    }

    item **solution = malloc(totalItems * sizeof(item *));
    item **temp = malloc(totalItems * sizeof(item *));

    solution[0] = NULL;

    int record = 0;

    recurse(totalItems, listCount, 0, 0, maxWeight, minWeight, &record, items, solution, temp);

    if(solution[0] == NULL)
    {
        printf("No solution found.\n");
    }
    else
    {
        int totalUsed = 0, totalWeight = 0, totalPrice = 0;

        for(int i = 0; solution[i] != NULL; ++i)
            solution[i]->used++;

        for(int i = 0; i < listCount; ++i)
        {
            if(items[i].used > 0)
            {
                printf("%s\t\t%d\t\t%d\t\t%d\n", items[i].name, items[i].used, items[i].weight * items[i].used, items[i].value * items[i].used);

                totalUsed += items[i].used;
                totalWeight += items[i].weight * items[i].used;
                totalPrice += items[i].value * items[i].used;
            }
        }

        printf("\nsolution\t\t%d\t\t%d\t\t%d\n", totalUsed, totalWeight, totalPrice);
    }

    fclose(file);
    free(solution);
    free(temp);
    free(items);

    return 0;
}

void recurse(int typeCount, int itemCount, int index, int weight, int maxWeight, int minWeight, int *record, item *items, item **solution, item **temp)
{
    if(weight > maxWeight)
        return;

    if((weight + minWeight) > maxWeight)
    {
        int totalPrice = 0;
        for(int i = 0; i < index; ++i)
            totalPrice += (temp[i])->value;

        if(totalPrice > *record)
        {
            *record = totalPrice;

            int i;
            for(i = 0; i < index; ++i)
                solution[i] = temp[i];

            if((i + 1) < itemCount)
                solution[i++] = NULL;
        }

        return;
    }

    for(int i = 0; i < typeCount; ++i)
    {
        if(items[i].availability > 0)
        {
            items[i].availability--;
            temp[index] = &items[i];

            recurse(typeCount, itemCount, (index + 1), (weight + items[i].weight), maxWeight, minWeight, record, items, solution, temp);

            items[i].availability++;
        }
    }

    return;
}
