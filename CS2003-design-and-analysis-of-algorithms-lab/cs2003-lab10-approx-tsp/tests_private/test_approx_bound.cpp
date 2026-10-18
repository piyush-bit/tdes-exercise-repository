#include "approx_tsp.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>

static double brute_force_optimal_tsp(const std::vector<Point>& points) {
    int n = static_cast<int>(points.size());
    if (n <= 1) return 0.0;

    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);

    double min_cost = std::numeric_limits<double>::infinity();
    do {
        double cost = calculate_tour_cost(points, perm);
        if (cost < min_cost) {
            min_cost = cost;
        }
    } while (std::next_permutation(perm.begin() + 1, perm.end()));

    return min_cost;
}

void test_brute_force_optimal_bound() {
    std::cout << "[PRIVATE TEST: APPROX BOUND] Testing against exact Brute-Force Optimal TSP..." << std::endl;

    // Test across several small point configurations (N=6 to N=8)
    std::vector<std::vector<Point>> test_cases = {
        // Case 1: Hexagon + center
        {
            {0, 0.0, 0.0},
            {1, 2.0, 0.0},
            {2, 3.0, 1.732},
            {3, 2.0, 3.464},
            {4, 0.0, 3.464},
            {5, -1.0, 1.732},
            {6, 1.0, 1.732}
        },
        // Case 2: Asymmetric 6 logistics points
        {
            {0, 10.0, 20.0},
            {1, 45.0, 60.0},
            {2, 80.0, 15.0},
            {3, 30.0, 90.0},
            {4, 90.0, 85.0},
            {5, 5.0, 50.0}
        }
    };

    for (size_t tc = 0; tc < test_cases.size(); ++tc) {
        const auto& points = test_cases[tc];
        std::vector<Edge> mst;
        std::vector<int> tour = approx_tsp_2approx(points, mst, 0);

        double tour_cost = calculate_tour_cost(points, tour);
        double opt_cost = brute_force_optimal_tsp(points);

        double mst_w = 0.0;
        for (const auto& e : mst) mst_w += e.weight;

        std::cout << "  [Case " << tc + 1 << "] Approx Cost: " << tour_cost
                  << " | MST Weight: " << mst_w
                  << " | OPT Cost: " << opt_cost << std::endl;

        // 1. Lower bound check: OPT >= MST Weight
        assert(opt_cost >= mst_w - 1e-6);

        // 2. 2-Approx bound relative to MST: Tour Cost <= 2.0 * MST Weight
        assert(tour_cost <= 2.0 * mst_w + 1e-6);

        // 3. 2-Approx bound relative to OPT: Tour Cost <= 2.0 * OPT
        assert(tour_cost <= 2.0 * opt_cost + 1e-6);

        // 4. Tour Cost >= OPT
        assert(tour_cost >= opt_cost - 1e-6);
    }

    std::cout << "  -> PASS: Brute-Force optimal bound comparisons validated." << std::endl;
}

void test_synthetic_grid_and_circle() {
    std::cout << "[PRIVATE TEST: APPROX BOUND] Testing 4x4 Grid & Circle configurations..." << std::endl;

    // 4x4 Grid of Points (N=16)
    std::vector<Point> grid_pts;
    int id = 0;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            grid_pts.push_back({id++, c * 10.0, r * 10.0});
        }
    }

    std::vector<Edge> grid_mst;
    std::vector<int> grid_tour = approx_tsp_2approx(grid_pts, grid_mst, 0);
    double grid_tour_cost = calculate_tour_cost(grid_pts, grid_tour);
    double grid_mst_w = 0.0;
    for (const auto& e : grid_mst) grid_mst_w += e.weight;

    assert(grid_tour_cost <= 2.0 * grid_mst_w + 1e-6);
    assert(grid_tour_cost >= grid_mst_w - 1e-6);

    // Circle of 20 points
    std::vector<Point> circle_pts;
    double radius = 100.0;
    for (int i = 0; i < 20; ++i) {
        double angle = 2.0 * M_PI * i / 20.0;
        circle_pts.push_back({i, radius * std::cos(angle), radius * std::sin(angle)});
    }

    std::vector<Edge> circle_mst;
    std::vector<int> circle_tour = approx_tsp_2approx(circle_pts, circle_mst, 0);
    double circle_tour_cost = calculate_tour_cost(circle_pts, circle_tour);
    double circle_mst_w = 0.0;
    for (const auto& e : circle_mst) circle_mst_w += e.weight;

    assert(circle_tour_cost <= 2.0 * circle_mst_w + 1e-6);
    assert(circle_tour_cost >= circle_mst_w - 1e-6);

    std::cout << "  -> PASS: Grid and Circle 2-approx bounds validated." << std::endl;
}

void test_large_scale_logistic_dataset() {
    std::cout << "[PRIVATE TEST: APPROX BOUND] Testing Large N=100 random warehouse dataset..." << std::endl;

    std::mt19937 rng(42); // deterministic seed
    std::uniform_real_distribution<double> dist(0.0, 1000.0);

    std::vector<Point> large_pts;
    for (int i = 0; i < 100; ++i) {
        large_pts.push_back({i, dist(rng), dist(rng)});
    }

    std::vector<Edge> large_mst;
    std::vector<int> large_tour = approx_tsp_2approx(large_pts, large_mst, 0);

    assert(large_tour.size() == 100);
    assert(large_mst.size() == 99);

    double tour_cost = calculate_tour_cost(large_pts, large_tour);
    double mst_w = 0.0;
    for (const auto& e : large_mst) mst_w += e.weight;

    std::cout << "  -> N=100 MST Weight: " << mst_w << " | Approx Tour Cost: " << tour_cost << std::endl;
    assert(tour_cost <= 2.0 * mst_w + 1e-6);
    assert(tour_cost >= mst_w - 1e-6);

    std::cout << "  -> PASS: Large N=100 scale test validated." << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "CS2003 Lab 10: Private Test (2-Approx Bound)" << std::endl;
    std::cout << "========================================" << std::endl;

    test_brute_force_optimal_bound();
    test_synthetic_grid_and_circle();
    test_large_scale_logistic_dataset();

    std::cout << "TSP 2-APPROXIMATION BOUND TESTS PASSED!" << std::endl;
    return 0;
}
