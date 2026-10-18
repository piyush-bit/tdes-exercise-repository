# Makefile for CS2004 Lab 09: Supply Chain Relational Joins

define _grade
	@cp solution.sql solution.sql.bak
	@cp reference/solution.sql solution.sql
	@python3 $(1); EXIT=$$?; \
	  cp solution.sql.bak solution.sql; \
	  rm -f solution.sql.bak; exit $$EXIT
endef

.PHONY: test-public test-submission-inner-joins test-submission-outer-joins clean

test-public:
	@python3 public_test.py

test-submission-inner-joins:
	$(call _grade,tests_private/test_inner_joins.py)

test-submission-outer-joins:
	$(call _grade,tests_private/test_outer_joins.py)

clean:
	@rm -rf *.db solution.sql.bak __pycache__ tests_private/__pycache__
