#include "shortest_path.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>

static bool double_equals(double a, double b) {
    if (std::isinf(a) && std::isinf(b)) return true;
    return std::abs(a - b) < 1e-6;
}

int main() {
    std::cout << "Running Private Tests for Dijkstra's Algorithm...\n";

    // 1. Invalid inputs validation
    {
        std::vector<Edge> edges = {{0, 1, 5.0}};
        assert(!dijkstra_shortest_path(0, edges, 0).success);
        assert(!dijkstra_shortest_path(2, edges, -1).success);
        assert(!dijkstra_shortest_path(2, edges, 2).success);

        // Edge with negative weight
        std::vector<Edge> neg_edges = {{0, 1, -1.0}};
        assert(!dijkstra_shortest_path(2, neg_edges, 0).success);

        // Edge with out-of-bounds nodes
        std::vector<Edge> oob_edges = {{0, 5, 2.0}};
        assert(!dijkstra_shortest_path(3, oob_edges, 0).success);
    }

    // 2. Single node graph
    {
        ShortestPathResult res = dijkstra_shortest_path(1, {}, 0);
        assert(res.success);
        assert(!res.has_negative_cycle);
        assert(double_equals(res.distances[0], 0.0));
        assert(res.parent[0] == -1);
        assert(reconstruct_path(0, 0, res.parent) == std::vector<int>{0});
    }

    // 3. Disconnected graph
    {
        int num_nodes = 4;
        std::vector<Edge> edges = {
            {0, 1, 2.5},
            {2, 3, 1.2}
        };

        ShortestPathResult res = dijkstra_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(double_equals(res.distances[0], 0.0));
        assert(double_equals(res.distances[1], 2.5));
        assert(std::isinf(res.distances[2]));
        assert(std::isinf(res.distances[3]));

        assert(reconstruct_path(0, 1, res.parent) == (std::vector<int>{0, 1}));
        assert(reconstruct_path(0, 2, res.parent).empty());
        assert(reconstruct_path(0, 3, res.parent).empty());
    }

    // 4. Complex Multi-route graph
    {
        int num_nodes = 6;
        std::vector<Edge> edges = {
            {0, 1, 7.0}, {0, 2, 9.0}, {0, 5, 14.0},
            {1, 2, 10.0}, {1, 3, 15.0},
            {2, 3, 11.0}, {2, 5, 2.0},
            {3, 4, 6.0},
            {4, 5, 9.0}
        };

        ShortestPathResult res = dijkstra_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(double_equals(res.distances[0], 0.0));
        assert(double_equals(res.distances[1], 7.0));
        assert(double_equals(res.distances[2], 9.0));
        assert(double_equals(res.distances[3], 20.0)); // 0->2->3 = 9 + 11 = 20
        assert(double_equals(res.distances[4], 26.0)); // 0->2->3->4 = 20 + 6 = 26
        assert(double_equals(res.distances[5], 11.0)); // 0->2->5 = 9 + 2 = 11 < 14

        assert(reconstruct_path(0, 5, res.parent) == (std::vector<int>{0, 2, 5}));
        assert(reconstruct_path(0, 4, res.parent) == (std::vector<int>{0, 2, 3, 4}));
    }

    std::cout << "All Dijkstra Private Tests Passed!\n";
    return 0;
}
