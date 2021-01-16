#include "stack.h"

static int (* itemDestroyCallback)(data_t) = NULL;
static int (* enumerationCallback)(data_t) = NULL;

stack_p stackInitialize()
{
    stack_p stack = malloc(sizeof(*stack));

    stack->elements = 0;
    stack->head = 0;

    return stack;
}

void stackPush(stack_p stackPointer, data_t payload, char freeBehavior)
{
    if(stackPointer == NULL)
        return;

    item_p new = malloc(sizeof(*new));

    new->payload = payload;
    new->next = stackPointer->head;

    stackPointer->head = new;
    stackPointer->elements++;
}

data_t stackPop(stack_p stackPointer)
{
    if(stackPointer == NULL || stackPointer->head == NULL)
        return NULL;

    item_p next = stackPointer->head->next;
    data_t payload = stackPointer->head->payload;

    if(itemDestroyCallback != NULL)
        itemDestroyCallback(stackPointer->head->payload);

    free(stackPointer->head);

    stackPointer->head = next;
    stackPointer->elements--;
    return payload;
}

void stackTraverse(stack_p stackPointer)
{
    if(enumerationCallback == NULL || stackPointer == NULL)
        return;

    item_p head = stackPointer->head;

    while(head != NULL)
    {
        enumerationCallback(head->payload);
        head = head->next;
    }
}

void stackDestroy(stack_p stackPointer)
{
    if(stackPointer == NULL)
        return;

    item_p head = stackPointer->head;

    while(head != NULL)
    {
        item_p next = head->next;
        if(itemDestroyCallback != NULL)
            itemDestroyCallback(head->payload);

        head = next;
    }

    free(stackPointer);
}

void stackSetItemDestroyCallback(int (* callback)(data_t payload))
{
    itemDestroyCallback = callback;
}

void stackSetEnumerationCallback(int (* callback)(data_t payload))
{
    enumerationCallback = callback;
}
