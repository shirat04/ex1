//shirat345@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.h"
#include "Algorithms.h"
using namespace graph;

TEST_CASE("AddEdge - Adds edge correctly") {
    Graph g(5);
    g.addEdge(0, 1, 7);

    VertexNode* adj = g.getAdjList();
    NeighborVer* neighbor = adj[0].neighbors;

    bool found = false;
    while (neighbor != nullptr) {
        if (neighbor->vertex == 1 && neighbor->weight == 7) {
            found = true;
            break;
        }
        neighbor = neighbor->next;
    }
    CHECK(found); // האם הקשת מ-0 ל-1 קיימת

    // נבדוק גם את הצד ההפוך (1 -> 0) כי הגרף הוא לא מכוון
    neighbor = adj[1].neighbors;
    found = false;
    while (neighbor != nullptr) {
        if (neighbor->vertex == 0 && neighbor->weight == 7) {
            found = true;
            break;
        }
        neighbor = neighbor->next;
    }
    CHECK(found); // האם הקשת מ-1 ל-0 קיימת
}

TEST_CASE("AddEdge - Invalid indices and self-loop") {
    Graph g(3);

    // קודקוד לא קיים
    CHECK_THROWS_AS(g.addEdge(3, 0, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(0, 5, 1), std::out_of_range);

    // קשת לעצמו
    CHECK_THROWS_AS(g.addEdge(2, 2, 1), std::invalid_argument);
}

TEST_CASE("AddEdge - Updates existing edge weight") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 1, 9); // מעדכן משקל

    VertexNode* adj = g.getAdjList();
    NeighborVer* neighbor = adj[0].neighbors;

    int weight = -1;
    while (neighbor != nullptr) {
        if (neighbor->vertex == 1) {
            weight = neighbor->weight;
            break;
        }
        neighbor = neighbor->next;
    }
    CHECK(weight == 9);

    neighbor = adj[1].neighbors;
    weight = -1;
    while (neighbor != nullptr) {
        if (neighbor->vertex == 0) {
            weight = neighbor->weight;
            break;
        }
        neighbor = neighbor->next;
    }
    CHECK(weight == 9);
}

TEST_CASE("RemoveEdge - Removes edge correctly") {
    Graph g(4);
    g.addEdge(1, 2, 4);
    g.removeEdge(1, 2);

    VertexNode* adj = g.getAdjList();

    // בדיקה שאין קשת 1 -> 2
    NeighborVer* neighbor = adj[1].neighbors;
    bool found = false;
    while (neighbor != nullptr) {
        if (neighbor->vertex == 2) {
            found = true;
            break;
        }
        neighbor = neighbor->next;
    }
    CHECK_FALSE(found);

    // בדיקה שאין קשת 2 -> 1
    neighbor = adj[2].neighbors;
    found = false;
    while (neighbor != nullptr) {
        if (neighbor->vertex == 1) {
            found = true;
            break;
        }
        neighbor = neighbor->next;
    }
    CHECK_FALSE(found);
}

TEST_CASE("RemoveEdge - Invalid indices") {
    Graph g(3);
    CHECK_THROWS_AS(g.removeEdge(-1, 0), std::out_of_range);
    CHECK_THROWS_AS(g.removeEdge(0, 4), std::out_of_range);
}

TEST_CASE("Remove edge - invalid vertex index") {
    Graph g(5);
    try {
        g.removeEdge(-1, 2); // אינדקס לא חוקי
        FAIL("Expected exception not thrown");
    } catch (const std::out_of_range& e) {
        CHECK(std::string(e.what()) == "Invalid vertex index.");
    }
}

TEST_CASE("Graph - getNumVertices") {
    Graph g(10);
    CHECK(g.getNumVertices() == 10);
}

TEST_CASE("Graph - hasNegativeWeights") {
    Graph g(2);
    g.addEdge(0, 1, -4);
    CHECK(g.hasNegativeWeights() == true);
    Graph g2(2);
    g2.addEdge(0, 1, 3);
    CHECK(g2.hasNegativeWeights() == false);
}

TEST_CASE("Graph - getAdjList") {
    Graph g(3);
    g.addEdge(0, 1);
    CHECK(g.getAdjList() != nullptr);
    CHECK(g.getAdjList()[0].neighbors != nullptr);
}

TEST_CASE("Graph - addTreeEdge") {
    Graph g(3);
    g.addTreeEdge(0, 1, 2);
    g.addTreeEdge(1, 2, 3);
    CHECK(g.getAdjList()[0].neighbors->vertex == 1);
    CHECK(g.getAdjList()[1].neighbors->vertex == 2);
}

TEST_CASE("Algorithms - BFS Tree") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    Graph bfsTree = Algorithms::bfs(0, g);
    CHECK(bfsTree.getNumVertices() == g.getNumVertices());
}

TEST_CASE("Algorithms - DFS Tree") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    Graph dfsTree = Algorithms::dfs(0, g);
    CHECK(dfsTree.getNumVertices() == g.getNumVertices());
}

TEST_CASE("Algorithms - Dijkstra") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    Graph d = Algorithms::dijkstra(0, g);
    CHECK(d.getNumVertices() == g.getNumVertices());
}

TEST_CASE("Algorithms - Prim") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    Graph mst = Algorithms::prim(g);
    CHECK(mst.getNumVertices() == g.getNumVertices());
}

TEST_CASE("Algorithms - Kruskal") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);
    Graph mst = Algorithms::kruskal(g);
    CHECK(mst.getNumVertices() == g.getNumVertices());
}
