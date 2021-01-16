#ifndef __HEADER_GUARD_GRAPH_EULER
#define __HEADER_GUARD_GRAPH_EULER
    #include "graph.h"

    void graphRecurseEuler(Graph graph, Vertex currentVertex, Vertex destinationVertex, Edge *solution, int count, int (* callback)(Edge edge, int firstIteration));
#endif