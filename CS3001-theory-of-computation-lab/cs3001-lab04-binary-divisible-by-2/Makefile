CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-even-binary \
        test-submission-odd-binary \
        clean

# Run the public test suite against student's live divisible_by_2.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) divisible_by_2.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp divisible_by_2.c divisible_by_2.c.bak
	@cp reference/divisible_by_2.c divisible_by_2.c
	@rm -f bin/test_runner
	@$(CC) $(CFLAGS) divisible_by_2.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp divisible_by_2.c.bak divisible_by_2.c; \
	  rm -f divisible_by_2.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-even-binary:
	$(call _grade,tests_private/test_even_binary.c)

test-submission-odd-binary:
	$(call _grade,tests_private/test_odd_binary.c)

clean:
	@rm -rf bin *.o *.bak divisible_by_2.c.bak
