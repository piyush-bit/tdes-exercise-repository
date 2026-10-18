#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

/**
 * Node structure representing an element in an adjacency list.
 */
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

/**
 * Graph structure representing an adjacency list graph.
 * num_vertices: total number of vertices (indexed from 0 to num_vertices - 1).
 * adj_lists: array of pointers to head nodes of adjacency lists.
 * is_directed: 0 for undirected graph, 1 for directed graph.
 */
typedef struct Graph {
    int num_vertices;
    Node** adj_lists;
    int is_directed;
} Graph;

/**
 * Creates and initializes a new Graph.
 *
 * @param num_vertices Number of vertices in the graph (must be > 0)
 * @param is_directed  0 for undirected graph, 1 for directed graph
 * @return             Pointer to newly created Graph, or NULL on error (num_vertices <= 0 or allocation failure).
 */
Graph* create_graph(int num_vertices, int is_directed);

/**
 * Adds an edge between src and dest vertices.
 * For directed graphs, adds edge src -> dest.
 * For undirected graphs, adds edge src -> dest and dest -> src (unless src == dest).
 * New adjacent nodes are appended to the end of the corresponding adjacency list.
 *
 * @param graph Pointer to Graph
 * @param src   Source vertex index (0 <= src < num_vertices)
 * @param dest  Destination vertex index (0 <= dest < num_vertices)
 * @return      0 on success, -1 on error (NULL graph, out-of-bounds indices, or allocation failure).
 */
int add_edge(Graph* graph, int src, int dest);

/**
 * Performs Breadth-First Search (BFS) traversal starting from start_vertex.
 *
 * @param graph        Pointer to Graph
 * @param start_vertex Vertex index to start traversal from (0 <= start_vertex < num_vertices)
 * @param result       Array to store the sequence of visited vertices
 * @param capacity     Maximum capacity of the result array
 * @return             Number of vertices visited on success, or -1 on error
 *                     (NULL parameters, invalid start_vertex, or insufficient capacity).
 */
int bfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity);

/**
 * Performs Depth-First Search (DFS) traversal starting from start_vertex.
 * Traverses adjacent vertices in the order they appear in the adjacency list.
 *
 * @param graph        Pointer to Graph
 * @param start_vertex Vertex index to start traversal from (0 <= start_vertex < num_vertices)
 * @param result       Array to store the sequence of visited vertices
 * @param capacity     Maximum capacity of the result array
 * @return             Number of vertices visited on success, or -1 on error
 *                     (NULL parameters, invalid start_vertex, or insufficient capacity).
 */
int dfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity);

/**
 * Frees all memory associated with the graph, including adjacency lists and nodes.
 * Safe to call with NULL.
 *
 * @param graph Pointer to Graph to free
 */
void free_graph(Graph* graph);

#endif /* GRAPH_H */
