// shirat345@gmail.com
#pragma once
#include "Graph.h"

namespace graph {

    // The Algorithms class contains static methods that implement various graph algorithms.
    // Each algorithm operates on a graph and performs specific tasks such as searching, finding shortest paths, or finding spanning trees.
    class Algorithms {
    public:
        // bfs: Performs a Breadth-First Search (BFS) on the given graph 'g' starting from 'startVertex'.
        // It returns a new graph representing the BFS tree.
        static Graph bfs(int startVertex, const Graph& g);

        // dfs: Performs a Depth-First Search (DFS) on the given graph 'g' starting from 'startVertex'.
        // It returns a new graph representing the DFS tree (forest if graph is disconnected).
        static Graph dfs(int startVertex, const Graph& g);

        // dfsvisit: A helper function for DFS that visits vertices recursively.
        // It updates the 'dfsTree' and marks visited vertices using the 'color' array.
        static void dfsvisit(const Graph& g, Graph& dfsTree, int vertex, int* color);

        // dijkstra: Implements Dijkstra's algorithm to find the shortest paths from 'startVertex' to all other vertices in graph 'g'.
        // It returns a graph representing the shortest path tree.
        static Graph dijkstra(int startVertex, const Graph& g);

        // prim: Implements Prim's algorithm to find the Minimum Spanning Tree (MST) of the given graph 'g'.
        // It returns a graph representing the MST.
        static Graph prim(const Graph& g);

        // kruskal: Implements Kruskal's algorithm to find the Minimum Spanning Tree (MST) of the given graph 'g'.
        // It returns a graph representing the MST.
        static Graph kruskal(const Graph& g);
    };
}
