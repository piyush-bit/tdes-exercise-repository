#include "approx_tsp.hpp"
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

double calculate_tour_cost(const std::vector<Point>& points, const std::vector<int>& tour) {
    if (tour.empty() || tour.size() == 1) {
        return 0.0;
    }
    double total = 0.0;
    size_t n = tour.size();
    for (size_t i = 0; i < n; ++i) {
        int u = tour[i];
        int v = tour[(i + 1) % n];
        total += points[u].distance_to(points[v]);
    }
    return total;
}

static void dfs_preorder(int curr, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<int>& tour) {
    visited[curr] = true;
    tour.push_back(curr);
    for (int nbr : adj[curr]) {
        if (!visited[nbr]) {
            dfs_preorder(nbr, adj, visited, tour);
        }
    }
}

std::vector<int> approx_tsp_2approx(const std::vector<Point>& points, std::vector<Edge>& mst_edges, int start_node) {
    mst_edges.clear();
    int n = static_cast<int>(points.size());
    if (n == 0) {
        return {};
    }
    if (n == 1) {
        return {0};
    }
    if (start_node < 0 || start_node >= n) {
        start_node = 0;
    }

    std::vector<double> min_weight(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::vector<bool> in_mst(n, false);

    min_weight[start_node] = 0.0;

    for (int step = 0; step < n; ++step) {
        int u = -1;
        double min_val = std::numeric_limits<double>::infinity();

        for (int v = 0; v < n; ++v) {
            if (!in_mst[v] && min_weight[v] < min_val) {
                min_val = min_weight[v];
                u = v;
            }
        }

        if (u == -1) break;

        in_mst[u] = true;

        if (parent[u] != -1) {
            Edge e{parent[u], u, min_val};
            mst_edges.push_back(e);
        }

        for (int v = 0; v < n; ++v) {
            if (!in_mst[v]) {
                double dist = points[u].distance_to(points[v]);
                if (dist < min_weight[v]) {
                    min_weight[v] = dist;
                    parent[v] = u;
                }
            }
        }
    }

    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : mst_edges) {
        adj[edge.u].push_back(edge.v);
        adj[edge.v].push_back(edge.u);
    }

    for (int i = 0; i < n; ++i) {
        std::sort(adj[i].begin(), adj[i].end());
    }

    std::vector<int> tour;
    tour.reserve(n);
    std::vector<bool> visited(n, false);

    dfs_preorder(start_node, adj, visited, tour);

    return tour;
}
