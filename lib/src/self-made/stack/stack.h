#ifndef __HEADER_GUARD_STACK_PRIVATE
#define __HEADER_GUARD_STACK_PRIVATE
    #include "public.h"
    #include <stdlib.h>

    struct stack_s
    {
        int    elements;
        item_p head;
    };

    struct item_s
    {
        void * payload;
        item_p next;
    };
#endif