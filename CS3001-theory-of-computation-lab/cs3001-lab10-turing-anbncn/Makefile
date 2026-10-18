CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-valid-anbncn \
        test-submission-invalid-anbncn \
        clean

# Public test suite against student's live turing_anbncn.c
test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) turing_anbncn.c public_test.c -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp turing_anbncn.c turing_anbncn.c.bak
	@cp reference/turing_anbncn.c turing_anbncn.c
	@$(CC) $(CFLAGS) turing_anbncn.c $(1) -o bin/test_runner; \
	  if [ $$? -eq 0 ]; then \
	    ./bin/test_runner; EXIT=$$?; \
	  else \
	    EXIT=$$?; \
	  fi; \
	  cp turing_anbncn.c.bak turing_anbncn.c; \
	  rm -f turing_anbncn.c.bak; \
	  rm -rf bin/test_runner; \
	  exit $$EXIT
endef

test-submission-valid-anbncn:
	$(call _grade,tests_private/test_valid_anbncn.c)

test-submission-invalid-anbncn:
	$(call _grade,tests_private/test_invalid_anbncn.c)

clean:
	@rm -rf bin *.o *.bak turing_anbncn.c.bak
