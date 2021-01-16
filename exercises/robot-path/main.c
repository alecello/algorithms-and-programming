#include <stdio.h>
#include <stdlib.h>

#include "self-made/stack.h"

void cover(int *steps, int n, int distance);
void calculateSequences(stack_p stack, int *steps, int n, int distance, int current);

int printStep(data_t payload);

int main(void)
{
    int stepSizes[] = {2, 6};
    int arrayLength = 2;
    int distance = 10;

    cover(stepSizes, arrayLength, distance);
}

void cover(int *steps, int n, int distance)
{
    stack_p stack = stackInitialize();
    calculateSequences(stack, steps, n, distance, 0);
    stackDestroy(stack);
}

void calculateSequences(stack_p stack, int *steps, int n, int distance, int current)
{
    if(current >= distance)
    {
        if(current == distance)
        {
            printf("SEQUENCE FOUND:\n\t");
            stackSetEnumerationCallback(printStep);
            stackTraverse(stack);
            printf("\n\n");
        }

        return;
    }

    for(int i = 0; i < n; ++i)
    {
        int *payload = malloc(sizeof(int));
        *payload = steps[i];

        stackPush(stack, payload, STACK_FREE_AFTER_POP);
        calculateSequences(stack, steps, n, distance, current + steps[i]);
        stackPop(stack);
    }
}

int printStep(data_t payload)
{
    printf("%d ", *((int *) payload));
    return 0;
}
