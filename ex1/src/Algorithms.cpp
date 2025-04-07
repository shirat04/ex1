// shirat345@gmail.com
#include "Algorithms.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "UnionFind.h"
#include <climits>
#include <stdexcept>

namespace graph {
    
    /*
    * Performs a Breadth-First Search (BFS) starting from the specified vertex.
    * Constructs and returns a BFS tree based on the original graph.
    * 
    * - Initializes color and distance arrays.
    * - Uses a queue to traverse nodes level-by-level.
    * - Adds tree edges to the BFS result graph.
    * - Frees dynamically allocated memory before returning.
    * 
    * Throws:
    * - invalid_argument if the graph is empty.
    * - out_of_range if the start vertex is invalid.
    */
    Graph Algorithms::bfs(int startVertex, const Graph& g) {
        // Check for edge cases where the graph is empty or the start vertex is out of bounds
        if (g.getNumVertices() == 0) {
            throw std::invalid_argument("Graph is empty, no vertices to traverse.");
        }
        if (startVertex < 0 || startVertex >= g.getNumVertices()) {
            throw std::out_of_range("Start vertex is out of valid range.");
        }

        // Initialize the BFS tree, color array (visited vertices), and distance array
        int numVertices = g.getNumVertices();
        Graph bfsTree(numVertices); 
        int* color = new int[numVertices]; 
        int* d = new int[numVertices]; 
        
        for (int i = 0; i < numVertices; i++) {
            color[i] = 0; // Unvisited
            d[i] = 1e9; // Infinite distance
        }
        
        // Initialize the start vertex as visited and distance as 0
        color[startVertex] = 1; 
        d[startVertex] = 0;
        
        Queue q; 
        q.addNode(startVertex); 
        
        // Traverse all vertices using BFS
        while (!q.isEmpty()) { 
            int v = q.deleteNode(); // Dequeue the current vertex
            NeighborVer* neighbor = g.getAdjList()[v].neighbors; 
        
            // Explore all neighbors of the current vertex
            while (neighbor) {  
                int neighbor_Vertex = neighbor->vertex;  
        
                if (color[neighbor_Vertex] == 0) { // If the neighbor hasn't been visited
                    color[neighbor_Vertex] = 1; 
                    d[neighbor_Vertex] = d[v] + 1; 
                    bfsTree.addEdge(v, neighbor_Vertex, neighbor->weight); 
                    q.addNode(neighbor_Vertex); // Enqueue the neighbor
                }
        
                neighbor = neighbor->next; 
            }
        
            color[v] = 2; // Mark the current vertex as fully processed
        }

        // Free dynamically allocated memory
        delete[] color;
        delete[] d;
        
        return bfsTree; 
    }

    /*
    * Performs a full Depth-First Search (DFS) starting from a given vertex.
    * Continues DFS on unvisited components to ensure complete coverage.
    * 
    * - Initializes a color array to track visited vertices.
    * - Recursively visits vertices using `dfsvisit`.
    * - Returns a forest representing the DFS traversal.
    * 
    * Throws:
    * - invalid_argument if the graph is empty.
    * - out_of_range if the start vertex is invalid.
    */
    Graph Algorithms::dfs(int startVertex, const Graph& g){
        // Check for edge cases where the graph is empty or the start vertex is out of bounds
        if (g.getNumVertices() == 0) {
            throw std::invalid_argument("Graph is empty, no vertices to traverse.");
        }
        if (startVertex < 0 || startVertex >= g.getNumVertices()) {
            throw std::out_of_range("Start vertex is out of valid range.");
        }

        // Initialize the DFS forest, color array (visited vertices)
        int numVertices = g.getNumVertices();
        Graph dfsForest(numVertices); 
        int* color = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            color[i] = 0; // Unvisited
        }

        // Perform DFS starting from the specified vertex
        dfsvisit(g, dfsForest, startVertex, color);

        // Explore other disconnected components (if any)
        for (int i = 0; i < numVertices; i++) {
            if (color[i] == 0) {
                dfsvisit(g, dfsForest, i, color);
            }
        }

        // Free dynamically allocated memory
        delete[] color; 
        
        return dfsForest;
    }

    /*
    * A helper recursive function used by DFS.
    * Visits all vertices connected to the given vertex.
    * 
    * - Marks the current vertex as visited (gray).
    * - Recursively visits all unvisited neighbors.
    * - Adds tree edges to the DFS forest.
    * - Marks the vertex as completely processed (black).
    */
    void Algorithms::dfsvisit(const Graph& g, Graph& dfsForest, int vertex, int* color){
        color[vertex] = 1; // Mark vertex as visited
        VertexNode* adjList = g.getAdjList(); 
        NeighborVer* neighbor = adjList[vertex].neighbors;

        while (neighbor) {
            int neighborVertex = neighbor->vertex;

            if(color[neighborVertex] == 0){ // If the neighbor hasn't been visited
                dfsForest.addEdge(vertex, neighborVertex, neighbor->weight); 
                dfsvisit(g, dfsForest, neighborVertex, color); // Recursive DFS call
            }
            neighbor = neighbor->next;
        }
        color[vertex] = 2; // Mark the vertex as fully processed
    }

    /*
    * Computes the shortest path tree from a single source using Dijkstra's algorithm.
    * 
    * - Uses a priority queue to always expand the node with the smallest tentative distance.
    * - Updates distances and parents when a shorter path is found.
    * - Builds and returns the shortest path tree as a graph.
    * 
    * Throws:
    * - invalid_argument if the graph is empty or contains negative weights.
    * - out_of_range if the start vertex is invalid.
    */
    Graph Algorithms::dijkstra(int startVertex, const Graph& g){
        // Check for edge cases where the graph is empty or the start vertex is out of bounds
        if (g.getNumVertices() == 0) {
            throw std::invalid_argument("Graph is empty, no vertices to process.");
        }
        if (startVertex < 0 || startVertex >= g.getNumVertices()) {
            throw std::out_of_range("Start vertex is out of valid range.");
        }
        if (g.hasNegativeWeights()) {
            throw std::invalid_argument("The graph contains edges with negative weights! Dijkstra's algorithm cannot operate on such a graph.");
        }

        // Initialize data structures for Dijkstra's algorithm
        int numVertices = g.getNumVertices();
        PriorityQueue pq;
        int* d = new int[numVertices]; // Stores the shortest distance from startVertex
        int* parent = new int[numVertices]; // Stores the parent of each vertex in the shortest path tree
        bool* visited = new bool[numVertices](); // Marks vertices as visited or not

        for (int i = 0; i < numVertices; i++) {
            d[i] = INT_MAX; // Initialize distances as infinity
            parent[i] = -1;  // No parent initially
        }

        d[startVertex] = 0; // Distance from start vertex to itself is 0
        pq.insert(-1, startVertex, 0); // Start the priority queue with the start vertex
        
        // Process the graph using Dijkstra's algorithm
        while (!pq.isEmpty()) {
            Edge e = pq.extractMin(); // Extract the vertex with the smallest tentative distance
            int u = e.dest;

            if (visited[u]) continue; // Skip if already processed
            visited[u] = true;

            // Relaxation of edges
            VertexNode* adjList = g.getAdjList();
            NeighborVer* neighbor = adjList[u].neighbors;
            while (neighbor) {
                int v = neighbor->vertex;
                int weight = neighbor->weight;
                if (!visited[v] && d[u] + weight < d[v]) {
                    d[v] = d[u] + weight;
                    parent[v] = u;
                    pq.insert(u, v, d[v]); // Insert the updated vertex into the priority queue
                }

                neighbor = neighbor->next; 
            }
        }

        // Construct the shortest path tree
        Graph shortestPathTree(numVertices);
        for (int i = 0; i < numVertices; i++) {
            if (parent[i] != -1) { 
                shortestPathTree.addEdge(parent[i], i, d[i] - d[parent[i]]);
            }
        }

        // Free dynamically allocated memory
        delete[] d;
        delete[] parent;
        delete[] visited;

        return shortestPathTree;
    }

    /*
    * Constructs a Minimum Spanning Tree (MST) using Prim's algorithm.
    * 
    * - Starts from vertex 0 and grows the MST by selecting the minimum weight edge.
    * - Uses a priority queue to efficiently retrieve the lowest-weight edge.
    * - Keeps track of which vertices are already included in the MST.
    * - Returns the constructed MST.
    * 
    * Throws:
    * - invalid_argument if the graph is empty.
    */
    Graph Algorithms::prim(const Graph& g){
        // Check for edge cases where the graph is empty
        if (g.getNumVertices() == 0) {
            throw std::invalid_argument("Graph is empty, no vertices to process.");
        }

        // Initialize data structures for Prim's algorithm
        int numVertices = g.getNumVertices();
        Graph mst(numVertices);
        int* key = new int[numVertices];   // Store the minimum weight edge for each vertex
        int* parent = new int[numVertices];  // Store the parent vertex in the MST
        bool* inMST = new bool[numVertices];  // Marks if the vertex is included in MST
        PriorityQueue pq; 

        for (int i = 0; i < numVertices; i++) {
            key[i] = INT_MAX; // Initialize keys to infinity
            parent[i] = -1;    // No parent initially
            inMST[i] = false;  // No vertices are in MST initially
        }

        int startVertex = 0;
        key[startVertex] = 0;     // Start from vertex 0
        pq.insert(-1, startVertex, 0); // Start the priority queue with the first vertex

        // Process the graph using Prim's algorithm
        while (!pq.isEmpty()) {
            Edge e = pq.extractMin(); // Extract the minimum weight edge
            int u = e.dest;

            if (inMST[u]) continue;  // Skip if already included in MST

            inMST[u] = true;  // Include vertex in MST

            if (e.src != -1) {  // Avoid adding the starting edge
                mst.addEdge(e.src, e.dest, e.weight);
            }

            // Relaxation of edges
            VertexNode* adjList = g.getAdjList();
            NeighborVer* neighbor = adjList[u].neighbors;
            while (neighbor) {
                int v = neighbor->vertex;
                int weight = neighbor->weight;
                if (!inMST[v] && weight < key[v]) {  // Check if edge can relax
                    key[v] = weight;
                    parent[v] = u;
                    pq.insert(u, v, weight); // Add the updated vertex to the priority queue
                }
                neighbor = neighbor->next; 
            }
        }

        // Free dynamically allocated memory
        delete[] key;
        delete[] parent;
        delete[] inMST;
    
        return mst;
    }
        /*
        * Constructs a Minimum Spanning Tree (MST) using Kruskal's algorithm.
        * 
        * - Inserts all edges into a priority queue.
        * - Uses Union-Find to avoid cycles by checking if vertices are in the same set.
        * - Adds the lowest-weight edges that do not form a cycle.
        * - Returns the constructed MST.
        * 
        * Throws:
        * - invalid_argument if the graph is empty.
        */

        Graph Algorithms::kruskal(const Graph& g) {
            // Check if the graph has vertices, throw an error if it's empty
            if (g.getNumVertices() == 0) {
                throw std::invalid_argument("Graph is empty, no edges to process.");
            }
            
            int numVertices = g.getNumVertices();  // Get the number of vertices in the graph
            PriorityQueue pq;  // Create a priority queue to store edges
            UnionFind uf(numVertices);  // Create a UnionFind structure to manage connected components
            Graph mst(numVertices);  // Create a new graph to store the resulting Minimum Spanning Tree (MST)
        
            // Traverse the adjacency list to insert all edges into the priority queue
            VertexNode* adjList = g.getAdjList();
            for (int i = 0; i < numVertices; i++) {
                NeighborVer* neighbor = adjList[i].neighbors;
                
                // Insert each edge (u, v) with its weight into the priority queue
                while (neighbor) {
                    int u = i;  // Current vertex
                    int v = neighbor->vertex;  // Neighboring vertex
                    int weight = neighbor->weight;  // Edge weight
                    
                    if (u < v) {  // To avoid duplicate edges, only insert (u, v) where u < v
                        pq.insert(u, v, weight);  // Insert the edge into the priority queue
                    }
                    neighbor = neighbor->next;
                }
            }
        
            // Process edges from the priority queue to form the MST
            while (!pq.isEmpty()) {
                Edge e = pq.extractMin();  // Extract the edge with the smallest weight
                
                int u = e.src;  // Source vertex of the edge
                int v = e.dest;  // Destination vertex of the edge
        
                // If the two vertices are not in the same set, add the edge to the MST
                if (uf.find(u) != uf.find(v)) {
                    if (uf.find(u) < uf.find(v)) {
                        mst.addEdge(u, v, e.weight);  // Add the edge (u, v) to the MST
                    } else {
                        mst.addEdge(v, u, e.weight);  // Add the edge (v, u) to the MST
                    }
                    uf.unionSets(u, v);  // Merge the sets containing u and v
                }
            }
            
            return mst;  // Return the resulting Minimum Spanning Tree
        }
        

}

    


