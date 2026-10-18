CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-start-end-patterns \
        test-submission-combined-dfa \
        clean

# Run the public test suite against student's live dfa_match.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) dfa_match.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp dfa_match.c dfa_match.c.bak
	@cp reference/dfa_match.c dfa_match.c
	@$(CC) $(CFLAGS) dfa_match.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp dfa_match.c.bak dfa_match.c; \
	  rm -rf dfa_match.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-start-end-patterns:
	$(call _grade,tests_private/test_start_end_patterns.c)

test-submission-combined-dfa:
	$(call _grade,tests_private/test_combined_dfa.c)

clean:
	@rm -rf bin *.o *.bak dfa_match.c.bak
