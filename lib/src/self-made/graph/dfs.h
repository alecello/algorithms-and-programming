#ifndef __HEADER_GUARD_GRAPH_DFS
#define __HEADER_GUARD_GRAPH_DFS
    #include "graph.h"

    void graphRunDFS(Graph graph, int useTopological);
    void graphDFSRecurse(Graph graph, Vertex current, List tree);
#endif