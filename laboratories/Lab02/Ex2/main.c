#include <stdio.h>
#include <string.h>
#define MAX 100

int vsequence[MAX];
int hnum = 0;
int vnum = 0;

int main(int argc, char **argv)
{
    for(int i = 0; i < MAX; ++i)
        vsequence[i] = 0;

    // MAX characters + newline + terminator
    char line[MAX + 1 + 1];
    char *filename;

    if(argc != 2)
        // Theorethically I should print an error, however to simplify debugging I assume a default filename instead.
        // This way i can launch the program from the editor without editing launch configuration.
        filename = "input.txt";
    else
        filename = argv[1];

    FILE *inputFile = fopen(filename, "r");

    while(fgets(line, MAX + 1 + 1, inputFile) != NULL)
    {
        int hsequence = 0;
    
        for(int i = 0; i < strlen(line); ++i)
        {
            if(line[i] == 'v')
                ++vsequence[i];
            else
            {
                if(vsequence[i] == 5)
                    ++vnum;

                vsequence[i] = 0;
            }

            if(line[i] == 'h')
                ++hsequence;
            else
            {
                if(hsequence == 5)
                    ++hnum;

                hsequence = 0;
            }
        }

        if(hsequence == 5)
            ++hnum;
    }

    for(int i = 0; i < MAX; ++i)
        if(vsequence[i] == 5)
            ++vnum;

    printf("hnum: %d\nvnum: %d\n", hnum, vnum);

    fclose(inputFile);
    return 0;
}