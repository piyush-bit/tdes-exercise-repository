#include "mst_optimizer.hpp"
#include <iostream>
#include <cassert>
#include <vector>

void test_prim_single_vertex() {
    MSTResult res = prim_mst(1, {});
    assert(res.is_connected);
    assert(res.total_weight == 0);
    assert(res.edges.empty());

    std::cout << "[PASS] test_prim_single_vertex" << std::endl;
}

void test_prim_star_graph() {
    // Star graph with vertex 0 at center connected to 1, 2, 3, 4
    std::vector<Edge> edges = {
        {0, 1, 3},
        {0, 2, 1},
        {0, 3, 4},
        {0, 4, 2}
    };
    MSTResult res = prim_mst(5, edges);
    assert(res.is_connected);
    assert(res.total_weight == 10);
    assert(res.edges.size() == 4);

    std::cout << "[PASS] test_prim_star_graph" << std::endl;
}

void test_prim_disconnected() {
    // 5 vertices, 2 components: (0-1: 3), (2-3: 4), (3-4: 2)
    std::vector<Edge> edges = {
        {0, 1, 3},
        {2, 3, 4},
        {3, 4, 2}
    };
    MSTResult res = prim_mst(5, edges);
    assert(!res.is_connected);

    std::cout << "[PASS] test_prim_disconnected" << std::endl;
}

void test_prim_negative_and_zero_weights() {
    // Graph with zero and negative edge weights
    std::vector<Edge> edges = {
        {0, 1, 0},
        {1, 2, -4},
        {2, 3, 2},
        {0, 3, -1}
    };
    // Expected MST: (0-1: 0), (1-2: -4), (0-3: -1) -> Total weight = -5
    MSTResult res = prim_mst(4, edges);
    assert(res.is_connected);
    assert(res.total_weight == -5);
    assert(res.edges.size() == 3);

    std::cout << "[PASS] test_prim_negative_and_zero_weights" << std::endl;
}

void test_prim_dense_graph() {
    // 6-vertex dense graph
    std::vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {1, 3, 6},
        {2, 3, 8}, {2, 4, 9}, {3, 4, 7}, {3, 5, 5}, {4, 5, 10}
    };
    // Expected MST: (1-2: 2), (0-1: 4), (1-3: 6), (3-5: 5), (3-4: 7) -> Total weight = 24
    MSTResult res = prim_mst(6, edges);
    assert(res.is_connected);
    assert(res.total_weight == 24);
    assert(res.edges.size() == 5);

    std::cout << "[PASS] test_prim_dense_graph" << std::endl;
}

int main() {
    std::cout << "=== Private Prim Test Suite ===" << std::endl;
    test_prim_single_vertex();
    test_prim_star_graph();
    test_prim_disconnected();
    test_prim_negative_and_zero_weights();
    test_prim_dense_graph();
    std::cout << "All Prim private tests passed!" << std::endl;
    return 0;
}
