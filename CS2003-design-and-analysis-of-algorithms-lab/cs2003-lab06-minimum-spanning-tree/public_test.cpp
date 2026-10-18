#include "mst_optimizer.hpp"
#include <iostream>
#include <cassert>
#include <vector>

void test_basic_kruskal() {
    // 4-vertex graph (0..3) with 5 edges
    // (0-1: 10), (0-2: 6), (0-3: 5), (1-3: 15), (2-3: 4)
    // Expected MST edges: (2-3: 4), (0-3: 5), (0-1: 10) -> Total weight = 19
    int num_vertices = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    MSTResult res = kruskal_mst(num_vertices, edges);
    assert(res.is_connected);
    assert(res.total_weight == 19);
    assert(res.edges.size() == 3);

    std::cout << "[PASS] test_basic_kruskal" << std::endl;
}

void test_basic_prim() {
    // Same 4-vertex graph
    int num_vertices = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    MSTResult res = prim_mst(num_vertices, edges);
    assert(res.is_connected);
    assert(res.total_weight == 19);
    assert(res.edges.size() == 3);

    std::cout << "[PASS] test_basic_prim" << std::endl;
}

void test_5_vertex_network() {
    // 5-vertex network
    int num_vertices = 5;
    std::vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };
    // Expected MST: (0-1: 2), (1-2: 3), (1-4: 5), (0-3: 6) -> Total weight = 16

    MSTResult k_res = kruskal_mst(num_vertices, edges);
    assert(k_res.is_connected);
    assert(k_res.total_weight == 16);
    assert(k_res.edges.size() == 4);

    MSTResult p_res = prim_mst(num_vertices, edges);
    assert(p_res.is_connected);
    assert(p_res.total_weight == 16);
    assert(p_res.edges.size() == 4);

    std::cout << "[PASS] test_5_vertex_network" << std::endl;
}

int main() {
    std::cout << "=== Public MST Test Suite ===" << std::endl;
    test_basic_kruskal();
    test_basic_prim();
    test_5_vertex_network();
    std::cout << "All public tests passed successfully!" << std::endl;
    return 0;
}
