#include "hamilton.h"

void graphHamiltonCycle(Graph graph, char *startID, int (* callback)(Vertex vertex, int firstIteration))
{
    graphHamiltonPath(graph, startID, startID, callback);
}

void graphHamiltonPath(Graph graph, char *originID, char *destinationID, int (* callback)(Vertex vertex, int firstIteration))
{
    Vertex origin = graphSearchVertex(graph, originID);
    Vertex destination = graphSearchVertex(graph, destinationID);

    if(origin == NULL || destination == NULL)
        return;

    Vertex *solution = calloc((graphGetVertexCount(graph) + 1), sizeof(*solution));
    graphSetGlobalVertexStatus(graph, UNTOUCHED);

    graphRecurseHamilton(graph, destination, origin, solution, 0, strcmp(originID, destinationID) == 0, callback);
}

void graphRecurseHamilton(Graph graph, Vertex destinationVertex, Vertex currentVertex, Vertex *solution, int count, int isCycle, int (* callback)(Vertex vertex, int firstIteration))
{
    if(count >= (graphGetVertexCount(graph) - ((isCycle) ? 0 : 1)))
    {
        if(count == (graphGetVertexCount(graph) - ((isCycle) ? 0 : 1)) && currentVertex == destinationVertex)
        {
            solution[count] = currentVertex;

            for(int i = 0; i <= count; ++i)
                callback(solution[i], !i);

            return;
        }

        return;
    }

    currentVertex->status = VISITED;
    solution[count] = currentVertex;

    Node edgeNode = listGetFirstElement(currentVertex->edges);
    while(edgeNode != NULL)
    {
        Edge edge = listGetNodeData(edgeNode);

        if(edge->destination->status == UNTOUCHED || (isCycle && count == (graphGetVertexCount(graph) - 1)  && edge->destination == destinationVertex))
            graphRecurseHamilton(graph, destinationVertex, edge->destination, solution, (count + 1), isCycle, callback);

        edgeNode = listGetNextNode(edgeNode);
    }

    currentVertex->status = UNTOUCHED;
    return;
}
