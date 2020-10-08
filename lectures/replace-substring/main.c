#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 40

int findNext(char *string, char *pattern, int from)
{
    int stringLength = strlen(string);
    int patternLength = strlen(pattern);

    for(int i = from; i <= stringLength - patternLength; ++i)
    {
        int found = 1;

        for(int j = 0; j < patternLength && found; ++j)
            if(pattern[j] != string[i+j])
                found = 0;
        
        if(found)
            return i;
    }

    return -1;
}

int main(int argc, char **argv)
{
    char pattern[MAXLEN + 1];
    char substitution[MAXLEN + 1];

    // Worst case scenario: MAXLEN occurrances of a single character that gets replaced with a MAXLEN string
    // Therefore the maximum length is MAXLEN*MAXLEN plus 1 character for the terminator.
    char final[MAXLEN*MAXLEN + 1];
    char string[MAXLEN*MAXLEN + 1];

    if(argc != 4)
    {
        printf("Usage: %s <string> <pattern> <replacement>\n", argv[0]);
        exit(1);
    }

    strcpy(string, argv[1]);
    strcpy(pattern, argv[2]);
    strcpy(substitution, argv[3]);

    printf("String: %s\nPattern: %s\nReplacement: %s\n", string, pattern, substitution);

    for(int i = 0; i < MAXLEN*MAXLEN + 1; ++i)
        final[i] = 0;

    int inputStringIndex = 0;
    int outputStringIndex = 0;
    int nextOccurrance = 0;

    do
    {
        nextOccurrance = findNext(string, pattern, inputStringIndex);

        for(; inputStringIndex < ((nextOccurrance < 0) ? strlen(string) : nextOccurrance); ++inputStringIndex, ++outputStringIndex)
            final[outputStringIndex] = string[inputStringIndex];

        for(int j = 0; j < strlen(substitution) && (nextOccurrance != -1); ++j, ++outputStringIndex)
            final[outputStringIndex] = substitution[j];

        inputStringIndex += strlen(pattern);
    }
    while(inputStringIndex < strlen(string));

    printf("\n%s\n", final);
}