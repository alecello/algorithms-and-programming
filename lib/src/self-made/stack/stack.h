#include "public.h"
#include <stdlib.h>

struct stack_s
{
    int elements;
    item_p head;
};

struct item_s
{
    void * payload;
    char freeBehavior;

    item_p next;
};

void destroyItem(item_p item);