CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-enqueue \
        test-submission-dequeue \
        test-submission-front \
        clean

# Run the public test suite against student's live queue.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) queue.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp queue.c queue.c.bak
	@cp reference/queue.c queue.c
	@$(CC) $(CFLAGS) queue.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp queue.c.bak queue.c; \
	  rm -rf queue.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-enqueue:
	$(call _grade,tests_private/test_enqueue.c)

test-submission-dequeue:
	$(call _grade,tests_private/test_dequeue.c)

test-submission-front:
	$(call _grade,tests_private/test_front.c)

clean:
	@rm -rf bin *.o *.bak queue.c.bak
