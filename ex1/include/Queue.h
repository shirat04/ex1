// shirat345@gmail.com
#pragma once

// Node struct represents an element in the queue with an integer value and a pointer to the next node.
struct Node {
    int value;  // The value of the node (integer type)
    Node* next; // Pointer to the next node in the queue (for linked list structure)
};

class Queue {

    Node* front;  // Pointer to the front of the queue
    Node* rear;   // Pointer to the rear (end) of the queue
    int size;     // The current size of the queue (number of elements)

public:
    // Constructor: Initializes an empty queue with front and rear pointers set to nullptr and size set to 0.
    Queue();        

    // Destructor: Frees dynamically allocated memory for nodes when the queue is destroyed.
    ~Queue();       

    // addNode: Adds a new node with the given value to the rear of the queue.
    // If the queue is empty, it also sets the front pointer to the new node.
    void addNode(int value); 

    // deleteNode: Removes the node at the front of the queue and returns its value.
    // If the queue is empty, it may return an error value or handle the situation.
    int deleteNode();   

    // isEmpty: Returns true if the queue is empty (size is 0), false otherwise.
    bool isEmpty() const;  
};
