#ifndef __HEADER_GUARD_STACK_PUBLIC
#define __HEADER_GUARD_STACK_PUBLIC
    #define STACK_FREE_AFTER_POP 1  // Free() the payload after pop
    #define STACK_NOOP_AFTER_POP 0  // Do not free() the payload after pop

    struct stack_s;
    struct item_s;

    typedef struct stack_s stack_t;
    typedef stack_t * stack_p;

    typedef struct item_s item_t;
    typedef item_t * item_p;


    typedef void * data_t;

    stack_p stackInitialize();
    data_t stackPop(stack_p stackPointer);

    void stackPush(stack_p stackPointer, data_t payload, char freeBehavior);
    void stackTraverse(stack_p stackPointer);
    void stackDestroy(stack_p stackPointer);
    void stackSetItemDestroyCallback(int (* callback)(data_t payload));
    void stackSetEnumerationCallback(int (* callback)(data_t payload));
#endif