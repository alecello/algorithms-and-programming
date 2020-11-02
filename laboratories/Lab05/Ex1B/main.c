#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

int main(int argc, char **argv)
{
    char *input,*output;

    if(argc != 3)
    {
        input = "input.txt";
        output = "output.txt";
    }
    else
    {
        input = argv[1];
        output = argv[2];
    }

    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");

    if(in == NULL || out == NULL)
    {
        fprintf(stderr, "Error opening files.\n");
        exit(-1);
    }

    int wordCount;
    fscanf(in, "%d", &wordCount);

    char **words = malloc(wordCount * sizeof(char *));

    char buffer[MAX_WORD_LEN + 1];
    for(int i = 0; i < wordCount; ++i)
    {
        fscanf(in, "%s", buffer);

        // Later we use strcmp to compare the strings
        // Strcmp is not case-insensitive
        // So we turn everything to lowercase
        // This also prevents "Word" and "word" to count as two different entities.
        for(int i = 0; i < strlen(buffer); ++i)
            buffer[i] = tolower(buffer[i]);

        words[i] = malloc(strlen(buffer) * sizeof(char));
        strncpy(words[i], buffer, (strlen(buffer) + 1));
    }

    // Sort the words using insertion sort
    // First, sort by alphabetic order
    for(int i = 1; i < wordCount; ++i)
    {
        char *t = words[i];

        int j = (i - 1);
        while(j >= 0 && strcmp(words[j], t) > 0)
        {
            words[j+1] = words[j];
            --j;
        }

        words[j+1] = t;
    }

    fprintf(out, "%d\n", wordCount);
    for(int i = 0; i < wordCount; ++i)
        fprintf(out, "%s\n", words[i]);

    for(int i = 0; i < wordCount; ++i)
        free(words[i]);

    free(words);

    fclose(in);
    fclose(out);

    return 0;
}