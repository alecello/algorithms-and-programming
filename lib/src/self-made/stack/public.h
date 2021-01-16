#ifndef __HEADER_GUARD_STACK_PUBLIC
#define __HEADER_GUARD_STACK_PUBLIC
    #define STACK_FREE_AFTER_POP 1  // Free() the payload after pop
    #define STACK_NOOP_AFTER_POP 0  // Do not free() the payload after pop

    typedef struct structStack * Stack;
    typedef struct structItem  * Item;

    typedef        void        * Data;

    Stack stackInitialize();
    Data stackPop(Stack stackPointer);

    void stackPush(Stack stackPointer, Data data, char freeBehavior);
    void stackTraverse(Stack stackPointer);
    void stackDestroy(Stack stackPointer);
    void stackSetItemDestroyCallback(int (* callback)(Data data));
    void stackSetEnumerationCallback(int (* callback)(Data data));
#endif