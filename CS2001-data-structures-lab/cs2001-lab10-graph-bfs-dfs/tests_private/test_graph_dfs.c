#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static int failed = 0;

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "[PRIVATE DFS FAIL] %s: Expected %d, got %d\n", msg, (expected), (actual)); \
            failed = 1; \
        } \
    } while (0)

#define ASSERT_PTR_NOT_NULL(ptr, msg) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "[PRIVATE DFS FAIL] %s: Expected non-NULL pointer\n", msg); \
            failed = 1; \
        } \
    } while (0)

static void test_dfs_undirected_tree(void) {
    Graph* g = create_graph(6, 0);
    ASSERT_PTR_NOT_NULL(g, "create_graph(6, 0)");
    if (!g) return;

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 3);
    add_edge(g, 1, 4);
    add_edge(g, 2, 5);

    int result[10];
    int count = dfs_traversal(g, 0, result, 10);
    ASSERT_EQ(count, 6, "DFS traversal count on tree graph is 6");

    int expected[6] = {0, 1, 3, 4, 2, 5};
    for (int i = 0; i < 6; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "DFS tree element[%d] == %d", i, expected[i]);
        ASSERT_EQ(result[i], expected[i], msg);
    }

    free_graph(g);
}

static void test_dfs_directed_cycles(void) {
    Graph* g = create_graph(4, 1);
    ASSERT_PTR_NOT_NULL(g, "create_graph(4, 1)");
    if (!g) return;

    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0);
    add_edge(g, 2, 3);
    add_edge(g, 3, 1);

    int result[10];
    int count = dfs_traversal(g, 0, result, 10);
    ASSERT_EQ(count, 4, "DFS traversal count on cyclic directed graph is 4");

    int expected[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "DFS cycle element[%d] == %d", i, expected[i]);
        ASSERT_EQ(result[i], expected[i], msg);
    }

    free_graph(g);
}

static void test_dfs_disconnected(void) {
    Graph* g = create_graph(5, 1);
    ASSERT_PTR_NOT_NULL(g, "create_graph(5, 1)");
    if (!g) return;

    // Component 1: 0->1->2
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);

    // Component 2: 3->4
    add_edge(g, 3, 4);

    int result[10];
    int count1 = dfs_traversal(g, 0, result, 10);
    ASSERT_EQ(count1, 3, "DFS from 0 in disconnected directed graph visits 3");
    ASSERT_EQ(result[0], 0, "DFS Comp 1 res[0]");
    ASSERT_EQ(result[1], 1, "DFS Comp 1 res[1]");
    ASSERT_EQ(result[2], 2, "DFS Comp 1 res[2]");

    int count2 = dfs_traversal(g, 3, result, 10);
    ASSERT_EQ(count2, 2, "DFS from 3 in disconnected directed graph visits 2");
    ASSERT_EQ(result[0], 3, "DFS Comp 2 res[0]");
    ASSERT_EQ(result[1], 4, "DFS Comp 2 res[1]");

    free_graph(g);
}

static void test_dfs_single_vertex(void) {
    Graph* g = create_graph(1, 1);
    ASSERT_PTR_NOT_NULL(g, "create_graph(1, 1)");
    if (!g) return;

    int result[5];
    int count = dfs_traversal(g, 0, result, 5);
    ASSERT_EQ(count, 1, "DFS on single vertex graph returns 1");
    ASSERT_EQ(result[0], 0, "DFS single vertex is 0");

    free_graph(g);
}

static void test_dfs_error_cases(void) {
    Graph* g = create_graph(5, 0);
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);

    int result[10];

    ASSERT_EQ(dfs_traversal(NULL, 0, result, 10), -1, "DFS NULL graph returns -1");
    ASSERT_EQ(dfs_traversal(g, 0, NULL, 10), -1, "DFS NULL result array returns -1");
    ASSERT_EQ(dfs_traversal(g, -1, result, 10), -1, "DFS negative start_vertex returns -1");
    ASSERT_EQ(dfs_traversal(g, 5, result, 10), -1, "DFS start_vertex >= num_vertices returns -1");
    ASSERT_EQ(dfs_traversal(g, 0, result, 0), -1, "DFS 0 capacity returns -1");
    ASSERT_EQ(dfs_traversal(g, 0, result, 2), -1, "DFS insufficient capacity returns -1");

    free_graph(g);
}

int main(void) {
    printf("Running Private DFS Tests...\n");
    test_dfs_undirected_tree();
    test_dfs_directed_cycles();
    test_dfs_disconnected();
    test_dfs_single_vertex();
    test_dfs_error_cases();

    if (failed) {
        fprintf(stderr, "Private DFS Tests FAILED!\n");
        return 1;
    }

    printf("All Private DFS Tests PASSED!\n");
    return 0;
}
