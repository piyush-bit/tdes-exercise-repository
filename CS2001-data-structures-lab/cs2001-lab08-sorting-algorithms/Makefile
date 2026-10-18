CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-basic-sorts \
        test-submission-heap-sort \
        clean

# Run the public test suite against student's live sorting.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) sorting.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp sorting.c sorting.c.bak
	@cp reference/sorting.c sorting.c
	@$(CC) $(CFLAGS) sorting.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp sorting.c.bak sorting.c; \
	  rm -rf sorting.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-basic-sorts:
	$(call _grade,tests_private/test_basic_sorts.c)

test-submission-heap-sort:
	$(call _grade,tests_private/test_heap_sort.c)

clean:
	@rm -rf bin *.o *.bak sorting.c.bak
