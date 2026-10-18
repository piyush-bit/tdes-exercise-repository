#include "approx_tsp.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <numeric>
#include <algorithm>

static bool is_close(double a, double b, double tol = 1e-5) {
    return std::abs(a - b) <= tol;
}

void test_tour_cost_calculation() {
    std::cout << "[PUBLIC TEST] Running tour cost calculation test..." << std::endl;
    // Unit square: (0,0), (1,0), (1,1), (0,1)
    std::vector<Point> points = {
        {0, 0.0, 0.0},
        {1, 1.0, 0.0},
        {2, 1.0, 1.0},
        {3, 0.0, 1.0}
    };

    std::vector<int> tour = {0, 1, 2, 3};
    double cost = calculate_tour_cost(points, tour);
    assert(is_close(cost, 4.0));

    // Diagonal crossing tour: (0,0) -> (1,1) -> (1,0) -> (0,1)
    // d(0,2) = sqrt(2), d(2,1) = 1, d(1,3) = sqrt(2), d(3,0) = 1
    // Total = 2 + 2*sqrt(2) approx 4.828427
    std::vector<int> tour_diag = {0, 2, 1, 3};
    double cost_diag = calculate_tour_cost(points, tour_diag);
    assert(is_close(cost_diag, 2.0 + 2.0 * std::sqrt(2.0)));

    std::cout << "  -> PASS: Tour cost calculation validated." << std::endl;
}

void test_2approx_tsp_tour_and_bound() {
    std::cout << "[PUBLIC TEST] Running 2-Approximation TSP tour generation & bound test..." << std::endl;
    // 5 logistics delivery waypoints
    std::vector<Point> points = {
        {0, 0.0, 0.0},
        {1, 3.0, 0.0},
        {2, 3.0, 4.0},
        {3, 0.0, 4.0},
        {4, 1.5, 2.0}
    };

    std::vector<Edge> mst_edges;
    std::vector<int> tour = approx_tsp_2approx(points, mst_edges, 0);

    // 1. Verify MST edge count
    assert(mst_edges.size() == points.size() - 1);

    // 2. Compute total MST weight
    double total_mst_weight = 0.0;
    for (const auto& edge : mst_edges) {
        total_mst_weight += edge.weight;
    }
    assert(total_mst_weight > 0.0);

    // 3. Verify tour validity (permutation of all point indices)
    assert(tour.size() == points.size());
    std::vector<int> sorted_tour = tour;
    std::sort(sorted_tour.begin(), sorted_tour.end());
    for (size_t i = 0; i < points.size(); ++i) {
        assert(sorted_tour[i] == static_cast<int>(i));
    }

    // 4. Verify tour starts at specified root
    assert(tour[0] == 0);

    // 5. Verify 2-approximation cost bound: Tour Cost <= 2.0 * MST Weight
    double tour_cost = calculate_tour_cost(points, tour);
    std::cout << "  -> MST Total Weight: " << total_mst_weight << std::endl;
    std::cout << "  -> Approx Tour Cost: " << tour_cost << std::endl;

    assert(tour_cost <= 2.0 * total_mst_weight + 1e-6);
    assert(tour_cost >= total_mst_weight - 1e-6);

    std::cout << "  -> PASS: 2-Approximation TSP tour and bound validated." << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "CS2003 Lab 10: Public Test Suite" << std::endl;
    std::cout << "========================================" << std::endl;

    test_tour_cost_calculation();
    test_2approx_tsp_tour_and_bound();

    std::cout << "ALL PUBLIC TESTS PASSED SUCCESSFULLY!" << std::endl;
    return 0;
}
