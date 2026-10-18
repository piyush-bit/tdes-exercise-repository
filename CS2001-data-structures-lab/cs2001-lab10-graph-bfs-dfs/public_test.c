#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static int failed = 0;

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "[FAIL] %s: Expected %d, got %d\n", msg, (expected), (actual)); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", msg); \
        } \
    } while (0)

#define ASSERT_PTR_NOT_NULL(ptr, msg) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "[FAIL] %s: Expected non-NULL pointer\n", msg); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", msg); \
        } \
    } while (0)

#define ASSERT_PTR_NULL(ptr, msg) \
    do { \
        if ((ptr) != NULL) { \
            fprintf(stderr, "[FAIL] %s: Expected NULL pointer\n", msg); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", msg); \
        } \
    } while (0)

void test_public_creation(void) {
    printf("--- Running Public Graph Creation & Edge Addition Test ---\n");
    Graph* g = create_graph(4, 0);
    ASSERT_PTR_NOT_NULL(g, "create_graph returns valid pointer");
    if (g != NULL) {
        ASSERT_EQ(g->num_vertices, 4, "Graph num_vertices is 4");
        ASSERT_EQ(g->is_directed, 0, "Graph is_directed is 0");

        ASSERT_EQ(add_edge(g, 0, 1), 0, "add_edge (0, 1) returns 0");
        ASSERT_EQ(add_edge(g, 1, 2), 0, "add_edge (1, 2) returns 0");
        ASSERT_EQ(add_edge(g, 2, 3), 0, "add_edge (2, 3) returns 0");
        ASSERT_EQ(add_edge(g, 0, 10), -1, "add_edge out-of-bounds dest returns -1");
        free_graph(g);
    }

    Graph* g_invalid = create_graph(0, 1);
    ASSERT_PTR_NULL(g_invalid, "create_graph with 0 vertices returns NULL");
}

void test_public_bfs(void) {
    printf("--- Running Public BFS Traversal Test ---\n");
    Graph* g = create_graph(5, 0);
    ASSERT_PTR_NOT_NULL(g, "create_graph(5, 0) valid");
    if (g == NULL) return;

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 3);
    add_edge(g, 1, 4);
    add_edge(g, 2, 4);

    int result[10];
    int count = bfs_traversal(g, 0, result, 10);
    ASSERT_EQ(count, 5, "bfs_traversal visited count is 5");

    int expected[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "BFS visited vertex[%d] == %d", i, expected[i]);
        ASSERT_EQ(result[i], expected[i], msg);
    }

    free_graph(g);
}

void test_public_dfs(void) {
    printf("--- Running Public DFS Traversal Test ---\n");
    Graph* g = create_graph(4, 1); // Directed graph
    ASSERT_PTR_NOT_NULL(g, "create_graph(4, 1) valid");
    if (g == NULL) return;

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0);
    add_edge(g, 2, 3);
    add_edge(g, 3, 3);

    int result[10];
    int count = dfs_traversal(g, 2, result, 10);
    ASSERT_EQ(count, 4, "dfs_traversal visited count is 4");

    int expected[4] = {2, 0, 1, 3};
    for (int i = 0; i < 4; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "DFS visited vertex[%d] == %d", i, expected[i]);
        ASSERT_EQ(result[i], expected[i], msg);
    }

    free_graph(g);
}

int main(void) {
    test_public_creation();
    test_public_bfs();
    test_public_dfs();

    if (failed) {
        fprintf(stderr, "\nPublic tests failed!\n");
        return 1;
    }

    printf("\nAll Public Tests Passed Successfully!\n");
    return 0;
}
