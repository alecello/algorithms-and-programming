#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20

typedef struct element element;
struct element
{
    char *name;
    float mark;

    char sortedName;
    char sortedMark;

    element *nextName;
    element *nextMark;
};

element *listCopy(element *list);
element *readData(char *filename);
void sortInPlace(element *list, char *criterion, element **nameList, element **markList);
void writeToFile(element *list, char *filenamem, char* criterion);

int main(void)
{
    element *list;

    element *nameList;
    element *markList;

    int run = 1;
    while(run)
    {
        char command[20];
        char argument[20];

        printf(">>> ");
        scanf("%s", command);

        if(strcmp(command, "read") == 0)
        {
            scanf("%s", argument);
            list = readData(argument);
            sortInPlace(list, "name", &nameList, &markList);
        }
        else if(strcmp(command, "writen") == 0)
        {
            scanf("%s", argument);
            writeToFile(nameList, argument, "name");
        }
        else if(strcmp(command, "writem") == 0)
        {
            scanf("%s", argument);
            writeToFile(markList, argument, "mark");
        }
        else if(strcmp(command, "stop") == 0)
            run = 0;
        else
            printf("Unknown command.\n");        
    }

    element *e = list;
    while(e != NULL)
    {
        element *next = e->nextName;

        free(e->name);
        free(e);

        e = next;
    }

    return 0;
}

// This assumes that the list by name and list by mark are absolutely identical
void appendToList(element *list, element *e)
{
    while(list->nextName != NULL)
        list = list->nextName;

    list->nextName = e;
    list->nextMark = e;
}

element *readData(char *filename)
{
    element *list = NULL;

    FILE *input = fopen(filename, "r");
    if(input == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    char name[MAX_NAME_LEN + 1];
    float mark;

    while(fscanf(input, "%s %f", name, &mark) != EOF)
    {
        element *pointer = (element *) malloc(sizeof(element));

        pointer->name = strdup(name);
        pointer->mark = mark;
        pointer->sortedName = 0;
        pointer->sortedMark = 0;
        pointer->nextName = NULL;
        pointer->nextMark = NULL;

        if(list == NULL) // First element
            list = pointer;
        else
            appendToList(list, pointer);
    }

    fclose(input);
    return list;
}

int needsSwap(element *current, element *next, char *criterion)
{
    if(strcmp(criterion, "name") == 0)
        return (strcmp(current->name, next->name) > 0);
    else if(strcmp(criterion, "mark") == 0)
        return (current->mark > next->mark);
    else  // Unknown criterion
        return 0;
}

element *getParent(element *list, element *e, char *criterion)
{
    if(e == list)
        return NULL;
    else
    {
        element *parent = list;

        if(!strcmp(criterion, "name"))
            while(parent->nextName != NULL && parent->nextName != e)
                parent = parent->nextName;
        else if(!strcmp(criterion, "mark"))
            while(parent->nextMark != NULL && parent->nextMark != e)
                parent = parent->nextMark;
        else
            return NULL;

        return parent;
    }
}

void swapElements(element **list, element *pointer, element *current, char *criterion)
{
    element *pointerParent = getParent(*list, pointer, criterion);

    // We might want to update nextMark or nextName depending on what is the criterion
    element **pointerNextPointer;
    element **currentNextPointer;
    element **pParentNextPointer;

    if(!strcmp(criterion, "name"))
    {
        pointerNextPointer = &(pointer->nextName);
        currentNextPointer = &(current->nextName);
        pParentNextPointer = &(pointerParent->nextName);
    }
    else
    {
        pointerNextPointer = &(pointer->nextMark);
        currentNextPointer = &(current->nextMark);
        pParentNextPointer = &(pointerParent->nextMark);
    }

    // Now current is the element we need to swap with
    element *currentChild = *currentNextPointer;
    element *pointerChild = *pointerNextPointer;

    if(pointerParent != NULL)
        *pParentNextPointer = pointerChild;
    else
        *list = pointerChild;
    
    *pointerNextPointer = currentChild;
    *currentNextPointer = pointer;
}

void sortInPlace(element *list, char *criterion, element **nameList, element **markList)
{
    element *listName = list;
    element *listMark = list;

    element *pointerName = listName;
    element *pointerMark = listMark;

    // Last element is sorted by definition
    // At this point both lists are equal so we can just iterate on one criterion
    while(pointerName->nextName != NULL)
    {
        pointerName->sortedName = 0;
        pointerName->sortedMark = 0;
        pointerName = pointerName->nextName;
    }

    pointerName->sortedName = 1;
    pointerName->sortedMark = 1;
    
    while(listName->sortedName == 0 || listMark->sortedMark == 0)
    {
        pointerName = listName;
        pointerMark = listMark;

        while(pointerName->nextName != NULL && pointerName->nextName->sortedName == 0)
            pointerName = pointerName->nextName;

        while(pointerMark->nextMark != NULL && pointerMark->nextMark->sortedMark == 0)
            pointerMark = pointerMark->nextMark;

        element *currentName = pointerName;
        element *currentMark = pointerMark;

        while(currentName->nextName != NULL && needsSwap(pointerName, currentName->nextName, "name"))
            currentName = currentName->nextName;

        while(currentMark->nextMark != NULL && needsSwap(pointerMark, currentMark->nextMark, "mark"))
            currentMark = currentMark->nextMark;
        
        // No need to swap with itself
        if(currentName != pointerName)
            swapElements(&listName, pointerName, currentName, "name");
        
        // No need to swap with itself
        if(currentMark != pointerMark)
            swapElements(&listMark, pointerMark, currentMark, "mark");

        pointerName->sortedName = 1;
        pointerMark->sortedMark = 1;
    }

    *nameList = listName;
    *markList = listMark;
}

void writeToFile(element *list, char *filename, char *criterion)
{
    element *pointer = list;

    FILE *output = fopen(filename, "w");
    if(output == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    while(pointer != NULL)
    {
        fprintf(output, "%s %.2f\n", pointer->name, pointer->mark);

        if(!strcmp(criterion, "name"))
            pointer = pointer->nextName;
        else
            pointer = pointer->nextMark;
    }

    fclose(output);
}