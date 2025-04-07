//shirat345@gmail.com
#pragma once

namespace graph {
    /*
     * Represents a neighbor vertex in an adjacency list.
     * Each node contains:
     * - vertex: the index of the adjacent vertex.
     * - weight: the weight of the edge to this neighbor.
     * - next: pointer to the next neighbor in the list (linked list structure).
     */
    struct NeighborVer {  
        int vertex; 
        int weight; 
        NeighborVer* next; 
    };
 /*
     * Represents a vertex in the graph.
     * Each vertex contains:
     * - vertex: the index of the vertex.
     * - neighbors: a linked list of its adjacent vertices.
     */
    struct VertexNode { 
        int vertex;    
        NeighborVer* neighbors; 
    };
 /*
     * Graph class using an adjacency list representation.
     * Supports directed or undirected graphs with weighted edges.
     */
    class Graph {

        int const numVertices;        // Total number of vertices in the graph
        VertexNode* adjList;          // Array of adjacency lists (one per vertex)
       
    public:
        /*
         * Constructor: initializes the graph with a given number of vertices.
         */
        Graph(int vertices);   

        /*
         * Destructor: cleans up dynamically allocated memory.
         */
        ~Graph();          

        /*
         * Adds an edge from 'src' to 'dest' with an optional weight (default is 1).
         * If the graph is undirected, you may want to call this method twice in the implementation.
         */
        void addEdge(int src, int dest, int weight = 1); 

        /*
         * Removes the edge from 'src' to 'dest' if it exists.
         */
        void removeEdge(int src, int dest);              

        /*
         * Prints the graph in a human-readable format (e.g., adjacency list).
         */
        void print_graph() const;                       

        /*
         * Returns the number of vertices in the graph.
         */
        int getNumVertices() const;

        /*
         * Returns a pointer to the adjacency list of the graph.
         */
        VertexNode* getAdjList() const;

        /*
         * Checks if any edge in the graph has a negative weight.
         * Useful for validating input for algorithms like Dijkstra's.
         */
        bool hasNegativeWeights() const;



        
    };
}
