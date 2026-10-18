CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-traversal \
        test-submission-insertion \
        test-submission-deletion \
        clean

# Run the public test suite against student's live array_operations.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) array_operations.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp array_operations.c array_operations.c.bak
	@cp reference/array_operations.c array_operations.c
	@$(CC) $(CFLAGS) array_operations.c $(1) -o bin/test_runner; EXIT=$$?; \
	  cp array_operations.c.bak array_operations.c; \
	  rm -rf array_operations.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-traversal:
	$(call _grade,tests_private/test_traversal.c)

test-submission-insertion:
	$(call _grade,tests_private/test_insertion.c)

test-submission-deletion:
	$(call _grade,tests_private/test_deletion.c)

clean:
	@rm -rf bin *.o *.bak array_operations.c.bak
