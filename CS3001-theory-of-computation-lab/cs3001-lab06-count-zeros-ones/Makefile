CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-count-basic \
        test-submission-count-empty-long \
        clean

# Run the public test suite against student's live count_symbols.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) count_symbols.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp count_symbols.c count_symbols.c.bak
	@cp reference/count_symbols.c count_symbols.c
	@$(CC) $(CFLAGS) count_symbols.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp count_symbols.c.bak count_symbols.c; \
	  rm -rf count_symbols.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-count-basic:
	$(call _grade,tests_private/test_count_basic.c)

test-submission-count-empty-long:
	$(call _grade,tests_private/test_count_empty_long.c)

clean:
	@rm -rf bin *.o *.bak count_symbols.c.bak
