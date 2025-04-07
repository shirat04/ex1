// shirat345@gmail.com
#include "PriorityQueue.h"
#include <iostream>

namespace graph {

    // Constructor: Initializes the priority queue with a given initial capacity.
    // Allocates memory for the queue array and sets size to 0.
    PriorityQueue::PriorityQueue(int initialCapacity)
        : capacity(initialCapacity), size(0) {
        data = new Edge[capacity];  // Dynamically allocate memory for the queue array
    }

    // Destructor: Frees the dynamically allocated memory for the queue data.
    PriorityQueue::~PriorityQueue() {
        delete[] data;  // Delete the allocated array of edges
    }

    // resize: Doubles the capacity of the priority queue when the queue is full.
    // Creates a new array with the doubled capacity, copies over existing data,
    // and deletes the old array.
    void PriorityQueue::resize() {
        int newCapacity = capacity * 2;  // Double the capacity
        Edge* newData = new Edge[newCapacity];  // Allocate a new array with the new capacity
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];  // Copy the existing data into the new array
        delete[] data;  // Delete the old array
        data = newData;  // Update the queue data pointer to the new array
        capacity = newCapacity;  // Update the capacity
    }

    // findMinIndex: Finds and returns the index of the edge with the minimum weight.
    // Scans through the queue to find the minimum weight edge.
    int PriorityQueue::findMinIndex() const {
        int minIdx = 0;  // Assume the first element is the minimum
        for (int i = 1; i < size; ++i) {
            if (data[i].weight < data[minIdx].weight)  // Compare weights
                minIdx = i;  // Update the index of the minimum weight edge
        }
        return minIdx;  // Return the index of the minimum weight edge
    }

    // insert: Adds a new edge to the priority queue.
    // If the queue is full, it will resize the array to accommodate the new edge.
    void PriorityQueue::insert(int src, int dest, int weight) {
        if (size == capacity)  // If the queue is full, resize it
            resize();
        data[size++] = {src, dest, weight};  // Add the new edge to the queue
    }

    // extractMin: Removes and returns the edge with the minimum weight from the queue.
    // The edge with the minimum weight is identified by findMinIndex.
    // After removal, the last edge is moved to the position of the removed edge, and the size is reduced.
    Edge PriorityQueue::extractMin() {
        if (isEmpty()) {
            std::cerr << "PriorityQueue is empty!\n";  // Error message if the queue is empty
            return {-1, -1, -1};  // Return an invalid edge if the queue is empty
        }

        int minIdx = findMinIndex();  // Find the index of the edge with the minimum weight
        Edge minEdge = data[minIdx];  // Store the minimum edge
        data[minIdx] = data[size - 1];  // Move the last edge to the position of the removed edge
        --size;  // Decrease the size of the queue
        return minEdge;  // Return the minimum edge
    }

    // isEmpty: Checks whether the priority queue is empty.
    // Returns true if the queue size is 0, otherwise false.
    bool PriorityQueue::isEmpty() const {
        return size == 0;  // Return true if size is 0, meaning the queue is empty
    }

}
