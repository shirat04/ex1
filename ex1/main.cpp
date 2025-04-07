//shirat345@gmail.com
#include <iostream>
#include "Graph.h"
#include "Algorithms.h"
using namespace graph;
    
    int main() {
        // Create a graph with 5 vertices
        Graph g(5);
    
        // Add edges
        g.addEdge(0, 1, 4);   // A-B with weight 4
        g.addEdge(0, 2, 1);   // A-C with weight 1
        g.addEdge(0, 3, 3);   // A-D with weight 3
        g.addEdge(1, 2, 2);   // B-C with weight 2
        g.addEdge(1, 4, 6);   // B-E with weight 6
        g.addEdge(3, 4, 5);   // D-E with weight 5
    
        std::cout << "Original graph:" << std::endl;
        g.print_graph();

        // BFS tree from vertex 0
        std::cout << "\nBFS tree from vertex 0:" << std::endl;
        Graph bfsTree = Algorithms::bfs(0, g);
        bfsTree.print_graph();
    
        // DFS tree from vertex 0
        std::cout << "\nDFS tree from vertex 0:" << std::endl;
        Graph dfsTree = Algorithms::dfs(0, g);
        dfsTree.print_graph();
    
        // Dijkstra shortest path tree from vertex 0
        std::cout << "\nDijkstra tree from vertex 0:" << std::endl;
        Graph dijkstraTree = Algorithms::dijkstra(0, g);
        dijkstraTree.print_graph();
    
        // Prim's minimum spanning tree
        std::cout << "\nPrim tree:" << std::endl;
        Graph primTree = Algorithms::prim(g);
        primTree.print_graph();
    
        // Kruskal's minimum spanning tree
        std::cout << "\nKruskal tree:" << std::endl;
        Graph kruskalTree = Algorithms::kruskal(g);
        kruskalTree.print_graph();
    
        return 0;
    }