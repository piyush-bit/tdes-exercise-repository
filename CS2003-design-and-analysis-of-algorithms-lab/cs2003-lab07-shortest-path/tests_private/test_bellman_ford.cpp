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
    std::cout << "Running Private Tests for Bellman-Ford Algorithm...\n";

    // 1. Invalid inputs validation
    {
        std::vector<Edge> edges = {{0, 1, -5.0}};
        assert(!bellman_ford_shortest_path(0, edges, 0).success);
        assert(!bellman_ford_shortest_path(2, edges, -1).success);
        assert(!bellman_ford_shortest_path(2, edges, 2).success);

        // Edge with out-of-bounds dest node
        std::vector<Edge> oob_edges = {{0, 10, -1.0}};
        assert(!bellman_ford_shortest_path(3, oob_edges, 0).success);
    }

    // 2. Bellman-Ford on DAG with negative edge weights
    {
        int num_nodes = 5;
        std::vector<Edge> edges = {
            {0, 1, 6.0},
            {0, 2, 7.0},
            {1, 2, 8.0},
            {1, 3, 5.0},
            {1, 4, -4.0},
            {2, 3, -3.0},
            {2, 4, 9.0},
            {3, 1, -2.0},
            {4, 0, 2.0},
            {4, 3, 7.0}
        };

        ShortestPathResult res = bellman_ford_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(!res.has_negative_cycle);

        assert(double_equals(res.distances[0], 0.0));
        assert(double_equals(res.distances[1], 2.0));  // 0->2->3->1 (7 - 3 - 2 = 2)
        assert(double_equals(res.distances[2], 7.0));
        assert(double_equals(res.distances[3], 4.0));  // 0->2->3 (7 - 3 = 4)
        assert(double_equals(res.distances[4], -2.0)); // 0->2->3->1->4 (7 - 3 - 2 - 4 = -2)

        assert(reconstruct_path(0, 4, res.parent) == (std::vector<int>{0, 2, 3, 1, 4}));
    }

    // 3. Positive and Zero weight cycles (should NOT report negative cycle)
    {
        int num_nodes = 3;
        std::vector<Edge> edges = {
            {0, 1, 3.0},
            {1, 2, 0.0},
            {2, 1, 0.0} // Zero-weight cycle
        };

        ShortestPathResult res = bellman_ford_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(!res.has_negative_cycle);
        assert(double_equals(res.distances[2], 3.0));
    }

    // 4. Reachable Negative Cycle Detection
    {
        int num_nodes = 4;
        std::vector<Edge> edges = {
            {0, 1, 1.0},
            {1, 2, 2.0},
            {2, 3, -4.0},
            {3, 1, 1.0} // Cycle 1 -> 2 -> 3 -> 1 has net weight 2 - 4 + 1 = -1
        };

        ShortestPathResult res = bellman_ford_shortest_path(num_nodes, edges, 0);
        assert(res.success);
        assert(res.has_negative_cycle);
    }

    std::cout << "All Bellman-Ford Private Tests Passed!\n";
    return 0;
}
