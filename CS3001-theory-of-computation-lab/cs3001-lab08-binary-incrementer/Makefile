CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99

.PHONY: all test-public test-submission-increment-basic test-submission-overflow-carry clean

all: test-public

test-public:
	$(CC) $(CFLAGS) binary_incrementer.c public_test.c -o test_public_bin
	./test_public_bin

define _grade
	@cp binary_incrementer.c binary_incrementer.c.bak
	@cp reference/binary_incrementer.c binary_incrementer.c
	@$(CC) $(CFLAGS) binary_incrementer.c $(1) -o test_priv_bin && ./test_priv_bin; EXIT=$$?; \
	  cp binary_incrementer.c.bak binary_incrementer.c; \
	  rm -f binary_incrementer.c.bak test_priv_bin; exit $$EXIT
endef

test-submission-increment-basic:
	$(call _grade,tests_private/test_increment_basic.c)

test-submission-overflow-carry:
	$(call _grade,tests_private/test_overflow_carry.c)

clean:
	rm -f test_public_bin test_priv_bin binary_incrementer.c.bak
