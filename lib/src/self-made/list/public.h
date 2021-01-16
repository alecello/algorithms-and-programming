#ifndef __HEADER_GUARD_LIST_PUBLIC
#define __HEADER_GUARD_LIST_PUBLIC
    typedef struct structNode * Node;
    typedef struct structList * List;
    typedef              void * Data;

    // **** INITIALIZATION FUNCTIONS ****
    List listInitialize();

    // **** INSERTION FUNCTIONS ****
    void listOrderedInsertion(List list, Data data, int (* compare)(Data a, Data b));
    void listPush(List list, Data data);

    // **** REMOVAL FUNCTIONS ****
    void listRemoveNode(List list, Node node);
    Data listPop(List list);

    // **** NODE TRAVERSAL FUNCTIONS ****
    Node listGetFirstElement(List list);
    Node listGetNextNode(Node node);
    Node listGetPreviousNode(Node node);
    int listGetSize(List list);

    // **** DATA ACQUIRING FUNCTIONS ****
    Data listGetNodeData(Node node);

    // **** ENUMERATION FUNCTIONS ****
    void listEnumerate(List list, int callback(Data data));

    // **** SEARCH FUNCTIONS ****
    Node listSearchWithData(List list, Data data);
    Node listSearchWithComparison(List list, int (* compare)(Data data));

    // **** ORDERING FUNCTIONS ****
    void listOrder(List list, int (* compare)(Data a, Data b));

    // **** LIST DESTROY FUNCTIONS ****
    void listDestroy(List list, int (* callback)(Data data));
#endif