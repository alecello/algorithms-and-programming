#include <stdio.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_STRING 100

char *inputPath, *outputPath, *string, *substitution;

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        // I should error out, but to ease debugging, I assume default values instead.
        // This way I can just launch the program from the editor without having to modify launch configuration.
        string = "test";
        substitution = "check";

        inputPath = "input.txt";
        outputPath = "output.txt";
    }

    FILE *inputFile, *outputFile;

    if((inputFile = fopen(inputPath, "r")) == NULL || (outputFile = fopen(outputPath, "w")) == NULL)
    {
        printf("Error while opening files.\n");
        return 1;
    }

    // Max characters + newline + terminator
    char line[MAX_LINE + 1 + 1];

    while(fgets(line, MAX_LINE + 1 + 1, inputFile) != NULL)
    {
        char output[MAX_LINE + 1 + 1];
        char *pointer;

        int i = 0;
        int o = 0;

        do
        {
            pointer = strstr((line + i), string);
            int to = (pointer != NULL) ? pointer - line : strlen(line);

            for(; i < to; ++i, ++o)
                output[o] = line[i];
            
            if(to != strlen(line))
            {
                for(int j = 0; j < strlen(substitution); ++j, ++o)
                    output[o] = substitution[j];
                
                i += strlen(string);
            }
        }
        while (pointer != NULL);

        output[o] = 0;
        fprintf(outputFile, "%s", output);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}