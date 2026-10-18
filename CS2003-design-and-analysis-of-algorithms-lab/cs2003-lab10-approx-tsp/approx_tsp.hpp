#ifndef APPROX_TSP_HPP
#define APPROX_TSP_HPP

#include <vector>
#include <cmath>

struct Point {
    int id;
    double x;
    double y;

    double distance_to(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

struct Edge {
    int u;
    int v;
    double weight;
};

// Calculates total Euclidean tour distance for a list of point indices representing a TSP cycle.
// Returns dist(p[tour[0]], p[tour[1]]) + ... + dist(p[tour[n-1]], p[tour[0]]).
// Returns 0.0 for empty or single-point tours.
double calculate_tour_cost(const std::vector<Point>& points, const std::vector<int>& tour);

// Computes 2-Approximation TSP tour using Prim's MST and Pre-order DFS traversal.
// Returns a vector of point indices representing the ordered visited vertices (Hamiltonian cycle).
// Also populates mst_edges with the N-1 edges of the Minimum Spanning Tree.
std::vector<int> approx_tsp_2approx(const std::vector<Point>& points, std::vector<Edge>& mst_edges, int start_node = 0);

#endif // APPROX_TSP_HPP
