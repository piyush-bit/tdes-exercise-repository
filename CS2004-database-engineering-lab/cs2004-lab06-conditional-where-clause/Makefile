.PHONY: test-public test-submission-comparison-filtering test-submission-range-filtering clean

PYTHON ?= python3

define _grade
	@cp solution.sql solution.sql.bak
	@cp reference/solution.sql solution.sql
	@$(PYTHON) $(1); EXIT=$$?; \
	  cp solution.sql.bak solution.sql; \
	  rm -f solution.sql.bak; exit $$EXIT
endef

test-public:
	$(PYTHON) public_test.py

test-submission-comparison-filtering:
	$(call _grade,tests_private/test_comparison_filtering.py)

test-submission-range-filtering:
	$(call _grade,tests_private/test_range_filtering.py)

clean:
	rm -f *.pyc *.bak
	rm -rf __pycache__ tests_private/__pycache__
