CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-conversion \
        test-submission-evaluation \
        clean

# Run public tests against student's live infix_postfix.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) infix_postfix.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp infix_postfix.c infix_postfix.c.bak
	@cp reference/infix_postfix.c infix_postfix.c
	@$(CC) $(CFLAGS) infix_postfix.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp infix_postfix.c.bak infix_postfix.c; \
	  rm -rf infix_postfix.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-conversion:
	$(call _grade,tests_private/test_conversion.c)

test-submission-evaluation:
	$(call _grade,tests_private/test_evaluation.c)

clean:
	@rm -rf bin *.o *.bak infix_postfix.c.bak
