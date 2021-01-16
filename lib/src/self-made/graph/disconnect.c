#include "disconnect.h"

static int (* edgeEnumerationCallback)(Edge edge, int firstItearation) = NULL;
static int edgeEnumerationCallbackFirstCall;

void graphDisconnect(Graph graph, int balanced, int (* callback)(Edge edge, int firstIteration))
{
    List solution = listInitialize();

    int status = GRAPH_ERROR;
    for(int i = 1; i < graphGetEdgeCount(graph) && status == GRAPH_ERROR; ++i)
    {
        status = graphRecursiveDisconnect(graph, solution, i, 0, balanced);
    }

    if(status == GRAPH_OK)
    {
        edgeEnumerationCallback          = callback;
        edgeEnumerationCallbackFirstCall = 1;

        listEnumerate(solution, listEdges);
    }
}

int graphRecursiveDisconnect(Graph graph, List solution, int level, int count, int balanced)
{
    if(count == level)
    {
        graphDFS(graph);

        if(graphGetConnectedComponentsCount(graph) > 1)
            if(balanced)
            {
                Node listHead = listGetFirstElement(graph->forest);
                int size = listGetSize((List) listGetNodeData(listHead));
                listHead = listGetNextNode(listHead);

                while(listHead != NULL)
                {
                    if(ABS(size - listGetSize((List) listGetNodeData(listHead))) > 1)
                        return GRAPH_ERROR;

                    listHead = listGetNextNode(listHead);
                }

                return GRAPH_OK;
            }
            else
                return GRAPH_OK;
        else
            return GRAPH_ERROR;
    }

    Node edgeNode = listGetFirstElement(graph->edges);
    while(edgeNode != NULL)
    {
        ((Edge) listGetNodeData(edgeNode))->disabled = 1;
        listPush(solution, (Edge) listGetNodeData(edgeNode));
        int status = graphRecursiveDisconnect(graph, solution, level, (count + 1), balanced);
        ((Edge) listGetNodeData(edgeNode))->disabled = 0;

        if(status == GRAPH_OK)
            return GRAPH_OK;
        else
            listPop(solution);

        edgeNode = listGetNextNode(edgeNode);
    }

    return GRAPH_ERROR;
}

int listEdges(Data data)
{
    edgeEnumerationCallback((Edge) data, edgeEnumerationCallbackFirstCall);
    edgeEnumerationCallbackFirstCall = 0;

    return GRAPH_OK;
}
