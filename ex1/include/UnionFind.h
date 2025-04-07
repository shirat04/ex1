// shirat345@gmail.com
#pragma once

class UnionFind {
private:
    int* parent;  // Array to store the parent of each element. Each element points to its root.
    int* rank;    // Array to store the rank (or depth) of each tree in the union-find structure, used for optimization.
    int size;     // The total number of elements in the union-find structure.

public:
    // Constructor: Initializes the union-find structure with 'n' elements.
    // Each element starts as its own parent (i.e., they form their own disjoint sets).
    UnionFind(int n);

    // Destructor: Frees dynamically allocated memory for the 'parent' and 'rank' arrays.
    ~UnionFind();

public:
    // find: Finds the representative (or root) of the set containing element 'x'.
    // Uses path compression to optimize future queries by making elements point directly to their root.
    int find(int x);

    // unionSets: Merges the sets containing elements 'x' and 'y' into a single set.
    // The set with the larger rank becomes the parent of the smaller rank set to keep the tree balanced.
    void unionSets(int x, int y);
};
