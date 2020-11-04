#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20

typedef struct element element;
struct element
{
    char *name;
    char sorted;
    float mark;

    element *next;
};

element *listCopy(element *list);
element *readData(char *filename);
element *sortInPlace(element *list, char *criterion);
void writeToFile(element *list, char *filename);

int main(void)
{
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
            nameList = readData(argument);
            markList = listCopy(nameList);

            nameList = sortInPlace(nameList, "name");
            markList = sortInPlace(markList, "mark");
        }
        else if(strcmp(command, "writen") == 0)
        {
            scanf("%s", argument);
            writeToFile(nameList, argument);
        }
        else if(strcmp(command, "writem") == 0)
        {
            scanf("%s", argument);
            writeToFile(markList, argument);
        }
        else if(strcmp(command, "stop") == 0)
            run = 0;
        else
            printf("Unknown command.\n");        
    }

    element *e = nameList;
    while(e != NULL)
    {
        element *next = e->next;

        free(e->name);
        free(e);

        e = next;
    }

    e = markList;
    while(e != NULL)
    {
        element *next = e->next;

        free(e->name);
        free(e);

        e = next;
    }

    return 0;
}

void appendToList(element *list, element *e)
{
    while(list->next != NULL)
        list = list->next;
    
    list->next = e;
}

element *listCopy(element *list)
{
    element *copy = NULL;

    while(list != NULL)
    {
        element *e = malloc(sizeof(element));

        e->name = strdup(list->name);
        e->mark = list->mark;
        e->next = NULL;

        if(copy != NULL)
            appendToList(copy, e);
        else
            copy = e;

        list = list->next;
    }

    return copy;
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
        pointer->sorted = 0;
        pointer->next = NULL;

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

element *getParent(element *list, element *e)
{
    if(e == list)
        return NULL;
    else
    {
        element *parent = list;

        while(parent->next != NULL && parent->next != e)
            parent = parent->next;
        
        return parent;
    }
}

element *sortInPlace(element *list, char *criterion)
{
    element *pointer = list;

    // Last element is sorted by definition
    while(pointer->next != NULL)
    {
        pointer->sorted = 0;
        pointer = pointer->next;
    }
    
    // TODO: What happens with list of one element?
    pointer->sorted = 1;
    
    while(list->sorted == 0)
    {
        pointer = list;
        while(pointer->next != NULL && pointer->next->sorted == 0)
            pointer = pointer->next;

        element *current = pointer;

        while(current->next != NULL && needsSwap(pointer, current->next, criterion))
            current = current->next; //TODO: Can this be null
        
        // No need to swap with itself
        if(current != pointer)
        {
            // Now current is the element we need to swap with
            element *currentChild = current->next;
            element *pointerChild = pointer->next;

            element *pointerParent = getParent(list, pointer);
            if(pointerParent != NULL)
                pointerParent->next = pointerChild;
            else
                list = pointerChild;
            
            pointer->next = currentChild;
            current->next = pointer;
        }

        pointer->sorted = 1;
    }

    return list;
}

void writeToFile(element *list, char *filename)
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
        pointer = pointer->next;
    }

    fclose(output);
}