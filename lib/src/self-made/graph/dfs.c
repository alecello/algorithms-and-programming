#include "dfs.h"

static int time;

void graphDFS(Graph graph)
{
    graphRunDFS(graph, 0);

    if(graph->directionality == DIRECTED)
        graphRunDFS(graph, 1);
}

void graphRunDFS(Graph graph, int useTopological)
{
    time = 0;

    // Preserve previous topological order in case we want to use it to find connected components in directed graphs.
    if(!useTopological)
    {
        if(graph->topology != NULL)
            listDestroy(graph->topology, NULL);
        graph->topology = listInitialize();
    }

    if(graph->forest != NULL)
        listDestroy(graph->forest, graphDestroyForest);
    graph->forest   = listInitialize();


    graphSetGlobalVertexStatus(graph, UNTOUCHED);

    Node   vertexNode = listGetFirstElement((useTopological) ? graph->topology : graph->vertices);
    Vertex vertex     = (Vertex) listGetNodeData(vertexNode);

    while(vertexNode != NULL)
    {
        vertex = (Vertex) listGetNodeData(vertexNode);

        if(vertex->status == UNTOUCHED)
        {
            List tree = listInitialize();
            graphDFSRecurse(graph, vertex, tree);
            listPush(graph->forest, tree);
        }

        vertexNode = listGetNextNode(vertexNode);
    }
}

void graphDFSRecurse(Graph graph, Vertex current, List tree)
{
    listPush(tree, current);

    current->status = VISITED;
    current->startTime = time++;

    Node edgeNode = listGetFirstElement(current->edges);
    while(edgeNode != NULL)
    {
        Edge edge = (Edge) listGetNodeData(edgeNode);

        if(!(edge->disabled))
        {
            if(edge->destination->status == UNTOUCHED)
            {
                if(edge->type == UNKNOWN)
                    graphSetEdgeStatus(graph, edge->origin, edge->destination, TREE);

                graphDFSRecurse(graph, edge->destination, tree);
            }
            else if(edge->destination->status == VISITED && edge->type == UNKNOWN)
                graphSetEdgeStatus(graph, edge->origin, edge->destination, BACK);
            else if(edge->destination->status == FINISHED && edge->destination->startTime > edge->origin->startTime && edge->type == UNKNOWN)
                graphSetEdgeStatus(graph, edge->origin, edge->destination, FORWARD);
            else if(edge->destination->status == FINISHED && edge->destination->startTime < edge->origin->startTime && edge->type == UNKNOWN)
                graphSetEdgeStatus(graph, edge->origin, edge->destination, CROSS);
        }

        edgeNode = listGetNextNode(edgeNode);
    }

    current->status = FINISHED;
    current->endTime = time++;

    listPush(graph->topology, current);
}
