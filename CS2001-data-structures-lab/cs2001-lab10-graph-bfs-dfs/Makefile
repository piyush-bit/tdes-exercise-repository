CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-graph-bfs \
        test-submission-graph-dfs \
        clean

# Run public tests against student's live graph.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) graph.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp graph.c graph.c.bak
	@cp reference/graph.c graph.c
	@$(CC) $(CFLAGS) graph.c $(1) -o bin/test_runner; EXIT=$$?; \
	  cp graph.c.bak graph.c; \
	  rm -rf graph.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-graph-bfs:
	$(call _grade,tests_private/test_graph_bfs.c)

test-submission-graph-dfs:
	$(call _grade,tests_private/test_graph_dfs.c)

clean:
	@rm -rf bin *.o *.bak graph.c.bak
