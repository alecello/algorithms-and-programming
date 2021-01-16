#include "self-made/graph.h"
#include "self-made/list.h"

#include <stdio.h>

void printGraph(Graph graph);
int  printHamilton(Vertex vertex, int firstIteration);
int  printEuler(Edge edge, int firstIteration);
int  printDisconnect(Edge edge, int firstIteration);

int main(void)
{
    Graph graph = graphInitialize(UNDIRECTED);

    printf("==============================\n");

    graphAddVertex(graph, "A");
    graphAddVertex(graph, "B");
    graphAddVertex(graph, "C");
    graphAddVertex(graph, "D");

    graphAddEdge(graph, "A", "C", 1);
    graphAddEdge(graph, "A", "B", 1);
    graphAddEdge(graph, "D", "C", 1);
    graphAddEdge(graph, "D", "B", 1);

    printGraph(graph);

    printf("==============================\n");

    printf("FINDING HAMILTON CYCLE FOR NODE \"A\":");
    graphHamiltonCycle(graph, "A", printHamilton);

    printf("\n==============================\n");

    printf("FINDING EULER CYCLE FOR NODE \"A\":");
    graphEulerCycle(graph, "A", printEuler);

    printf("\n==============================\n");

    printf("DISCONNECTING GRAPH (non-balanced):\n");
    graphDisconnect(graph, 0, printDisconnect);

    printf("\n==============================\n");

    printf("DISCONNECTING GRAPH (balanced):\n");
    graphDisconnect(graph, 1, printDisconnect);

    printf("\n==============================\n");

    printf("ADDOMG EDGE \"A\" -> \"D\":\n");
    printf("ADDOMG EDGE \"B\" -> \"C\":\n");
    graphAddEdge(graph, "A", "D", 1);
    graphAddEdge(graph, "B", "C", 1);

    printGraph(graph);

    printf("==============================\n");

    printf("REMOVING VERTEX \"B\":\n");
    graphRemoveVertex(graph, "B");

    printGraph(graph);

    printf("==============================\n");

    printf("REMOVING EDGE \"A\" -> \"D\":\n");
    graphRemoveEdge(graph, "A", "D");

    printGraph(graph);

    printf("==============================\n");

    graphDestroy(graph);
}

int printVertexEdgeCallback(Edge edge)
{
    printf("\t\t%s -> %s\n", graphGetEdgeOrigin(edge), graphGetEdgeDestination(edge));
    return GRAPH_OK;
}

int printVertexCallback(Vertex vertex)
{
    printf("\tVertex [%s]:\n", graphGetVertexID(vertex));
    graphEnumerateVertexEdges(vertex, printVertexEdgeCallback);

    return GRAPH_OK;
}

void printGraph(Graph graph)
{
    printf("YOUR GRAPH HAS:\n\t- %d Vertices\n\t- %d Edges\n\n", graphGetVertexCount(graph), graphGetEdgeCount(graph));
    graphEnumerateVertices(graph, printVertexCallback);
}

int printHamilton(Vertex vertex, int firstIteration)
{
    if(firstIteration)
        printf("\n\tSOLUTION FOUND: ");
    else
        printf(" ");

    printf("%s", graphGetVertexID(vertex));

    return GRAPH_OK;
}

int printEuler(Edge edge, int firstIteration)
{
    if(firstIteration)
        printf("\n\tSOLUTION FOUND:\n\t\t");
    else
        printf("\n\t\t");

    printf("%s -> %s", graphGetEdgeOrigin(edge), graphGetEdgeDestination(edge));

    return GRAPH_OK;
}

int printDisconnect(Edge edge, int firstIteration)
{
    if(firstIteration)
        printf("\tSOLUTION FOUND:\n\t\t");
    else
        printf("\n\t\t");

    printf("%s -> %s", graphGetEdgeOrigin(edge), graphGetEdgeDestination(edge));

    return GRAPH_OK;
}
