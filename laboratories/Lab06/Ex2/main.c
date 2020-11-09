#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define ID_LEN 16

typedef struct employee
{
    char name[MAX_NAME + 1];
    char id[ID_LEN + 1];

    int hire_d;
    int hire_m;
    int hire_y;

    int salary;

    struct employee *prev;
    struct employee *next;
}
employee;

employee *findEmployee(employee *list, char *name)
{
    while(list != NULL)
    {
        if(!strcmp(list->name, name))
            return list;
        
        list = list->next;
    }

    return NULL;
}

void printEmployee(employee *e)
{
    printf("%s %s %02d.%02d.%04d %d\n", e->name, e->id, e->hire_d, e->hire_m, e->hire_y, e->salary);
}

int main(int argc, char **argv)
{
    char *searchName;
    char *searchCommand;

    if(argc != 3)
    {
        searchName = "Giallo_Antonio";
        searchCommand = "---+";
    }
    else
    {
        searchName = argv[1];
        searchCommand = argv[2];
    }
    

    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file!\n");
        exit(1);
    }

    employee *list = NULL;

    char name[MAX_NAME + 1];
    char id[ID_LEN + 1];

    int d;
    int m;
    int y;

    int salary;
    while(fscanf(input, " %s %s %d.%d.%d %d \n", name, id, &d, &m, &y, &salary) != EOF)
    {
        employee *e = malloc(sizeof(employee));

        e->hire_d = d;
        e->hire_m = m;
        e->hire_y = y;

        strncpy(e->id, id, (ID_LEN + 1));
        strncpy(e->name, name, (ID_LEN + 1));

        e->salary = salary;

        e->prev = NULL;
        e->next = list;

        if(list != NULL)
            e->next->prev = e;
        
        list = e;
    }

    employee *e = findEmployee(list, searchName);
    if(e == NULL)
    {
        printf("No employee named %s.\n", searchName);
        exit(0);
    }

    printEmployee(e);
    for(int i = 0; i < strlen(searchCommand); ++i)
    {
        if(searchCommand[i] == '+')
        {
            if(e->next != NULL)
                e = e->next;
            
            printEmployee(e);
        }
        else if(searchCommand[i] == '-')
        {
            if(e->prev != NULL)
                e = e->prev;
            
            printEmployee(e);
        }
    }
}