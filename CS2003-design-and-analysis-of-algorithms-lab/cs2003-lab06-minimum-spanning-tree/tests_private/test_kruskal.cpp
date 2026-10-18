#include "mst_optimizer.hpp"
#include <iostream>
#include <cassert>
#include <vector>

void test_dsu_basic() {
    DisjointSet dsu(5);
    assert(dsu.find(0) == 0);
    assert(dsu.find(1) == 1);
    assert(dsu.unite(0, 1) == true);
    assert(dsu.find(0) == dsu.find(1));
    assert(dsu.unite(0, 1) == false); // Already united

    dsu.unite(2, 3);
    dsu.unite(1, 2);
    assert(dsu.find(0) == dsu.find(3));

    std::cout << "[PASS] test_dsu_basic" << std::endl;
}

void test_single_vertex() {
    MSTResult res = kruskal_mst(1, {});
    assert(res.is_connected);
    assert(res.total_weight == 0);
    assert(res.edges.empty());

    std::cout << "[PASS] test_single_vertex" << std::endl;
}

void test_kruskal_equal_weights() {
    // 3 vertices forming a triangle with edge weight 1 each
    std::vector<Edge> edges = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 0, 1}
    };
    MSTResult res = kruskal_mst(3, edges);
    assert(res.is_connected);
    assert(res.total_weight == 2);
    assert(res.edges.size() == 2);

    std::cout << "[PASS] test_kruskal_equal_weights" << std::endl;
}

void test_kruskal_disconnected() {
    // 4 vertices with only 1 edge (0-1)
    std::vector<Edge> edges = {
        {0, 1, 5}
    };
    MSTResult res = kruskal_mst(4, edges);
    assert(!res.is_connected);

    std::cout << "[PASS] test_kruskal_disconnected" << std::endl;
}

void test_kruskal_negative_weights() {
    // Graph with negative edge weights
    std::vector<Edge> edges = {
        {0, 1, -5},
        {1, 2, 3},
        {2, 0, -2}
    };
    // Minimum spanning tree should pick (-5) and (-2) -> Total = -7
    MSTResult res = kruskal_mst(3, edges);
    assert(res.is_connected);
    assert(res.total_weight == -7);
    assert(res.edges.size() == 2);

    std::cout << "[PASS] test_kruskal_negative_weights" << std::endl;
}

void test_kruskal_complete_graph_k5() {
    // Complete graph K5 (vertices 0..4)
    std::vector<Edge> edges = {
        {0, 1, 1}, {0, 2, 4}, {0, 3, 3}, {0, 4, 2},
        {1, 2, 2}, {1, 3, 5}, {1, 4, 1},
        {2, 3, 1}, {2, 4, 3},
        {3, 4, 4}
    };
    // Expected MST weight:
    // Sorted edges: (0-1:1), (1-4:1), (2-3:1), (0-4:2 -> cycle since 0,1,4 connected), (1-2:2)
    // MST edges: (0-1:1), (1-4:1), (2-3:1), (1-2:2) -> Total weight = 5
    MSTResult res = kruskal_mst(5, edges);
    assert(res.is_connected);
    assert(res.total_weight == 5);
    assert(res.edges.size() == 4);

    std::cout << "[PASS] test_kruskal_complete_graph_k5" << std::endl;
}

int main() {
    std::cout << "=== Private Kruskal Test Suite ===" << std::endl;
    test_dsu_basic();
    test_single_vertex();
    test_kruskal_equal_weights();
    test_kruskal_disconnected();
    test_kruskal_negative_weights();
    test_kruskal_complete_graph_k5();
    std::cout << "All Kruskal private tests passed!" << std::endl;
    return 0;
}
