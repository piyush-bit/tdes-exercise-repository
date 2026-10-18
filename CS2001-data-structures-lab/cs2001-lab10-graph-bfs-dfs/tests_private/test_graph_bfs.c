#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static int failed = 0;

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "[PRIVATE BFS FAIL] %s: Expected %d, got %d\n", msg, (expected), (actual)); \
            failed = 1; \
        } \
    } while (0)

#define ASSERT_PTR_NOT_NULL(ptr, msg) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "[PRIVATE BFS FAIL] %s: Expected non-NULL pointer\n", msg); \
            failed = 1; \
        } \
    } while (0)

static void test_bfs_undirected_cycle(void) {
    Graph* g = create_graph(6, 0);
    ASSERT_PTR_NOT_NULL(g, "create_graph(6, 0)");
    if (!g) return;

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 3);
    add_edge(g, 2, 4);
    add_edge(g, 3, 5);
    add_edge(g, 4, 5);

    int result[10];
    int count = bfs_traversal(g, 0, result, 10);
    ASSERT_EQ(count, 6, "BFS traversal count on undirected cycle graph is 6");

    int expected[6] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < 6; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "BFS element[%d] == %d", i, expected[i]);
        ASSERT_EQ(result[i], expected[i], msg);
    }

    free_graph(g);
}

static void test_bfs_directed_dag(void) {
    Graph* g = create_graph(6, 1);
    ASSERT_PTR_NOT_NULL(g, "create_graph(6, 1)");
    if (!g) return;

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 3);
    add_edge(g, 1, 4);
    add_edge(g, 2, 4);
    add_edge(g, 3, 5);
    add_edge(g, 4, 5);

    int result[10];
    int count = bfs_traversal(g, 0, result, 10);
    ASSERT_EQ(count, 6, "BFS traversal count on directed DAG is 6");

    int expected[6] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < 6; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "BFS DAG element[%d] == %d", i, expected[i]);
        ASSERT_EQ(result[i], expected[i], msg);
    }

    free_graph(g);
}

static void test_bfs_disconnected(void) {
    Graph* g = create_graph(6, 0);
    ASSERT_PTR_NOT_NULL(g, "create_graph(6, 0) disconnected");
    if (!g) return;

    // Component 1: 0-1-2
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);

    // Component 2: 3-4-5
    add_edge(g, 3, 4);
    add_edge(g, 4, 5);

    int result[10];
    int count1 = bfs_traversal(g, 0, result, 10);
    ASSERT_EQ(count1, 3, "BFS starting at 0 in disconnected graph visits 3 vertices");
    ASSERT_EQ(result[0], 0, "BFS Comp 1 res[0]");
    ASSERT_EQ(result[1], 1, "BFS Comp 1 res[1]");
    ASSERT_EQ(result[2], 2, "BFS Comp 1 res[2]");

    int count2 = bfs_traversal(g, 3, result, 10);
    ASSERT_EQ(count2, 3, "BFS starting at 3 in disconnected graph visits 3 vertices");
    ASSERT_EQ(result[0], 3, "BFS Comp 2 res[0]");
    ASSERT_EQ(result[1], 4, "BFS Comp 2 res[1]");
    ASSERT_EQ(result[2], 5, "BFS Comp 2 res[2]");

    free_graph(g);
}

static void test_bfs_single_vertex(void) {
    Graph* g = create_graph(1, 0);
    ASSERT_PTR_NOT_NULL(g, "create_graph(1, 0)");
    if (!g) return;

    int result[5];
    int count = bfs_traversal(g, 0, result, 5);
    ASSERT_EQ(count, 1, "BFS on single vertex graph returns 1");
    ASSERT_EQ(result[0], 0, "BFS single vertex is 0");

    free_graph(g);
}

static void test_bfs_error_cases(void) {
    Graph* g = create_graph(5, 0);
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);

    int result[10];

    ASSERT_EQ(bfs_traversal(NULL, 0, result, 10), -1, "BFS NULL graph returns -1");
    ASSERT_EQ(bfs_traversal(g, 0, NULL, 10), -1, "BFS NULL result array returns -1");
    ASSERT_EQ(bfs_traversal(g, -1, result, 10), -1, "BFS negative start_vertex returns -1");
    ASSERT_EQ(bfs_traversal(g, 5, result, 10), -1, "BFS start_vertex >= num_vertices returns -1");
    ASSERT_EQ(bfs_traversal(g, 0, result, 0), -1, "BFS 0 capacity returns -1");
    ASSERT_EQ(bfs_traversal(g, 0, result, 2), -1, "BFS insufficient capacity returns -1");

    free_graph(g);
}

int main(void) {
    printf("Running Private BFS Tests...\n");
    test_bfs_undirected_cycle();
    test_bfs_directed_dag();
    test_bfs_disconnected();
    test_bfs_single_vertex();
    test_bfs_error_cases();

    if (failed) {
        fprintf(stderr, "Private BFS Tests FAILED!\n");
        return 1;
    }

    printf("All Private BFS Tests PASSED!\n");
    return 0;
}
