#ifndef __HEADER_GUARD_GRAPH_HAMILTON
#define __HEADER_GUARD_GRAPH_HAMILTON
    #include "graph.h"

    void graphRecurseHamilton(Graph graph, Vertex destinationVertex, Vertex currentVertex, Vertex *solution, int count, int isCycle, int (* callback)(Vertex vertex, int firstIteration));
#endif