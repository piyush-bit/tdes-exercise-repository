CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-accept-states \
        test-submission-reject-states \
        clean

# Run the public test suite against student's live consecutive_ones.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) consecutive_ones.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp consecutive_ones.c consecutive_ones.c.bak
	@cp reference/consecutive_ones.c consecutive_ones.c
	@$(CC) $(CFLAGS) consecutive_ones.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp consecutive_ones.c.bak consecutive_ones.c; \
	  rm -rf consecutive_ones.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-accept-states:
	$(call _grade,tests_private/test_accept_states.c)

test-submission-reject-states:
	$(call _grade,tests_private/test_reject_states.c)

clean:
	@rm -rf bin *.o *.bak consecutive_ones.c.bak
