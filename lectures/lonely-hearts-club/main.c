#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LEN 100

typedef struct characteristic
{
    char *name;
    char *value;

    struct characteristic *next;
}
characteristic;

typedef struct person
{
    char gender;
    
    char *name;
    char *surname;

    struct characteristic *characteristics;
    struct person *next;
}
person;

void appendPerson(person *list, person *element)
{
    while(list != NULL)
        list = list->next;
    
    list->next = element;
    element->next = NULL;
}

void appendCharacteristic(characteristic **listPointer, characteristic *element)
{
    if(*listPointer == NULL)
    {
        *listPointer = element;
        return;
    }

    characteristic *list = *listPointer;

    while(list->next != NULL)
        list = list->next;
    
    list->next = element;
}

void freeCharacteristics(characteristic *list)
{
    while(list != NULL)
    {
        characteristic *next = list->next;

        free(list->name);
        free(list->value);
        free(list);

        list = next;
    }
}

void freePersons(person *list)
{
    while(list != NULL)
    {
        person *next = list->next;

        freeCharacteristics(list->characteristics);
        free(list->name);
        free(list->surname);
        free(list);

        list = next;        
    }
}

person *readPersons(FILE *inputFile)
{
    // Pound, first and last name, one character for gender, one newline and null terminator and spacing in between.
    int maxLineLen = 1 + 1 + MAX_FIELD_LEN + 1 + MAX_FIELD_LEN + 1 + 1 + 1 + 1;
    char line[maxLineLen];

    int read = 0;

    char name[MAX_FIELD_LEN + 1], surname[MAX_FIELD_LEN + 1], gender;
    person *start = NULL;
    person *previous = NULL;
    characteristic *chars = NULL;
    characteristic *prev = NULL;
    while(fgets(line, maxLineLen, inputFile) != NULL)
    {
        if(line[0] == '#')
        {
            if(read > 0)
            {
                // We're reading a new person - save everything in a struct and start again
                person *new = malloc(sizeof(person));

                new->name = strdup(name);
                new->surname = strdup(surname);
                new->gender = gender;
                new->characteristics = chars;

                new->next = NULL;

                if(previous != NULL)
                    previous->next = new;
                else
                    start = new;

                previous = new;
                read = 0;
            }

            sscanf(line, "%*c%s %s %c\n", name, surname, &gender);

            chars = prev = NULL;
        }
        else
        {
            // We're reading a characteristic
            char cname[MAX_FIELD_LEN + 1], cval[MAX_FIELD_LEN + 1];
            sscanf(line, "%s %s\n", cname, cval);

            characteristic *new = malloc(sizeof(characteristic));

            new->name = strdup(cname);
            new->value = strdup(cval);
            new->next = NULL;

            if(prev != NULL)
                prev->next = new;
            else
                chars = new;
            
            prev = new;
            ++read;
        }

        if(read > 0)
        {
            // We're reading a new person - save everything in a struct and start again
            person *new = malloc(sizeof(person));

            new->name = strdup(name);
            new->surname = strdup(surname);
            new->gender = gender;
            new->characteristics = chars;

            new->next = NULL;

            if(previous != NULL)
                previous->next = new;
            else
                start = new;
        }
    }

    return start;
}

int matchCharacteristics(characteristic *needle, characteristic *haystack)
{
    int found = 0;
    while(needle != NULL)
    {
        characteristic *current = haystack;
        while(current != NULL)
        {
            if(!strcmp(needle->name, current->name) && !strcmp(needle->value, current->value))
                ++found;

            current = current->next;
        }

        needle = needle->next;
    }

    return found;
}

person *search(person *persons, char gender, characteristic *characteristics)
{
    person *match = NULL;

    int max = -1;
    while(persons != NULL)
    {
        if(persons->gender == gender)
        {
            persons = persons->next;
            continue;
        }

        int cur = matchCharacteristics(characteristics, persons->characteristics);

        if(cur > max)
        {
            max = cur;
            match = persons;
        }

        persons = persons->next;
    }

    return match;
}

int getPairsNumber(char *line, int len)
{
    char previous = ' ';
    char current = ' ';

    int wordCount = 0;

    for(int i = 0; i < len; ++i)
    {
        current = line[i];

        if(current != ' ' && previous == ' ')
            ++wordCount;
        
        previous = current;
    }

    return wordCount/2;
}

int getAttributes(char ****data)
{
    // We read the line allocating it in chunks of 10 characters
    int chunksNumber = 0;
    int chunksSize = 10;
    int lineLength = 0;;

    char *line = NULL;
    char character;

    while((character = getc(stdin)) != '\n')
    {
        if((lineLength + 1) > (chunksNumber * chunksSize))
        {
            // Reallocate the string
            line = realloc(line, (++chunksNumber * chunksSize) * sizeof(char));
        }

        line[lineLength++] = character;
    }

    line[lineLength++] = 0;

    // Shrink string to size
    line = realloc(line, lineLength * sizeof(char));

    int pairs = getPairsNumber(line, lineLength);

    // Allocate 2D array
    char ***matrix = (char ***) malloc(pairs * sizeof(char *));

    for(int i = 0; i < pairs; ++i)
        matrix[i] = (char **) malloc(2 * sizeof(char *));
    
    char *offset = line;
    for(int i = 0; i < pairs; ++i)
    {
        char k[MAX_FIELD_LEN + 1];
        char v[MAX_FIELD_LEN + 1];

        sscanf(offset, " %s %s", k, v);

        matrix[i][0] = strdup(k);
        matrix[i][1] = strdup(v);

        offset = strstr(line, v) + strlen(v);
    }

    *data = matrix;
    return pairs;
}

int runCommand(person *persons)
{
    char gender;
    scanf(" %c", &gender);

    if(gender != 'M' && gender != 'F')
    {
        if(gender == 'T')
            return 0;
        else
            return 1;
    }
    
    characteristic *characteristics = NULL;

    char ***attributes;
    int pairs = getAttributes(&attributes);

    for(int i = 0; i < pairs; ++i)
    {
        characteristic *c = malloc(sizeof(characteristic));

        c->name = attributes[i][0];
        c->value = attributes[i][1];
        c->next = NULL;

        appendCharacteristic(&characteristics, c);
    }

    person *match = search(persons, gender, characteristics);

    if(match != NULL)
        printf("It's a match!\n\tName: %s\n\tSurname: %s\n", match->name, match->surname);

    // Free the attributes matrix
    for(int i = 0; i < pairs; ++i)
    {
        // No need to free the individual string as they already get free'd by freeCharacteristics(characteristics)
        free(attributes[i]);
    }

    free(attributes);

    freeCharacteristics(characteristics);
    return 1;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }

    person *persons = readPersons(input);

    int cont = 1;
    while(cont)
        cont = runCommand(persons);

    // Terminate program
    freePersons(persons);
}