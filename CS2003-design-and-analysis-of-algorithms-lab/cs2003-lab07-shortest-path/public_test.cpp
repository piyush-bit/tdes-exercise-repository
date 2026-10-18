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
    std::cout << "Running Public Tests for Shortest Path Engine...\n";

    // Test 1: Dijkstra algorithm on a 5-node weighted directed graph
    {
        int num_nodes = 5;
        std::vector<Edge> edges = {
            {0, 1, 4.0},
            {0, 2, 2.0},
            {1, 2, 1.0},
            {1, 3, 5.0},
            {2, 3, 8.0},
            {2, 4, 10.0},
            {3, 4, 2.0}
        };

        ShortestPathResult res = dijkstra_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(!res.has_negative_cycle);

        assert(double_equals(res.distances[0], 0.0));
        assert(double_equals(res.distances[1], 4.0));
        assert(double_equals(res.distances[2], 2.0));
        assert(double_equals(res.distances[3], 9.0));  // 0 -> 1 -> 3 (4 + 5 = 9)
        assert(double_equals(res.distances[4], 11.0)); // 0 -> 1 -> 3 -> 4 (4 + 5 + 2 = 11)

        std::vector<int> path = reconstruct_path(0, 4, res.parent);
        std::vector<int> expected_path = {0, 1, 3, 4};
        assert(path == expected_path);

        std::cout << "  [PASS] Dijkstra basic shortest path & path reconstruction\n";
    }

    // Test 2: Bellman-Ford algorithm with negative edge weights (no negative cycle)
    {
        int num_nodes = 4;
        std::vector<Edge> edges = {
            {0, 1, 4.0},
            {0, 2, 5.0},
            {1, 2, -2.0},
            {2, 3, 3.0}
        };

        ShortestPathResult res = bellman_ford_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(!res.has_negative_cycle);

        assert(double_equals(res.distances[0], 0.0));
        assert(double_equals(res.distances[1], 4.0));
        assert(double_equals(res.distances[2], 2.0)); // 0 -> 1 -> 2 (4 - 2 = 2)
        assert(double_equals(res.distances[3], 5.0)); // 2 + 3 = 5

        std::vector<int> path = reconstruct_path(0, 3, res.parent);
        std::vector<int> expected_path = {0, 1, 2, 3};
        assert(path == expected_path);

        std::cout << "  [PASS] Bellman-Ford shortest path with negative edge weights\n";
    }

    // Test 3: Bellman-Ford negative weight cycle detection
    {
        int num_nodes = 3;
        std::vector<Edge> edges = {
            {0, 1, 1.0},
            {1, 2, -3.0},
            {2, 1, 1.0} // Cycle 1 -> 2 -> 1 has net weight -2
        };

        ShortestPathResult res = bellman_ford_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(res.has_negative_cycle);

        std::cout << "  [PASS] Bellman-Ford negative weight cycle detection\n";
    }

    std::cout << "All Public Tests Passed Successfully!\n";
    return 0;
}
