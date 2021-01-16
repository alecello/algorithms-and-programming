#ifndef __HEADER_GUARD_GRAPH_DISCONNECT
#define __HEADER_GUARD_GRAPH_DISCONNECT
    #include "graph.h"

    #define ABS(x) ((x < 0) ? -x : x)

    int graphRecursiveDisconnect(Graph graph, List solution, int level, int count, int balanced);
    int listEdges(Data data);
#endif