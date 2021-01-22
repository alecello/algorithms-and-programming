#define MAX_NAME 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct structEdge
{
    char a[MAX_NAME + 1];
    char b[MAX_NAME + 1];

    struct structEdge *next;
}
edge;

typedef struct structVertex
{
    char id[MAX_NAME + 1];
    int included;

    struct structVertex *next;
}
vertex;

vertex *findVertex(vertex *list, char *id)
{
    while(list != NULL)
    {
        if(strcmp(id, list->id) == 0)
            return list;

        list = list->next;
    }

    return NULL;
}

vertex * insertVertex(vertex *list, char *id)
{
    if(findVertex(list, id) == NULL)
    {
        vertex *new = malloc(sizeof(vertex));

        strcpy(new->id, id);
        new->included = 0;

        new->next = list;
        return new;
    }

    return list;
}

void readEdge(char *a, char *b, vertex **vListPointer, edge **eListPointer)
{
    *vListPointer = insertVertex(*vListPointer, a);
    *vListPointer = insertVertex(*vListPointer, b);

    // We assume duplicate edges are not inside the file (each edge is unique)
    // Even if edges are duplicate the program should still work.
    edge *new = malloc(sizeof(edge));

    strcpy(new->a, a);
    strcpy(new->b, b);

    new->next = *eListPointer;
    *eListPointer = new;
}

int verify(vertex *vList, edge *eList)
{
    while(eList != NULL)
    {
        if(findVertex(vList, eList->a)->included || findVertex(vList, eList->b)->included)
            eList = eList->next;
        else
            return 0;
    }

    return 1;
}

int recurse(vertex *list, vertex *current, edge *edges)
{
    if(current == NULL)
    {
        int retval = verify(list, edges);
        if(retval)
        {
            printf("{");

            vertex *pointer = list;
            while(pointer != NULL)
            {
                if(pointer->included)
                    printf(" %s", pointer->id);

                pointer = pointer->next;
            }

            printf(" }\n");
        }

        return retval;
    }

    current->included = 0;
    if(recurse(list, current->next, edges))
        return 1;

    current->included = 1;
    if(recurse(list, current->next, edges))
        return 1;

    return 0;
}

int main(int argc, char **argv)
{
    char *filename;

    if(argc == 1)
    {
        filename = "input.txt";
    }
    else if(argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        fprintf(stderr, "Usage: %s <filename>\n\nDefault filename, if not specified, is 'input.txt'\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Error: failed to open file.\n");
        exit(1);
    }

    vertex *vList = NULL;
    edge   *eList = NULL;

    char a[MAX_NAME + 1], b[MAX_NAME + 1];
    while(fscanf(file, "%s %s", a, b) != EOF)
        readEdge(a, b, &vList, &eList);

    if(!recurse(vList, vList, eList))
        printf("No solution found.\n");

    fclose(file);

    while(vList != NULL)
    {
        vertex *next = vList->next;
        free(vList);

        vList = next;
    }

    while(eList != NULL)
    {
        edge *next = eList->next;
        free(eList);

        eList = next;
    }

    return 0;
}
