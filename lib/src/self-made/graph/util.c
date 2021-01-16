#include "util.h"


char * graphGetVertexID(Vertex vertex)
{
    return vertex->identifier;
}

double graphGetEdgeWeight(Graph graph, char *originID, char *destinationID)
{
    Vertex origin      = graphSearchVertex(graph, originID);
    Vertex destination = graphSearchVertex(graph, destinationID);

    if(origin == NULL || destination == NULL)
        return 0.0f;

    Edge edge = graphSearchEdge(graph, origin->identifier, destination->identifier);

    if(edge == NULL)
        return 0.0f;

    return edge->weight;
}

int graphGetVertexCount(Graph graph)
{
    if(graph == NULL)
        return -1;
    else
        return listGetSize(graph->vertices);
}

int graphGetEdgeCount(Graph graph)
{
    if(graph == NULL)
        return -1;
    else
        return listGetSize(graph->edges)/((graph->directionality == UNDIRECTED) ? 2 : 1);
}

int graphGetConnectedComponentsCount(Graph graph)
{
    if(graph == NULL)
        return -1;
    else
        return listGetSize(graph->forest);
}

char * graphGetEdgeOrigin(Edge edge)
{
    if(edge == NULL)
        return NULL;
    else
        return edge->origin->identifier;
}

char * graphGetEdgeDestination(Edge edge)
{
    if(edge == NULL)
        return NULL;
    else
        return edge->destination->identifier;
}
