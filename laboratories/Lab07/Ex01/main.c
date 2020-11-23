#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD 20
#define PRINT_ALL 1

typedef struct product
{
    char name[MAX_FIELD + 1];
    int price;

    struct product *next;
}
product;

typedef struct manufacturer
{
    char name[MAX_FIELD + 1];
    char id[MAX_FIELD + 1];
    struct product *products;

    struct manufacturer *next;
}
manufacturer;

manufacturer *findManufacturerByID(char *id, manufacturer *manufacturers);
manufacturer *findManufacturerByName(char *name, manufacturer *manufacturers);

int main(void)
{
    FILE *manufacturerFile = fopen("manufacturers.txt", "r");
    FILE *productsFile = fopen("products.txt", "r");

    if(!manufacturerFile || !productsFile)
    {
        fprintf(stderr, "An error occurred while trying to open files.\n");
        exit(1);
    }

    manufacturer *manufacturers = NULL;

    char name[MAX_FIELD + 1];
    char id[MAX_FIELD + 1];
    int price;

    // We use head insertion beause it's easy and adequate
    while(fscanf(manufacturerFile, "%s %s", name, id) != EOF)
    {
        manufacturer *e = malloc(sizeof(manufacturer));
        strncpy(e->name, name, MAX_FIELD + 1);
        strncpy(e->id, id, MAX_FIELD + 1);
        e->products = NULL;

        e->next = manufacturers;
        manufacturers = e;
    }

    while(fscanf(productsFile, "%s %s %d", id, name, &price) != EOF)
    {
        product *e = malloc(sizeof(product));
        
        strncpy(e->name, name, MAX_FIELD + 1);
        e->price = price;
        e->next = NULL;

        manufacturer *m = findManufacturerByID(id, manufacturers);
        if(m != NULL)
        {
            e->next = m->products;
            m->products = e;
        }
    }

    char input[MAX_FIELD + 1 + 1];
    while(1)
    {
        printf(">>> ");
        fgets(input, (MAX_FIELD + 2), stdin);

        if(strcmp(input, "end") == 0)
            break;

        // Search for a newline or space and replace it with a null terminator
        for(int i = 0; i < strlen(input); ++i)
            if(input[i] == ' ' || input[i] == '\n')
            {
                input[i] = 0;
                break;
            }
        
        manufacturer *m = findManufacturerByName(input, manufacturers);

        if(m != NULL)
        {
            product *p = m->products;

            while(p != NULL)
            {
                printf("\t%s (%d €)\n", p->name, p->price);
                p = p->next;
            }
        }
        else
            fprintf(stderr, "Manufacturer not found.\n");
        
    }

    // Print everything and free allocated memory
    while(manufacturers != NULL)
    {
        if(PRINT_ALL)
            printf("Manufacturer \"%s\" (ID %s):\n", manufacturers->name, manufacturers->id);

        while(manufacturers->products != NULL)
        {
            if(PRINT_ALL)
                printf("\t%s (%d €)\n", manufacturers->products->name, manufacturers->products->price);

            product *p = manufacturers->products->next;
            free(manufacturers->products);
            manufacturers->products = p;
        }

        manufacturer *m = manufacturers->next;
        free(manufacturers);
        manufacturers = m;
    }
}

manufacturer *findManufacturerByID(char *id, manufacturer *manufacturers)
{
    while(manufacturers != NULL)
    {
        if((strlen(id) == strlen(manufacturers->id)) && (strcmp(id, manufacturers->id) == 0))
            return manufacturers;
        
        manufacturers = manufacturers->next;
    }

    return NULL;
}

manufacturer *findManufacturerByName(char *name, manufacturer *manufacturers)
{
    while(manufacturers != NULL)
    {
        if((strlen(name) == strlen(manufacturers->name)) && (strcmp(name, manufacturers->name) == 0))
            return manufacturers;
        
        manufacturers = manufacturers->next;
    }

    return NULL;
}