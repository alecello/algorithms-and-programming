#include "treePublic.h"

#define MAX_COMMAND 255

void loadData();
void searchS();
void searchN();
void save(int mode);

static node_t *bst = NULL;

int main(void)
{

    int run = 1;
    char command[MAX_COMMAND];

    while(run)
    {
        printf("Enter a command from the following list:\n");
        printf("\tload <filename> - load data from file\n");
        printf("\tsearchS <surname> <name> - search student by name\n");
        printf("\tsearchN <register number> - search student by register number\n");
        printf("\tsaveS <filename> - save student data to file ordered by name\n");
        printf("\tsaveN <filename> - save student data to file ordered by register number\n");
        printf("\tquit - terminates the program\n");
        printf(">>> ");
        scanf(" %s", command);

        if(strcmp(command, "load") == 0)
            loadData();
        else if(strcmp(command, "searchS") == 0)
            searchS();
        else if(strcmp(command, "searchN") == 0)
            searchN();
        else if(strcmp(command, "saveS") == 0)
            save(BYNAME);
        else if(strcmp(command, "saveN") == 0)
            save(BYRNUM);
        else if(strcmp(command, "quit") == 0)
            run = 0;
        else
            fprintf(stderr, "ERROR: Unknown command.\n");
    }

    printf("Terminating program...\n");
    fflush(stdout);

    if(bst != NULL)
        freeTree(bst);

    return 0;
}

void loadData()
{
    char filename[MAX_COMMAND];
    printf("Insert filename: ");
    scanf(" %s", filename);

    FILE *input = fopen(filename, "r");

    if(input == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open input file.\n");
        return;
    }

    bst = readTree(input);
    fclose(input);
}

void searchS()
{
    if(bst == NULL)
    {
        fprintf(stderr, "ERROR: Load the data first!\n");
        return;
    }

    char name[MAX_COMMAND];
    char surname[MAX_COMMAND];

    printf("Insert student identity in the form '<name> <surname>': ");
    scanf(" %s %s", surname, name);

    struct student query;

    strcpy(query.name, name);
    strcpy(query.surname, surname);

    node_t *result = search(bst, &query, BYNAME);

    if(result == NULL)
    {
        fprintf(stderr, "ERROR: Not found!\n");
        return;
    }

    data_t data = getData(result);
    writeData(stdout, data);
}

void searchN()
{
    if(bst == NULL)
    {
        fprintf(stderr, "ERROR: Load the data first!\n");
        return;
    }

    int registerNumber;
    printf("Insert registry number: ");
    scanf(" %d", &registerNumber);

    struct student query;

    query.registerNumber = registerNumber;

    node_t *result = search(bst, &query, BYRNUM);
    data_t data = getData(result);
    writeData(stdout, data);
}

void save(int mode)
{
    char filename[MAX_COMMAND];
    printf("Insert filename: ");
    scanf(" %s", filename);

    FILE *output = fopen(filename, "w");

    if(output == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open input file.\n");
        return;
    }

    writeTree(output, bst, INORDER, mode);
    fclose(output);
}
