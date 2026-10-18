#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include <vector>
#include <limits>
#include <cstddef>

// Represents a directed weighted edge between src and dest nodes.
struct Edge {
    int src;
    int dest;
    double weight;

    Edge(int s = 0, int d = 0, double w = 0.0)
        : src(s), dest(d), weight(w) {}
};

// Represents the output result of single-source shortest path algorithms.
struct ShortestPathResult {
    bool success{false};
    bool has_negative_cycle{false};
    std::vector<double> distances;
    std::vector<int> parent;
};

/**
 * Computes single-source shortest paths using Dijkstra's algorithm.
 * Assumes non-negative edge weights.
 * 
 * @param num_nodes Total number of nodes in the graph (0 to num_nodes - 1).
 * @param edges Vector of directed weighted edges.
 * @param start_node Source node ID.
 * @return ShortestPathResult structure containing distances, parents, and status flags.
 */
ShortestPathResult dijkstra_shortest_path(int num_nodes, const std::vector<Edge>& edges, int start_node);

/**
 * Computes single-source shortest paths using Bellman-Ford algorithm with negative cycle detection.
 * Supports negative edge weights.
 * 
 * @param num_nodes Total number of nodes in the graph (0 to num_nodes - 1).
 * @param edges Vector of directed weighted edges.
 * @param start_node Source node ID.
 * @return ShortestPathResult structure containing distances, parents, and status flags.
 */
ShortestPathResult bellman_ford_shortest_path(int num_nodes, const std::vector<Edge>& edges, int start_node);

/**
 * Reconstructs the node sequence along the shortest path from start_node to target_node.
 * 
 * @param start_node Source node ID.
 * @param target_node Destination node ID.
 * @param parent Vector of parent node indices produced by Dijkstra or Bellman-Ford.
 * @return Vector of node IDs in order [start_node, ..., target_node], or empty vector if unreachable.
 */
std::vector<int> reconstruct_path(int start_node, int target_node, const std::vector<int>& parent);

#endif // SHORTEST_PATH_HPP
