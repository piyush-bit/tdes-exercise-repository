CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-lstack \
        test-submission-lqueue \
        clean

# Run the public test suite against student's live linked_sq.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) linked_sq.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp linked_sq.c linked_sq.c.bak
	@cp reference/linked_sq.c linked_sq.c
	@$(CC) $(CFLAGS) linked_sq.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp linked_sq.c.bak linked_sq.c; \
	  rm -rf linked_sq.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-lstack:
	$(call _grade,tests_private/test_lstack.c)

test-submission-lqueue:
	$(call _grade,tests_private/test_lqueue.c)

clean:
	@rm -rf bin *.o *.bak linked_sq.c.bak
