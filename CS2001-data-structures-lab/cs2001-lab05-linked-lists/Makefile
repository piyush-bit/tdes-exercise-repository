CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-sll \
        test-submission-dll \
        clean

# Run the public test suite against student's live linked_lists.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) linked_lists.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp linked_lists.c linked_lists.c.bak
	@cp reference/linked_lists.c linked_lists.c
	@$(CC) $(CFLAGS) linked_lists.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp linked_lists.c.bak linked_lists.c; \
	  rm -rf linked_lists.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-sll:
	$(call _grade,tests_private/test_sll.c)

test-submission-dll:
	$(call _grade,tests_private/test_dll.c)

clean:
	@rm -rf bin *.o *.bak linked_lists.c.bak
