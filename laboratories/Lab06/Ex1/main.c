#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ROW 1000

typedef struct element
{
    char *string;
    int frequency;

    struct element *next;
}
element;

// Insertion is SORTED ALPHABETICALLY!
element *storeWord(element *list, char *word)
{
    for(int i = 0; i < strlen(word); ++i)
        word[i] = tolower(word[i]);

    if(list == NULL)
    {
        element *e = malloc(sizeof(element));
        e->string = strdup(word);
        e->frequency = 1;
        e->next = NULL;

        return e;
    }

    element *parent = NULL;
    element *cursor = list;

    while(cursor != NULL)
    {
        int result = strcmp(word, cursor->string);

        if(result == 0)
        {
            ++cursor->frequency;
            return list;
        }
        else if(result > 0) // Word comes after the current string: continue searching...
        {
            parent = cursor;
            cursor = cursor->next;
        }
        else // Word comes before the current string but no match has been found: need to insert!
        {
            element *e = malloc(sizeof(element));
            e->string = strdup(word);
            e->frequency = 1;
            e->next = cursor;

            if(parent == NULL)  // No parent -> word is the parent of the first element -> head insertion
                return e;
            else
            {
                parent->next = e;
                return list;
            }
        }
        
    }

    // If we reached here, it means that the word is not present in the list and comes after every word: tail insertion
    element *e = malloc(sizeof(element));
    e->string = strdup(word);
    e->frequency = 1;
    e->next = NULL;
    
    parent->next = e;

    return list;
}

int main(void)
{
    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file!\n");
        exit(1);
    }

    element *list = NULL;

    char word[MAX_ROW + 1];
    while(fscanf(input, "%s", word) != EOF)
        list = storeWord(list, word);
    
    element *current = list;
    while(current != NULL)
    {
        element *next = current->next;
        
        printf("%s %d\n", current->string, current->frequency);

        free(current->string);
        free(current);

        current = next;
    }
}