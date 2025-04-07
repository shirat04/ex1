//shirat345@gmail.com
#include "Graph.h"
#include <stdexcept>
#include <iostream>

namespace graph {

    // Constructor: Initializes the graph with a specified number of vertices
    // Throws an exception if the number of vertices is non-positive
    Graph::Graph(int vertices): numVertices(vertices){ 
        if (vertices <= 0) {
            throw std::invalid_argument("Number of vertices must be positive.");
        }
        adjList = new VertexNode[vertices];  // Dynamically allocate memory for the adjacency list
        for (int i = 0; i < numVertices; i++) { 
            adjList[i].vertex = i;  // Assign the vertex number to the node
            adjList[i].neighbors = nullptr;  // Initialize the neighbors to nullptr
        }
    }

    // Destructor: Frees all dynamically allocated memory
    // Iterates through each vertex and deletes its linked list of neighbors
    Graph::~Graph() {
        for (int i = 0; i < numVertices; i++) {
            NeighborVer* curr = adjList[i].neighbors;
            while (curr) {
                NeighborVer* temp = curr;
                curr = curr->next;
                delete temp;  // Free the memory for each neighbor
            }
        }
        delete[] adjList;  // Free the memory for the adjacency list
    }

    // Returns the number of vertices in the graph
    int Graph::getNumVertices() const {
        return numVertices;
    }

    // Returns the adjacency list of the graph
    VertexNode* Graph::getAdjList() const {
        return adjList;
    }

    // Adds an undirected edge between src and dest with a given weight
    // If the edge already exists, its weight is updated
    // Throws exceptions if the vertices are invalid or if the edge is between the same vertex
    void Graph::addEdge(int src, int dest, int weight) {
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            throw std::out_of_range("Invalid vertex index.");
        }
        if(src == dest){  // Prevent adding edges to the same vertex (no loops allowed)
            throw std::invalid_argument("This is must be simple graph.");
        }
        // Check if the edge already exists from src to dest and update the weight if found
        NeighborVer* current = adjList[src].neighbors;
        while (current != nullptr) {
            if (current->vertex == dest) {
                current->weight = weight;  // Update the weight of the existing edge
                break;
            }
            current = current->next;
        }
        // Check if the edge already exists from dest to src and update the weight if found
        current = adjList[dest].neighbors;
        while (current != nullptr) {
            if (current->vertex == src) {
                current->weight = weight;  // Update the weight of the existing edge
                return;  // No need to add a new edge, it already exists
            }
            current = current->next;
        }
        // If edge does not exist, create new neighbor nodes
        NeighborVer* newNeighbor = new NeighborVer{dest, weight, adjList[src].neighbors};
        adjList[src].neighbors = newNeighbor;

        newNeighbor = new NeighborVer{src, weight, adjList[dest].neighbors};
        adjList[dest].neighbors = newNeighbor;
    }

    // Removes an undirected edge between src and dest
    // Throws an error if the edge does not exist
    void Graph::removeEdge(int src, int dest){
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            throw std::out_of_range("Invalid vertex index.");
        }
        
        bool found = false;  // Flag to check if the edge is found and removed
        
        // Remove edge from src to dest
        NeighborVer* prev = nullptr;   
        NeighborVer* curr = adjList[src].neighbors; 

        while (curr) { 
            if (curr->vertex == dest) {
                if (prev == nullptr) {  // If it's the first node in the list
                    adjList[src].neighbors = curr->next;
                } else {
                    prev->next = curr->next;  // Remove the current node
                }
                delete curr;  // Free the memory for the edge
                found = true;
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        // Remove edge from dest to src (undirected graph)
        prev = nullptr;
        curr = adjList[dest].neighbors;

        while (curr) {
            if (curr->vertex == src) {  
                if (prev == nullptr) {
                    adjList[dest].neighbors = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;  // Free the memory for the edge
                found = true;
                break; 
            }
            prev = curr;
            curr = curr->next;
        }
        
        // If the edge was not found, throw an error
        if (!found) {
            throw std::runtime_error("Error: Edge does not exist.");
        }
    }

    // Prints the adjacency list of the graph
    // Displays each vertex and its neighbors with the respective edge weights
    void Graph::print_graph() const {
        std::cout << "vertex: (neighbor, [Edge weight])\n";
        for (int i = 0; i < numVertices; i++) {
            std::cout << i << ": "; 

            NeighborVer* temp = adjList[i].neighbors;
            if (!temp) {
                std::cout << "No edges";  // If the vertex has no neighbors, print "No edges"
            } else {
                // Print all neighbors and their respective weights
                while (temp) {
                    std::cout << "(" << temp->vertex << ", [" << temp->weight << "])";

                    if (temp->next) {
                        std::cout << " - ";  // Add a separator between neighbors
                    }
                    temp = temp->next;
                }
            }

            std::cout << std::endl;
        }
    }

    // Checks whether the graph contains any negative-weight edges
    // Returns true if any edge has a negative weight
    bool Graph::hasNegativeWeights() const {
        for (int i = 0; i < numVertices; ++i) {
            NeighborVer* current = adjList[i].neighbors;
    
            while (current != nullptr) {
                if (current->weight < 0) {
                    return true;  // Return true if a negative weight is found
                }
                current = current->next;
            }
        }
        return false;  // Return false if no negative weights are found
    }

}


