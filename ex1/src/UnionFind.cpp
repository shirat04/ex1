// shirat345@gmail.com
#include "UnionFind.h"
#include <climits>

// Constructor: initializes the UnionFind structure with 'n' elements.
// Each element is initially in its own set (parent points to itself).
// The rank array is used for optimizing union operations.
UnionFind::UnionFind(int n) {
    size = n;
    parent = new int[size];  // Array to store the parent of each element
    rank = new int[size];    // Array to store the rank (tree height) of each set

    // Initially, each element is its own parent, and the rank is 0
    for (int i = 0; i < size; i++) {
        parent[i] = i;  // Each element is its own parent
        rank[i] = 0;    // Rank of each element is 0 initially
    }
}

// Destructor: frees dynamically allocated memory for parent and rank arrays.
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

// Find operation with path compression.
// This method finds the root of the set containing 'x' and applies path compression
// to flatten the structure, speeding up future find operations.
int UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // Path compression: recursively find the root
    }
    return parent[x];
}

// Union operation to combine the sets containing 'x' and 'y'.
// The set with the higher rank becomes the parent of the set with the lower rank,
// ensuring that the tree remains shallow for efficiency.
void UnionFind::unionSets(int x, int y) {
    int rootX = find(x);  // Find the root of the set containing 'x'
    int rootY = find(y);  // Find the root of the set containing 'y'

    // If they are already in the same set, no union is needed
    if (rootX == rootY) return;

    // Union by rank: attach the tree with the smaller rank under the tree with the larger rank
    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;  // Make rootX the parent of rootY
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;  // Make rootY the parent of rootX
    } else {
        parent[rootY] = rootX;  // Arbitrary decision when both ranks are equal
        rank[rootX]++;  // Increment the rank of the new root
    }
}
