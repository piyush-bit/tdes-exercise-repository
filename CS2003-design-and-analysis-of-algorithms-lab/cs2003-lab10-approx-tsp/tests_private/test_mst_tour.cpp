#include "approx_tsp.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <set>

static bool is_close(double a, double b, double tol = 1e-5) {
    return std::abs(a - b) <= tol;
}

void test_edge_cases() {
    std::cout << "[PRIVATE TEST: MST & TOUR] Testing edge cases (N=0, N=1, N=2)..." << std::endl;

    // N = 0
    std::vector<Point> empty_pts;
    std::vector<Edge> empty_mst;
    std::vector<int> empty_tour = approx_tsp_2approx(empty_pts, empty_mst, 0);
    assert(empty_tour.empty());
    assert(empty_mst.empty());
    assert(is_close(calculate_tour_cost(empty_pts, empty_tour), 0.0));

    // N = 1
    std::vector<Point> one_pt = {{0, 5.0, 5.0}};
    std::vector<Edge> one_mst;
    std::vector<int> one_tour = approx_tsp_2approx(one_pt, one_mst, 0);
    assert(one_tour.size() == 1 && one_tour[0] == 0);
    assert(one_mst.empty());
    assert(is_close(calculate_tour_cost(one_pt, one_tour), 0.0));

    // N = 2
    std::vector<Point> two_pts = {{0, 0.0, 0.0}, {1, 3.0, 4.0}};
    std::vector<Edge> two_mst;
    std::vector<int> two_tour = approx_tsp_2approx(two_pts, two_mst, 0);
    assert(two_tour.size() == 2);
    assert(two_mst.size() == 1);
    assert(is_close(two_mst[0].weight, 5.0));
    assert(is_close(calculate_tour_cost(two_pts, two_tour), 10.0));

    std::cout << "  -> PASS: Edge cases validated." << std::endl;
}

void test_mst_properties_and_traversal() {
    std::cout << "[PRIVATE TEST: MST & TOUR] Testing MST tree properties & DFS traversal..." << std::endl;

    // Collinear points along X-axis: x = 0, 1, 3, 6
    // Known MST edges: (0,1) len=1, (1,2) len=2, (2,3) len=3. Total MST weight = 6.0
    std::vector<Point> line_pts = {
        {0, 0.0, 0.0},
        {1, 1.0, 0.0},
        {2, 3.0, 0.0},
        {3, 6.0, 0.0}
    };

    std::vector<Edge> mst;
    std::vector<int> tour = approx_tsp_2approx(line_pts, mst, 0);

    assert(mst.size() == 3);
    double mst_w = 0.0;
    for (const auto& e : mst) {
        mst_w += e.weight;
    }
    assert(is_close(mst_w, 6.0));

    // Verify tree connectivity using Disjoint Set / Union-Find or BFS
    std::vector<int> parent_ds(4);
    for (int i = 0; i < 4; ++i) parent_ds[i] = i;
    auto find_ds = [&](auto self, int i) -> int {
        return parent_ds[i] == i ? i : parent_ds[i] = self(self, parent_ds[i]);
    };
    int components = 4;
    for (const auto& e : mst) {
        int r1 = find_ds(find_ds, e.u);
        int r2 = find_ds(find_ds, e.v);
        if (r1 != r2) {
            parent_ds[r1] = r2;
            components--;
        }
    }
    assert(components == 1); // MST must fully connect all vertices

    // Tour starting from node 0
    assert(tour.size() == 4);
    assert(tour[0] == 0);

    // Tour starting from custom root node 2
    std::vector<Edge> mst2;
    std::vector<int> tour2 = approx_tsp_2approx(line_pts, mst2, 2);
    assert(tour2.size() == 4);
    assert(tour2[0] == 2);

    std::cout << "  -> PASS: MST properties and DFS pre-order traversal validated." << std::endl;
}

void test_complex_star_layout() {
    std::cout << "[PRIVATE TEST: MST & TOUR] Testing star configuration..." << std::endl;
    // Central hub at (0,0) and 4 spokes at (1,0), (0,1), (-1,0), (0,-1)
    std::vector<Point> star = {
        {0, 0.0, 0.0},   // center
        {1, 1.0, 0.0},   // right
        {2, 0.0, 1.0},   // top
        {3, -1.0, 0.0},  // left
        {4, 0.0, -1.0}   // bottom
    };

    std::vector<Edge> mst;
    std::vector<int> tour = approx_tsp_2approx(star, mst, 0);

    assert(mst.size() == 4);
    double mst_w = 0.0;
    for (const auto& e : mst) {
        mst_w += e.weight;
    }
    // Each spoke connects directly to central hub with distance 1.0
    assert(is_close(mst_w, 4.0));

    // Verify tour contains all 5 vertices
    std::set<int> visited_set(tour.begin(), tour.end());
    assert(visited_set.size() == 5);

    std::cout << "  -> PASS: Complex star layout validated." << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "CS2003 Lab 10: Private Test (MST & Pre-order Tour)" << std::endl;
    std::cout << "========================================" << std::endl;

    test_edge_cases();
    test_mst_properties_and_traversal();
    test_complex_star_layout();

    std::cout << "MST PRE-ORDER TOUR TESTS PASSED!" << std::endl;
    return 0;
}
