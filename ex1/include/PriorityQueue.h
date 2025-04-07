// shirat345@gmail.com
#pragma once

namespace graph {

    /*
     * Represents a weighted edge in a graph.
     * - src: source vertex of the edge
     * - dest: destination vertex of the edge
     * - weight: weight of the edge
     */
    struct Edge {
        int src;
        int dest;
        int weight;
    };

    /*
     * PriorityQueue class for managing edges based on their weights.
     * Designed for use in algorithms like Dijkstra, Prim, and Kruskal.
     */
    class PriorityQueue {
    private:
        Edge* data;          // Dynamic array to store edges
        int capacity;        // Current maximum capacity of the array
        int size;            // Current number of elements in the queue

        /*
         * Doubles the capacity of the internal array when it's full.
         */
        void resize();        

        /*
         * Returns the index of the edge with the smallest weight.
         */
        int findMinIndex() const; 

    public:
        /*
         * Constructor: initializes the priority queue with a given capacity (default is 10).
         */
        PriorityQueue(int initialCapacity = 10); 

        /*
         * Destructor: releases dynamically allocated memory.
         */
        ~PriorityQueue();                       

        /*
         * Inserts a new edge into the queue.
         */
        void insert(int src, int dest, int weight); 

        /*
         * Removes and returns the edge with the minimum weight.
         */
        Edge extractMin();                        

        /*
         * Checks whether the queue is empty.
         */
        bool isEmpty() const;                      
    };
}
