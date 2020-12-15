#include <stdio.h>
#include <string.h>

#include "course-provided/hashtable-struct.h"
#include "course-provided/bst-struct.h"

#define ID_LEN 9
#define NAME_MAX 100

typedef struct item
{
    char *registerNumber;
    char *lastName;

    int creditLoaded;
    int creditPassed;
}
item;

int BSTTraversalCallback(node_t *node);
int BSTFreeCallback(node_t *node);
int BSTcompareCallback(data_t one, data_t two);
int BSTreadCallback(FILE *file, data_t *data);
void BSTwriteCallback(FILE *file, data_t data);
void freeCallback(data_t *data);
void STItemShowCallback(Item STItem);
void listAndBST();

static ST hashtable;
static node_t *bst;
static FILE *output;

int main(int argc, char **argv)
{
    char *firstPath;
    char *secondPath;

    if(argc != 3)
    {
        firstPath = "input.txt";
        secondPath = "output.txt";
    }
    else
    {
        firstPath = argv[1];
        secondPath = argv[2];
    }

    FILE *input = fopen(firstPath, "r");
    output = fopen(secondPath, "w");

    if(input == NULL || output == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open files!\n");
        return 1;
    }

    // Read and store the input file
    bst = createEmptyTree();
    hashtable = STinit(100);

    BSTinitialzieCallbacks(BSTcompareCallback, NULL, NULL);
    STInitializeCallback(STItemShowCallback, NULL, NULL);

    char registerNumber[ID_LEN + 1];
    char lastName[NAME_MAX + 1];

    int creditLoaded = 0;
    int creditPassed = 0;

    while(fscanf(input, "%s %s %d %d\n", registerNumber, lastName, &creditLoaded, &creditPassed) != EOF)
    {
        item *new = malloc(sizeof(item));

        new->registerNumber = strdup(registerNumber);
        new->lastName = strdup(lastName);
        new->creditLoaded = creditLoaded;
        new->creditPassed = creditPassed;

        bst = insert(bst, new);
    }

    visitTree(bst, INORDER, BSTTraversalCallback);
    STdisplay(hashtable, output);
    fclose(output);

    listAndBST();

    // Clean up and exit
    visitTree(bst, INORDER, BSTFreeCallback);
    freeTree(bst);

    fclose(input);

    return 0;
}

int BSTTraversalCallback(node_t *node)
{
    item *element = getData(node);
    Item i = ITEMcreate(element->registerNumber, element);

    STinsert(hashtable, i);

    return CONTINUE_TRAVERSAL;
}

int BSTFreeCallback(node_t *node)
{
    item *element = getData(node);

    free(element->lastName);
    free(element->registerNumber);
    free(element);

    return CONTINUE_TRAVERSAL;
}

int BSTcompareCallback(data_t one, data_t two)
{
    item *e1 = (item *) one;
    item *e2 = (item *) two;

    return(strcmp(e1->registerNumber, e2->registerNumber));
}

void STItemShowCallback(Item STItem)
{
    item *data = (item *) ITEMGetValue(STItem);
    fprintf(output, "   register no. = \"%s\"    name = \"%s\"    creditLoaded = %d    creditPassed= %d", data->registerNumber, data->lastName, data->creditLoaded, data->creditPassed);
}

void listAndBST()
{
    link list = listUnique(hashtable);
    item *cursor = malloc(sizeof(*cursor));

    while(list != NULL)
    {
        char *key = KEYget(getItemFromLink(list));
        cursor->registerNumber = strdup(key);

        int level = getDistance(bst, cursor);
        printf("Register number: %s Level: %d\n", key, level);

        free(cursor->registerNumber);

        list = getNext(list);
    }
}
