#ifndef __HEADER_GUARD_STACK_PRIVATE
#define __HEADER_GUARD_STACK_PRIVATE
    #include "public.h"
    #include <stdlib.h>

    struct structStack
    {
        int  elements;
        Item head;
    };

    struct structItem
    {
        Data data;
        Item next;
    };
#endif