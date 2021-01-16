#include "euler.h"

void graphEulerCycle(Graph graph, char *startID, int (* callback)(Edge edge, int firstIteration))
{
    graphEulerPath(graph, startID, startID, callback);
}

void graphEulerPath(Graph graph, char *originID, char *destinationID, int (* callback)(Edge edge, int firstIteration))
{
    Vertex origin = graphSearchVertex(graph, originID);
    Vertex destination = graphSearchVertex(graph, destinationID);

    if(origin == NULL || destination == NULL)
        return;

    Edge *solution = calloc((graphGetEdgeCount(graph) + 1), sizeof(*solution));
    graphSetGlobalEdgeStatus(graph, UNTOUCHED);

    graphRecurseEuler(graph, destination, origin, solution, 0, callback);
}

void graphRecurseEuler(Graph graph, Vertex currentVertex, Vertex destinationVertex, Edge *solution, int count, int (* callback)(Edge edge, int firstIteration))
{
    if(count >= graphGetEdgeCount(graph))
    {
        if(currentVertex == destinationVertex && count == graphGetEdgeCount(graph))
        {
            for(int i = 0; i < count; ++i)
                callback(solution[i], !i);

            return;
        }

        return;
    }

    Node edgeNode = listGetFirstElement(currentVertex->edges);
    while(edgeNode != NULL)
    {
        Edge edge = listGetNodeData(edgeNode);

        solution[count] = edge;

        if(edge->status == UNTOUCHED)
        {
            graphSetEdgeStatus(graph, currentVertex, edge->destination, VISITED);
            graphRecurseEuler(graph, edge->destination, destinationVertex, solution, (count + 1), callback);
            graphSetEdgeStatus(graph, currentVertex, edge->destination, UNTOUCHED);
        }

        edgeNode = listGetNextNode(edgeNode);
    }
}
