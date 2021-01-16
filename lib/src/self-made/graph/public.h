#ifndef __HEADER_GUARD_GRAPH_PUBLIC
#define __HEADER_GUARD_GRAPH_PUBLIC
    #define GRAPH_OK    1
    #define GRAPH_ERROR 0

    typedef struct structGraph  * Graph;
    typedef struct structEdge   * Edge;
    typedef struct structVertex * Vertex;

    typedef enum graphDirectionality
    {
        DIRECTED,
        UNDIRECTED
    }
    Directionality;

    // ********************************************************************************
    // *                                   GRAPH.H                                    *
    // ********************************************************************************
    Graph graphInitialize(Directionality directionality);

    // **** ENUMERATION FUNCTIONS ****
    void graphEnumerateVertices(Graph graph, int (* callback)(Vertex vertex));
    void graphEnumerateEdges(Graph graph, int (* callback)(Edge edge));
    void graphEnumerateVertexEdges(Vertex vertex, int (* callback)(Edge edge));

    // **** INSERTION FUNCTIONS ****
    int graphAddVertex(Graph graph, char *identifier);
    int graphAddEdge(Graph graph, char *originID, char *destinationID, double weight);
    
    // **** REMOVAL FUNCTIONS ****
    double graphRemoveEdge(Graph graph, char * originID, char * destinationID);
    void graphRemoveVertex(Graph graph, char *ID);
    
    // **** SEARCH FUNCTIONS ****
    Vertex graphSearchVertex(Graph graph, char *ID);
    Edge graphSearchEdge(Graph graph, char *originID, char *destinationID);
    
    // **** MEMORY FREE FUNCTIONS ****
    void graphDestroy(Graph graph);

    // ********************************************************************************
    // *                                    DFS.C                                     *
    // ********************************************************************************
    void graphDFS(Graph graph);

    // ********************************************************************************
    // *                                   EULER.C                                    *
    // ********************************************************************************
    void graphEulerCycle(Graph graph, char *startID, int (* callback)(Edge edge, int firstIteration));
    void graphEulerPath(Graph graph, char *originID, char *destinationID, int (* callback)(Edge edge, int firstIteration));

    // ********************************************************************************
    // *                                  HAMILTON.C                                  *
    // ********************************************************************************
    void graphHamiltonCycle(Graph graph, char *startID, int (* callback)(Vertex vertex, int firstIteration));
    void graphHamiltonPath(Graph graph, char *originID, char *destinationID, int (* callback)(Vertex vertex, int firstIteration));

    // ********************************************************************************
    // *                                 DISCONNECT.C                                 *
    // ********************************************************************************
    void graphDisconnect(Graph graph, int balanced, int (* callback)(Edge edge, int firstIteration));

    // ********************************************************************************
    // *                                    UTILS.C                                   *
    // ********************************************************************************
    char * graphGetVertexID(Vertex vertex);
    double graphGetEdgeWeight(Graph graph, char *originID, char *destinationID);
    int graphGetVertexCount(Graph graph);
    int graphGetEdgeCount(Graph graph);
    int graphGetConnectedComponentsCount(Graph graph);
    char * graphGetEdgeOrigin(Edge edge);
    char * graphGetEdgeDestination(Edge edge);
#endif