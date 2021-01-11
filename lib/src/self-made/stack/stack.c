#include "stack.h"

stack_p initStack()
{
    stack_p stack = malloc(sizeof(*stack));

    stack->elements = 0;
    stack->head = 0;

    return stack;
}

void pushStack(stack_p stackPointer, data_t payload, char freeBehavior)
{
    if(stackPointer == NULL)
        return;

    item_p new = malloc(sizeof(*new));

    new->payload = payload;
    new->next = stackPointer->head;
    new->freeBehavior = freeBehavior;

    stackPointer->head = new;
    stackPointer->elements++;
}

data_t popStack(stack_p stackPointer)
{
    if(stackPointer == NULL || stackPointer->head == NULL)
        return NULL;

    item_p next = stackPointer->head->next;
    data_t payload = stackPointer->head->payload;

    destroyItem(stackPointer->head);

    stackPointer->head = next;
    stackPointer->elements--;
    return payload;
}

void traverseStack(stack_p stackPointer, void callback(data_t payload))
{
    if(callback == NULL || stackPointer == NULL)
        return;

    item_p head = stackPointer->head;

    while(head != NULL)
    {
        callback(head->payload);
        head = head->next;
    }
}

void destroyStack(stack_p stackPointer)
{
    if(stackPointer == NULL)
        return;

    item_p head = stackPointer->head;

    while(head != NULL)
    {
        item_p next = head->next;
        destroyItem(head);

        head = next;
    }
}

void destroyItem(item_p item)
{
    if(item->freeBehavior == STACK_FREE_AFTER_POP)
        free(item->payload);

    free(item);
}
