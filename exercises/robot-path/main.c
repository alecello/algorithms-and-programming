#include <stdio.h>
#include <stdlib.h>

#include "self-made/stack.h"

void cover(int *steps, int n, int distance);
void calculateSequences(stack_p stack, int *steps, int n, int distance, int current);
void printStep(data_t payload);

int main(void)
{
    int stepSizes[] = {2, 6};
    int arrayLength = 2;
    int distance = 10;

    cover(stepSizes, arrayLength, distance);
}

void cover(int *steps, int n, int distance)
{
    stack_p stack = initStack();
    calculateSequences(stack, steps, n, distance, 0);
}

void calculateSequences(stack_p stack, int *steps, int n, int distance, int current)
{
    if(current >= distance)
    {
        if(current == distance)
        {
            printf("SEQUENCE FOUND:\n\t");
            traverseStack(stack, printStep);
            printf("\n\n");
        }

        return;
    }

    for(int i = 0; i < n; ++i)
    {
        int *payload = malloc(sizeof(int));
        *payload = steps[i];

        pushStack(stack, payload, STACK_FREE_AFTER_POP);
        calculateSequences(stack, steps, n, distance, current + steps[i]);
        popStack(stack);
    }
}

void printStep(data_t payload)
{
    printf("%d ", *((int *) payload));
}
