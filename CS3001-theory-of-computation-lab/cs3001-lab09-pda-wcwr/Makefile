CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.

.PHONY: test-public \
        test-submission-valid-wcwr \
        test-submission-invalid-wcwr \
        clean

test-public:
	@mkdir -p bin
	@$(CC) $(CFLAGS) pda_wcwr.c public_test.c -o bin/public_test
	@./bin/public_test

define _grade
	@mkdir -p bin
	@cp pda_wcwr.c pda_wcwr.c.bak
	@cp reference/pda_wcwr.c pda_wcwr.c
	@$(CC) $(CFLAGS) pda_wcwr.c $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp pda_wcwr.c.bak pda_wcwr.c; \
	  rm -rf pda_wcwr.c.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-valid-wcwr:
	$(call _grade,tests_private/test_valid_wcwr.c)

test-submission-invalid-wcwr:
	$(call _grade,tests_private/test_invalid_wcwr.c)

clean:
	@rm -rf bin *.o *.bak pda_wcwr.c.bak
