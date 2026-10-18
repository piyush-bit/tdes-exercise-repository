#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* create_graph(int num_vertices, int is_directed) {
    (void)num_vertices;
    (void)is_directed;
    // TODO: Allocate memory for Graph and initialize adj_lists array
    return NULL;
}

int add_edge(Graph* graph, int src, int dest) {
    (void)graph;
    (void)src;
    (void)dest;
    // TODO: Create adjacency list nodes and append to adj_lists[src] (and adj_lists[dest] if undirected)
    return -1;
}

int bfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity) {
    (void)graph;
    (void)start_vertex;
    (void)result;
    (void)capacity;
    // TODO: Perform BFS traversal using a queue and visited array, returning number of visited vertices
    return -1;
}

int dfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity) {
    (void)graph;
    (void)start_vertex;
    (void)result;
    (void)capacity;
    // TODO: Perform DFS traversal using recursion or stack and visited array, returning number of visited vertices
    return -1;
}

void free_graph(Graph* graph) {
    (void)graph;
    // TODO: Free all nodes, adj_lists array, and graph structure
}
