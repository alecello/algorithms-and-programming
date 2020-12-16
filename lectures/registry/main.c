#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define FALSE 0
#define TRUE 1

typedef struct student
{
    char name[MAX + 1];
    char surname[MAX + 1];

    struct student *next;
}
student;

int orderedInsertion(student **listPointer, char *surname, char *name);

int main(void)
{
    student *list = NULL;

    orderedInsertion(&list, "Pinco", "Pallino");
    orderedInsertion(&list, "Pinco", "Pallina");
    orderedInsertion(&list, "Pluto", "Pippone");

    if(orderedInsertion(&list, "Zinco", "Pipetta") == FALSE)
        printf("Assertion #1 Failed!\n");

    if(orderedInsertion(&list, "Zinco", "Pipetta") == TRUE)
        printf("Assertion #2 Failed!\n");

    while(list != NULL)
    {
        printf("Name: %s\nSurname: %s\n\n", list->name, list->surname);

        student *tmp = list->next;
        free(list);

        list = tmp;
    }

    return 0;
}

int studentcmp(student *a, student *b)
{
    int s = strcmp(a->surname, b->surname);
    int n = strcmp(a->name, b->name);

    if(s != 0) return s; else return n;
}

int orderedInsertion(student **listPointer, char *surname, char *name)
{
    student *new = malloc(sizeof(student));
    student *list = *listPointer;

    strcpy(new->name, name);
    strcpy(new->surname, surname);

    student *parent = NULL;
    student *cursor = list;

    while(cursor != NULL && studentcmp(new, cursor) > 0)
    {
        parent = cursor;
        cursor = cursor->next;
    }

    if(cursor != NULL && studentcmp(new, cursor) == 0)
    {
        free(new);
        return FALSE;
    }

    if(parent == NULL)
    {
        new->next = list;
        *listPointer = new;
    }
    else
    {
        parent->next = new;
        new->next = cursor;
    }

    return TRUE;
}
