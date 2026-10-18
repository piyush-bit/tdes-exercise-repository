CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-mod3-eval \
        test-submission-mod3-large \
        clean

# Run the public test suite against student's live mod3_machine.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) mod3_machine.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp mod3_machine.c mod3_machine.c.bak
	@cp reference/mod3_machine.c mod3_machine.c
	@$(CC) $(CFLAGS) mod3_machine.c $(1) -o bin/test_runner; EXIT=$$?; \
	  cp mod3_machine.c.bak mod3_machine.c; \
	  rm -rf mod3_machine.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-mod3-eval:
	$(call _grade,tests_private/test_mod3_eval.c)

test-submission-mod3-large:
	$(call _grade,tests_private/test_mod3_large.c)

clean:
	@rm -rf bin *.o *.bak mod3_machine.c.bak
