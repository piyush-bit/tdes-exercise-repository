CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-push \
        test-submission-pop \
        test-submission-peek \
        clean

# Run the public test suite against student's live stack.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) stack.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp stack.c stack.c.bak
	@cp reference/stack.c stack.c
	@$(CC) $(CFLAGS) stack.c $(1) -o bin/test_runner; EXIT=$$?; \
	  cp stack.c.bak stack.c; \
	  rm -rf stack.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-push:
	$(call _grade,tests_private/test_push.c)

test-submission-pop:
	$(call _grade,tests_private/test_pop.c)

test-submission-peek:
	$(call _grade,tests_private/test_peek.c)

clean:
	@rm -rf bin *.o *.bak stack.c.bak
