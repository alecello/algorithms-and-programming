#include "list.h"

static int (* freeCallback)(Data data) = NULL;

// **** INITIALIZATION FUNCTIONS ****
List listInitialize()
{
    List list = malloc(sizeof(*list));

    if(list != NULL)
    {
        list->head         = NULL;
        list->elementCount = 0;
    }

    return list;
}

void listSetFreeCallback(int callback(Data element))
{
    freeCallback = callback;
}



// **** INSERTION FUNCTIONS ****
void listOrderedInsertion(List list, Data data, int (* compare)(Data a, Data b))
{
    Node new = malloc(sizeof(*new));
    new->data = data;

    if(compare(list->head, data) >= 0)
    {
        listPush(list, data);
        return;
    }

    Node node = list->head;
    while(node->next != NULL)
    {
        if(compare(node->next, data) >= 0)
        {
            Node next = node->next;

            node->next = new;
            new->prev = node;

            new->next = next;
            next->prev = new;

            return;
        }

        node = node->next;
    }

    node->next = new;
    new->prev = node;
}

void listPush(List list, Data data)
{
    Node node  = malloc(sizeof(*node));
    node->data = data;
    node->next = list->head;

    node->prev = NULL;

    if(node->next != NULL)
        node->next->prev = node;

    list->head = node;
    list->elementCount++;
}



// **** REMOVAL FUNCTIONS ****
void listRemoveNode(List list, Node node)
{
    if(list->head == node)
    {
        listPop(list);
        return;
    }

    if(node->prev != NULL)
        node->prev->next = node->next;
    if(node->next != NULL)
        node->next->prev = node->prev;

    list->elementCount--;
    itemDestroy(node, NULL);
}

Data listPop(List list)
{
    Node node  = list->head;
    Data data  = node->data;

    list->head = node->next;

    if(node->next != NULL)
        node->next->prev = NULL;

    itemDestroy(node, NULL);
    list->elementCount--;

    return data;
}



// **** NODE TRAVERSAL FUNCTIONS ****
Node listGetFirstElement(List list)
{
    return list->head;
}

Node listGetNextNode(Node node)
{
    return node->next;
}

Node listGetPreviousNode(Node node)
{
    return node->prev;
}

int listGetSize(List list)
{
    if(list == NULL)
        return -1;
    else
        return list->elementCount;
}



// **** DATA ACQUIRING FUNCTIONS ****
Data listGetNodeData(Node node)
{
    return node->data;
}



// **** ENUMERATION FUNCTIONS ****
void listEnumerate(List list, int callback(Data data))
{
    if(callback == NULL)
        return;

    Node pointer = list->head;

    while(pointer != NULL)
    {
        callback(pointer->data);
        pointer = pointer->next;
    }
}



// **** SEARCH FUNCTIONS ****
Node listSearchWithData(List list, Data data)
{
    Node pointer = list->head;

    while(pointer != NULL)
    {
        if(pointer->data == data)
            return pointer;

        pointer = pointer->next;
    }

    return NULL;
}

Node listSearchWithComparison(List list, int (* compare)(Data data))
{
    Node pointer = list->head;

    while(pointer != NULL)
        if(compare(pointer->data) == 0)
            return pointer;

    return NULL;
}



// **** ORDERING FUNCTIONS ****
void listOrder(List list, int (* compare)(Data a, Data b))
{
    Node *pointer = NULL;
    Node lastSwap = NULL;

    int swapped;

    do
    {
        pointer = &(list->head);
        swapped = 0;

        while((*pointer) != NULL && (*pointer) != lastSwap)
        {
            if((*pointer)->next != NULL && compare(*pointer, (*pointer)->next) > 0)
            {
                swapped = 1;
                lastSwap = (*pointer)->next;

                Node first  = *pointer;
                Node second = first->next;
                Node third  = second->next;

                first->next = third;
                second->next = first;

                second->prev = first->prev;
                first->prev = second;

                if(third != NULL)
                    third->prev = first;

                (*pointer) = second;
            }

            pointer = &((*pointer)->next);
        }
    }
    while (swapped != 0);
}



// **** LIST DESTROY FUNCTIONS ****
void listDestroy(List list, int (* callback)(Data data))
{
    Node next, pointer = list->head;

    while(pointer != NULL)
    {
        next = pointer->next;
        itemDestroy(pointer, callback);
        pointer = next;
    }

    free(list);
}

void itemDestroy(Node node, int (* callback)(Data data))
{
    if(callback == NULL && freeCallback != NULL)
        freeCallback(node->data);
    else if(callback != NULL)
        callback(node->data);

    free(node);
}
