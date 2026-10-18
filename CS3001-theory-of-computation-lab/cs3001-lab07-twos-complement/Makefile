CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-twos-comp-basic \
        test-submission-twos-comp-advanced \
        clean

# Run public tests against student's live twos_complement.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) twos_complement.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp twos_complement.c twos_complement.c.bak
	@cp reference/twos_complement.c twos_complement.c
	@$(CC) $(CFLAGS) twos_complement.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp twos_complement.c.bak twos_complement.c; \
	  rm -f twos_complement.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-twos-comp-basic:
	$(call _grade,tests_private/test_twos_comp_basic.c)

test-submission-twos-comp-advanced:
	$(call _grade,tests_private/test_twos_comp_advanced.c)

clean:
	@rm -rf bin *.o *.bak twos_complement.c.bak
