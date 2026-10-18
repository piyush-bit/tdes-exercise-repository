CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-traversals \
        test-submission-insertion \
        test-submission-deletion \
        clean

# Run the public test suite against student's live binary_tree.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) binary_tree.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp binary_tree.c binary_tree.c.bak
	@cp reference/binary_tree.c binary_tree.c
	@$(CC) $(CFLAGS) binary_tree.c $(1) -o bin/test_runner; EXIT=$$?; \
	  cp binary_tree.c.bak binary_tree.c; \
	  rm -rf binary_tree.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-traversals:
	$(call _grade,tests_private/test_traversals.c)

test-submission-insertion:
	$(call _grade,tests_private/test_insertion.c)

test-submission-deletion:
	$(call _grade,tests_private/test_deletion.c)

clean:
	@rm -rf bin *.o *.bak binary_tree.c.bak
