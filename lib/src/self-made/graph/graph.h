#ifndef __HEADER_GUARD_GRAPH_PRIVATE
#define __HEADER_GUARD_GRAPH_PRIVATE
    #include "public.h"

    #include "self-made/list.h"

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    enum vertexStatus
    {
        UNTOUCHED,
        VISITED,
        FINISHED
    };

    enum edgeType
    {
        TREE,
        BACK,
        FORWARD,
        CROSS,

        UNKNOWN
    };

    typedef enum   edgeType     EdgeType;
    typedef enum   vertexStatus Status;

    struct structEdge
    {
        Vertex          origin;                 // Originating vertex.
        Vertex          destination;            // Destination vertex.
        
        EdgeType        type;                   // Type of the edge (tree, back, forward or cross edge).
        Status          status;                 // Used by algorithms that need to know if we already used an edge.

        double          weight;                 // Weight of the edge. Always one for unweighted graphs.
        int             disabled;               // Disables the edge, as if it doesn't exist.
    };

    struct structVertex
    {
        char            *identifier;            // Identifier string of the vertex.
        int             startTime;              // Start time (visit) of the vertex.
        int             endTime;                // End time of the vertex.
        
        Status          status;                 // Current status of the vertex.
        
        List            edges;                  // Outgoing edges list.
    };

    struct structGraph
    {
        Directionality directionality;          // Graph directionality (undirected vs directed).

        List vertices;                          // List of vertices in the graph.
        List edges;                             // List of edges in the graph.
        List forest;                            // Forest of DFS trees for the graph.
        List topology;                          // Topological order of the vertices.
    };
    
    // **** SINGULAR VERTEX PROPERTY SETTERS ****
    void graphSetVertexStatus(Vertex vertex, Status status);
    
    // **** GLOBAL VERTEX PROPERTY SETTERS ****
    void graphSetGlobalVertexStatus(Graph graph, Status status);
    
    // **** SINGULAR EDGE PROPERTY SETTERS ****
    void graphSetEdgeStatus(Graph graph, Vertex origin, Vertex destination, Status status);
    void graphSetEdgeType(Graph graph, Vertex origin, Vertex destination, EdgeType type);
    void graphSetEdgeDisabled(Graph graph, Vertex origin, Vertex destination, int disabled);
    
    // **** GLOBAL EDGE PROPERTY SETTERS ****
    void graphSetGlobalEdgeStatus(Graph graph, Status status);
    void graphSetGlobalEdgeType(Graph graph, EdgeType type);
    void graphSetGlobalEdgeDisabled(Graph graph, int disabled);

    // **** MEMORY FREE FUNCTIONS ****
    int graphDestroyForest(Data data);
    int graphDestroyVertex(Data data);
    int graphDestroyEdge(Data data);
#endif