CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-advanced-sorts \
        test-submission-searches \
        clean

# Run the public test suite against student's live sort_search.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) sort_search.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp sort_search.c sort_search.c.bak
	@cp reference/sort_search.c sort_search.c
	@$(CC) $(CFLAGS) sort_search.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp sort_search.c.bak sort_search.c; \
	  rm -rf sort_search.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-advanced-sorts:
	$(call _grade,tests_private/test_adv_sorts.c)

test-submission-searches:
	$(call _grade,tests_private/test_searches.c)

clean:
	@rm -rf bin *.o *.bak sort_search.c.bak
