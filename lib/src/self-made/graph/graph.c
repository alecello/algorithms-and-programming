#include "graph.h"

Graph graphInitialize(Directionality directionality)
{
    Graph graph = malloc(sizeof(*graph));

    if(graph != NULL)
    {
        graph->vertices = NULL;
        graph->directionality = directionality;

        graph->edges = listInitialize();
        graph->vertices = listInitialize();
    }

    return graph;
}



// **** ENUMERATION FUNCTIONS ****
void graphEnumerateVertices(Graph graph, int (* callback)(Vertex vertex))
{
    for(Node node = listGetFirstElement(graph->vertices); node != NULL; node = listGetNextNode(node))
        callback(listGetNodeData(node));
}

void graphEnumerateEdges(Graph graph, int (* callback)(Edge edge))
{
    for(Node node = listGetFirstElement(graph->edges); node != NULL; node = listGetNextNode(node))
        callback(listGetNodeData(node));
}

void graphEnumerateVertexEdges(Vertex vertex, int (* callback)(Edge edge))
{
    for(Node node = listGetFirstElement(vertex->edges); node != NULL; node = listGetNextNode(node))
        callback(listGetNodeData(node));
}



// **** INSERTION FUNCTIONS ****
int graphAddVertex(Graph graph, char *identifier)
{
    Vertex vertex = malloc(sizeof(*vertex));

    if(vertex != NULL)
    {
        vertex->identifier = strdup(identifier);
        vertex->endTime = -1;
        vertex->startTime = -1;
        vertex->status = UNTOUCHED;

        vertex->edges = listInitialize();
        listPush(graph->vertices, vertex);

        return GRAPH_OK;
    }
    else
    {
        return GRAPH_ERROR;
    }
}

int graphAddEdge(Graph graph, char *originID, char *destinationID, double weight)
{
    Vertex origin = graphSearchVertex(graph, originID);
    Vertex destination = graphSearchVertex(graph, destinationID);

    if(origin == NULL || destination == NULL)
        return GRAPH_ERROR;

    Edge edge = malloc(sizeof(*edge));

    edge->destination = destination;
    edge->origin = origin;

    edge->type = UNKNOWN;
    edge->status = UNTOUCHED;
    edge->weight = weight;
    edge->disabled = 0;

    listPush(origin->edges, edge);
    listPush(graph->edges, edge);

    if(graph->directionality == UNDIRECTED)
    {
        Edge counter = malloc(sizeof(*counter));

        counter->destination = origin;
        counter->origin = destination;

        counter->type = UNKNOWN;
        edge->status = UNTOUCHED;
        counter->weight = weight;
        edge->disabled = 0;

        listPush(destination->edges, counter);
        listPush(graph->edges, counter);
    }

    return GRAPH_OK;
}



// **** REMOVAL FUNCTIONS ****
double graphRemoveEdge(Graph graph, char * originID, char * destinationID)
{
    Vertex origin      = graphSearchVertex(graph, originID);
    Vertex destination = graphSearchVertex(graph, destinationID);

    if(origin == NULL || destination == NULL)
        return 0.0f;

    Edge forward, backward;

    forward = graphSearchEdge(graph, origin->identifier, destination->identifier);
    if(forward == NULL)
        return GRAPH_ERROR;

    double weight = forward->weight;

    listRemoveNode(origin->edges, listSearchWithData(origin->edges, forward));
    listRemoveNode(graph->edges, listSearchWithData(graph->edges, forward));

    if(graph->directionality == UNDIRECTED)
    {
        backward = graphSearchEdge(graph, destination->identifier, origin->identifier);
        if(backward == NULL)
            return GRAPH_ERROR;

        if(forward->weight != backward->weight)
            return GRAPH_ERROR;

        listRemoveNode(destination->edges, listSearchWithData(destination->edges, backward));
        listRemoveNode(graph->edges, listSearchWithData(graph->edges, backward));
    }

    return weight;
}

void graphRemoveVertex(Graph graph, char *ID)
{
    Vertex vertex = graphSearchVertex(graph, ID);
    if(vertex == NULL)
        return;

    Node edgeNode = listGetFirstElement(graph->edges);
    while(edgeNode != NULL)
    {
        Edge edge = (Edge) listGetNodeData(edgeNode);
        if(edge->origin == vertex || edge->destination == vertex)
        {
            // We don't know how many and which edges get eliminated by the following statement so we need to start
            // from the beginning of the list (maybe the next node is the counter-node of a undirected graph, maybe not).
            graphRemoveEdge(graph, edge->origin->identifier, edge->destination->identifier);
            edgeNode = listGetFirstElement(graph->edges);
        }
        else
        {
            edgeNode = listGetNextNode(edgeNode);
        }
    }

    listRemoveNode(graph->vertices, listSearchWithData(graph->vertices, vertex));
}



// **** SEARCH FUNCTIONS ****
Vertex graphSearchVertex(Graph graph, char *ID)
{
    Node vertexNode = listGetFirstElement(graph->vertices);

    while(vertexNode != NULL)
    {
        if(strcmp(((Vertex) listGetNodeData(vertexNode))->identifier, ID) == 0)
            return (Vertex) listGetNodeData(vertexNode);

        vertexNode = listGetNextNode(vertexNode);
    }

    return NULL;
}

Edge graphSearchEdge(Graph graph, char *originID, char *destinationID)
{
    Vertex origin = graphSearchVertex(graph, originID);
    Vertex destination = graphSearchVertex(graph, destinationID);

    if(origin == NULL || destination == NULL)
        return NULL;

    Node edgeNode = listGetFirstElement(origin->edges);

    while(edgeNode != NULL)
    {
        Edge edge = (Edge) listGetNodeData(edgeNode);

        if(edge->destination == destination)
            return edge;
        else
            edgeNode = listGetNextNode(edgeNode);
    }

    return NULL;
}



// **** SINGULAR VERTEX PROPERTY SETTERS ****
void graphSetVertexStatus(Vertex vertex, Status status)
{
        vertex->status = status;
}



// **** GLOBAL VERTEX PROPERTY SETTERS ****
void graphSetGlobalVertexStatus(Graph graph, Status status)
{
    Node vertexNode = listGetFirstElement(graph->vertices);

    while(vertexNode != NULL)
    {
        ((Vertex) listGetNodeData(vertexNode))->status =  status;
        vertexNode = listGetNextNode(vertexNode);
    }
}



// **** SINGULAR EDGE PROPERTY SETTERS ****
void graphSetEdgeStatus(Graph graph, Vertex origin, Vertex destination, Status status)
{
    Edge forward = graphSearchEdge(graph, origin->identifier, destination->identifier);
    if(forward != NULL)
        forward->status = status;

    if(graph->directionality == UNDIRECTED)
    {
        Edge backward = graphSearchEdge(graph, destination->identifier, origin->identifier);
        if(backward != NULL)
            backward->status = status;
    }
}

void graphSetEdgeType(Graph graph, Vertex origin, Vertex destination, EdgeType type)
{
    Edge forward = graphSearchEdge(graph, origin->identifier, destination->identifier);
    if(forward != NULL)
        forward->type = type;

    if(graph->directionality == UNDIRECTED)
    {
        Edge backward = graphSearchEdge(graph, destination->identifier, origin->identifier);
        if(backward != NULL)
            backward->type = type;
    }
}

void graphSetEdgeDisabled(Graph graph, Vertex origin, Vertex destination, int disabled)
{
    Edge forward = graphSearchEdge(graph, origin->identifier, destination->identifier);
    if(forward != NULL)
        forward->disabled = disabled;

    if(graph->directionality == UNDIRECTED)
    {
        Edge backward = graphSearchEdge(graph, destination->identifier, origin->identifier);
        if(backward != NULL)
            backward->disabled = disabled;
    }
}



// **** GLOBAL EDGE PROPERTY SETTERS ****
void graphSetGlobalEdgeStatus(Graph graph, Status status)
{
    Node edgeNode = listGetFirstElement(graph->edges);

    while(edgeNode != NULL)
    {
        ((Edge) listGetNodeData(edgeNode))->status = status;
        edgeNode = listGetNextNode(edgeNode);
    }
}

void graphSetGlobalEdgeType(Graph graph, EdgeType type)
{
    Node edgeNode = listGetFirstElement(graph->edges);

    while(edgeNode != NULL)
    {
        ((Edge) listGetNodeData(edgeNode))->type = type;
        edgeNode = listGetNextNode(edgeNode);
    }
}

void graphSetGlobalEdgeDisabled(Graph graph, int disabled)
{
    Node edgeNode = listGetFirstElement(graph->edges);

    while(edgeNode != NULL)
    {
        ((Edge) listGetNodeData(edgeNode))->disabled = disabled;
        edgeNode = listGetNextNode(edgeNode);
    }
}


// **** MEMORY FREE FUNCTIONS ****
void graphDestroy(Graph graph)
{
    listDestroy(graph->forest, graphDestroyForest);
    listDestroy(graph->vertices, graphDestroyVertex);
    listDestroy(graph->edges, graphDestroyEdge);

    listDestroy(graph->topology, NULL);
}

int graphDestroyForest(Data data)
{
    listDestroy((List) data, NULL);

    return GRAPH_OK;
}

int graphDestroyVertex(Data data)
{
    Vertex vertex = (Vertex) data;

    listDestroy(vertex->edges, NULL);
    free(vertex);

    return GRAPH_OK;
}

int graphDestroyEdge(Data data)
{
    Edge edge = (Edge) data;
    free(edge);

    return GRAPH_OK;
}
