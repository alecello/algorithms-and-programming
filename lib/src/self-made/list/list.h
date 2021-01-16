#ifndef __HEADER_GUARD_LIST
#define __HEADER_GUARD_LIST
    #include "public.h"
    #include <stdlib.h>

    struct structNode
    {
        void * data;

        Node   next;
        Node   prev;
    };

    struct structList
    {
        Node head;
        int  elementCount;
    };

    // **** LIST DESTROY FUNCTIONS ****
    void itemDestroy(Node node, int (* callback)(Data data));
#endif