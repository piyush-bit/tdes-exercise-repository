CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-even-parity \
        test-submission-odd-parity \
        clean

# Run the public test suite against student's live even_parity.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) even_parity.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp even_parity.c even_parity.c.bak
	@cp reference/even_parity.c even_parity.c
	@$(CC) $(CFLAGS) even_parity.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp even_parity.c.bak even_parity.c; \
	  rm -rf even_parity.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-even-parity:
	$(call _grade,tests_private/test_even_parity.c)

test-submission-odd-parity:
	$(call _grade,tests_private/test_odd_parity.c)

clean:
	@rm -rf bin *.o *.bak even_parity.c.bak
