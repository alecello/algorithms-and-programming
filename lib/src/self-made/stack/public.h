#define STACK_FREE_AFTER_POP 1  // Free() the payload after pop
#define STACK_NOOP_AFTER_POP 0  // Do not free() the payload after pop

struct stack_s;
struct item_s;

typedef struct stack_s stack_t;
typedef stack_t * stack_p;

typedef struct item_s item_t;
typedef item_t * item_p;


typedef void * data_t;

stack_p initStack();

void   pushStack(stack_p stackPointer, data_t payload, char freeBehavior);
data_t popStack(stack_p stackPointer);

void traverseStack(stack_p stackPointer, void callback(data_t payload));

void destroyStack(stack_p stackPointer);