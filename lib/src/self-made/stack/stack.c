#include "stack.h"

static int (* itemDestroyCallback)(Data) = NULL;
static int (* enumerationCallback)(Data) = NULL;

Stack stackInitialize()
{
    Stack stack = malloc(sizeof(*stack));

    stack->elements = 0;
    stack->head = 0;

    return stack;
}

void stackPush(Stack stackPointer, Data data, char freeBehavior)
{
    if(stackPointer == NULL)
        return;

    Item new = malloc(sizeof(*new));

    new->data = data;
    new->next = stackPointer->head;

    stackPointer->head = new;
    stackPointer->elements++;
}

Data stackPop(Stack stackPointer)
{
    if(stackPointer == NULL || stackPointer->head == NULL)
        return NULL;

    Item next = stackPointer->head->next;
    Data data = stackPointer->head->data;

    if(itemDestroyCallback != NULL)
        itemDestroyCallback(stackPointer->head->data);

    free(stackPointer->head);

    stackPointer->head = next;
    stackPointer->elements--;
    return data;
}

void stackTraverse(Stack stackPointer)
{
    if(enumerationCallback == NULL || stackPointer == NULL)
        return;

    Item head = stackPointer->head;

    while(head != NULL)
    {
        enumerationCallback(head->data);
        head = head->next;
    }
}

void stackDestroy(Stack stackPointer)
{
    if(stackPointer == NULL)
        return;

    Item head = stackPointer->head;

    while(head != NULL)
    {
        Item next = head->next;
        if(itemDestroyCallback != NULL)
            itemDestroyCallback(head->data);

        head = next;
    }

    free(stackPointer);
}

void stackSetItemDestroyCallback(int (* callback)(Data data))
{
    itemDestroyCallback = callback;
}

void stackSetEnumerationCallback(int (* callback)(Data data))
{
    enumerationCallback = callback;
}
