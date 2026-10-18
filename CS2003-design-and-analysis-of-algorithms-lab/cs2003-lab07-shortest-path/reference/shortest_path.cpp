#include "shortest_path.hpp"
#include <queue>
#include <limits>
#include <algorithm>

ShortestPathResult dijkstra_shortest_path(int num_nodes, const std::vector<Edge>& edges, int start_node) {
    ShortestPathResult result;
    if (num_nodes <= 0 || start_node < 0 || start_node >= num_nodes) {
        result.success = false;
        return result;
    }

    for (const auto& edge : edges) {
        if (edge.src < 0 || edge.src >= num_nodes ||
            edge.dest < 0 || edge.dest >= num_nodes ||
            edge.weight < 0.0) {
            result.success = false;
            return result;
        }
    }

    const double INF = std::numeric_limits<double>::infinity();
    result.distances.assign(num_nodes, INF);
    result.parent.assign(num_nodes, -1);
    result.has_negative_cycle = false;
    result.success = true;

    std::vector<std::vector<std::pair<int, double>>> adj(num_nodes);
    for (const auto& edge : edges) {
        adj[edge.src].push_back({edge.dest, edge.weight});
    }

    result.distances[start_node] = 0.0;

    using Element = std::pair<double, int>;
    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> pq;
    pq.push({0.0, start_node});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > result.distances[u]) {
            continue;
        }

        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            double w = neighbor.second;

            if (result.distances[u] + w < result.distances[v]) {
                result.distances[v] = result.distances[u] + w;
                result.parent[v] = u;
                pq.push({result.distances[v], v});
            }
        }
    }

    return result;
}

ShortestPathResult bellman_ford_shortest_path(int num_nodes, const std::vector<Edge>& edges, int start_node) {
    ShortestPathResult result;
    if (num_nodes <= 0 || start_node < 0 || start_node >= num_nodes) {
        result.success = false;
        return result;
    }

    for (const auto& edge : edges) {
        if (edge.src < 0 || edge.src >= num_nodes ||
            edge.dest < 0 || edge.dest >= num_nodes) {
            result.success = false;
            return result;
        }
    }

    const double INF = std::numeric_limits<double>::infinity();
    result.distances.assign(num_nodes, INF);
    result.parent.assign(num_nodes, -1);
    result.has_negative_cycle = false;
    result.success = true;

    result.distances[start_node] = 0.0;

    for (int i = 0; i < num_nodes - 1; ++i) {
        bool updated = false;
        for (const auto& edge : edges) {
            if (result.distances[edge.src] != INF &&
                result.distances[edge.src] + edge.weight < result.distances[edge.dest]) {
                result.distances[edge.dest] = result.distances[edge.src] + edge.weight;
                result.parent[edge.dest] = edge.src;
                updated = true;
            }
        }
        if (!updated) break;
    }

    for (const auto& edge : edges) {
        if (result.distances[edge.src] != INF &&
            result.distances[edge.src] + edge.weight < result.distances[edge.dest]) {
            result.has_negative_cycle = true;
            break;
        }
    }

    return result;
}

std::vector<int> reconstruct_path(int start_node, int target_node, const std::vector<int>& parent) {
    if (parent.empty() || start_node < 0 || target_node < 0 ||
        start_node >= static_cast<int>(parent.size()) ||
        target_node >= static_cast<int>(parent.size())) {
        return {};
    }

    if (start_node == target_node) {
        return {start_node};
    }

    std::vector<int> path;
    int curr = target_node;
    std::vector<bool> visited(parent.size(), false);

    while (curr != -1) {
        if (visited[curr]) {
            return {};
        }
        visited[curr] = true;
        path.push_back(curr);
        if (curr == start_node) {
            break;
        }
        curr = parent[curr];
    }

    if (path.empty() || path.back() != start_node) {
        return {};
    }

    std::reverse(path.begin(), path.end());
    return path;
}
