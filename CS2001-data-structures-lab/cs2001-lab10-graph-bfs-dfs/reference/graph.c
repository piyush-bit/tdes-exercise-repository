#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* create_graph(int num_vertices, int is_directed) {
    if (num_vertices <= 0) {
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;
    }

    graph->num_vertices = num_vertices;
    graph->is_directed = (is_directed != 0) ? 1 : 0;
    graph->adj_lists = (Node**)calloc(num_vertices, sizeof(Node*));
    if (graph->adj_lists == NULL) {
        free(graph);
        return NULL;
    }

    return graph;
}

static int append_neighbor(Node** head_ptr, int dest) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->vertex = dest;
    new_node->next = NULL;

    if (*head_ptr == NULL) {
        *head_ptr = new_node;
    } else {
        Node* curr = *head_ptr;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    return 0;
}

int add_edge(Graph* graph, int src, int dest) {
    if (graph == NULL || graph->adj_lists == NULL) {
        return -1;
    }
    if (src < 0 || src >= graph->num_vertices || dest < 0 || dest >= graph->num_vertices) {
        return -1;
    }

    if (append_neighbor(&(graph->adj_lists[src]), dest) != 0) {
        return -1;
    }

    if (graph->is_directed == 0 && src != dest) {
        if (append_neighbor(&(graph->adj_lists[dest]), src) != 0) {
            return -1;
        }
    }

    return 0;
}

int bfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity) {
    if (graph == NULL || graph->adj_lists == NULL || result == NULL || capacity <= 0) {
        return -1;
    }
    if (start_vertex < 0 || start_vertex >= graph->num_vertices) {
        return -1;
    }

    int* visited = (int*)calloc(graph->num_vertices, sizeof(int));
    int* queue = (int*)malloc(sizeof(int) * graph->num_vertices);
    if (visited == NULL || queue == NULL) {
        free(visited);
        free(queue);
        return -1;
    }

    int front = 0, rear = 0;
    int count = 0;

    visited[start_vertex] = 1;
    queue[rear++] = start_vertex;

    while (front < rear) {
        int u = queue[front++];
        if (count >= capacity) {
            free(visited);
            free(queue);
            return -1;
        }
        result[count++] = u;

        Node* curr = graph->adj_lists[u];
        while (curr != NULL) {
            int v = curr->vertex;
            if (v >= 0 && v < graph->num_vertices && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
            curr = curr->next;
        }
    }

    free(visited);
    free(queue);
    return count;
}

static int dfs_helper(const Graph* graph, int curr, int* visited, int* result, int* count, int capacity) {
    if (*count >= capacity) {
        return -1;
    }

    visited[curr] = 1;
    result[*count] = curr;
    (*count)++;

    Node* node = graph->adj_lists[curr];
    while (node != NULL) {
        int v = node->vertex;
        if (v >= 0 && v < graph->num_vertices && !visited[v]) {
            if (dfs_helper(graph, v, visited, result, count, capacity) == -1) {
                return -1;
            }
        }
        node = node->next;
    }

    return 0;
}

int dfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity) {
    if (graph == NULL || graph->adj_lists == NULL || result == NULL || capacity <= 0) {
        return -1;
    }
    if (start_vertex < 0 || start_vertex >= graph->num_vertices) {
        return -1;
    }

    int* visited = (int*)calloc(graph->num_vertices, sizeof(int));
    if (visited == NULL) {
        return -1;
    }

    int count = 0;
    int res = dfs_helper(graph, start_vertex, visited, result, &count, capacity);
    free(visited);

    if (res == -1) {
        return -1;
    }

    return count;
}

void free_graph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    if (graph->adj_lists != NULL) {
        for (int i = 0; i < graph->num_vertices; i++) {
            Node* curr = graph->adj_lists[i];
            while (curr != NULL) {
                Node* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(graph->adj_lists);
    }

    free(graph);
}
