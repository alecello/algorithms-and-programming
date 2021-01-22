#include <stdio.h>
#include <stdlib.h>

typedef struct structCondition
{
    int numVariables;   // Number of variables involved

    int *isNegated;     // Negated status array for all numVariables
    int *varNumber;     // Number of the variable for each involved variables
}
condition;

void recurse(int, int, int, int *, condition *);

int main(int argc, char **argv)
{
    char *filename;

    if(argc != 2)
    {
        // Normally print an error and exit. To aid with debugging the program, I will assume a default value instead
        // so that I can run the program directly from the IDE terminal without having to type each time the parameters.
        filename = "input.txt";
    }
    else
    {
        filename = argv[1];
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file.\n");
        exit(1);
    }

    int statements, variableCount;
    fscanf(file, " %d %d\n", &statements, &variableCount);

    condition *conditions = malloc(statements * sizeof(condition));

    for(int i = 0; i < statements; ++i)
    {
        fscanf(file, " %d", &(conditions[i].numVariables));

        conditions[i].varNumber = malloc(conditions[i].numVariables * sizeof(int));
        conditions[i].isNegated = malloc(conditions[i].numVariables * sizeof(int));

        for(int j = 0; j < conditions[i].numVariables; ++j)
        {
            int vNum;
            fscanf(file, " %d", &vNum);
            conditions[i].varNumber[j] = (vNum >= 0) ? vNum : -vNum;

            if(vNum < 0)
                conditions[i].isNegated[j] = 1;
            else
                conditions[i].isNegated[j] = 0;
        }
    }

    int *variables = calloc(variableCount, sizeof(int));
    recurse(0, variableCount, statements, variables, conditions);

    for(int i = 0; i < statements; ++i)
    {
        free(conditions[i].isNegated);
        free(conditions[i].varNumber);
    }
    free(conditions);
    free(variables);

    fclose(file);
    return 0;
}

void recurse(int index, int variableCount, int conditionCount, int *variables, condition *conditions)
{
    if(index >= variableCount)
    {
        int encounteredFalse = 0;
        for(int i = 0; i < conditionCount && !encounteredFalse; ++i)
        {
            int isTrue = 0;
            for(int j = 0; j < conditions[i].numVariables && !isTrue; ++j)
                if(variables[conditions[i].varNumber[j] - 1] - conditions[i].isNegated[j])
                    isTrue = 1;

            if(!isTrue)
            {
                encounteredFalse = 1;
            }
        }

        if(!encounteredFalse)
        {
            for(int i = 0; i < variableCount; ++i)
                printf("X%d = %d\n", (i + 1), variables[i]);

            printf("\n\n");
        }

        return;
    }

    variables[index] = 0;
    recurse((index + 1), variableCount, conditionCount, variables, conditions);

    variables[index] = 1;
    recurse((index + 1), variableCount, conditionCount, variables, conditions);

    return;
}
