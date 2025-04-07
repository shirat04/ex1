// shirat345@gmail.com
#include "Queue.h"
#include <iostream>

// Constructor: Initializes an empty queue with front and rear pointers set to nullptr
// and size set to 0.
Queue::Queue() : front(nullptr), rear(nullptr), size(0) { 
}

// Destructor: Frees all dynamically allocated memory by deleting all nodes in the queue.
Queue::~Queue() {
    while (!isEmpty()) {
        deleteNode();  // Repeatedly remove and delete nodes until the queue is empty
    }
}

// addNode: Adds a new node with the given value to the rear of the queue.
// If the queue is empty, both front and rear pointers are set to the new node.
void Queue::addNode(int value){
    Node* newNode = new Node{value, nullptr};  // Create a new node with the given value
    if(isEmpty()){
        // If the queue is empty, both front and rear should point to the new node
        front = rear = newNode;
    } else {
        // If the queue is not empty, add the new node at the rear and update rear pointer
        rear->next = newNode;
        rear = newNode;
    }
    size++;  // Increase the size of the queue
}

// deleteNode: Removes and returns the node at the front of the queue.
// If the queue becomes empty after deletion, rear is set to nullptr.
int Queue::deleteNode(){
    if (isEmpty()) {
        // If the queue is empty, print an error message and return -1
        std::cerr << "Error: Queue is empty!" << std::endl;
        return -1;
    }
    Node* temp = front;  // Temporary pointer to hold the node being removed
    int value = front->value;  // Store the value of the front node to return
    front = front->next;  // Move front pointer to the next node
    if (!front) {  // If the queue becomes empty, set rear to nullptr
        rear = nullptr;
    }
    delete temp;  // Delete the old front node
    size--;  // Decrease the size of the queue
    if (isEmpty()) {
        size = 0;  // Ensure size is set to 0 if the queue is empty
    }
    return value;  // Return the value of the node that was removed
}

// isEmpty: Checks if the queue is empty by verifying if the front pointer is nullptr.
bool Queue::isEmpty() const {
    return front == nullptr;  // If front is nullptr, the queue is empty
}
