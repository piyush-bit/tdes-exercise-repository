.PHONY: test-public \
        test-submission-sorting-ordering \
        test-submission-group-aggregates \
        clean

# Run the public test suite against student's solution.sql
test-public:
	@python3 -m unittest public_test.py

# ---------------------------------------------------------------------------
# Grading targets — one per private test group (Strategy B: Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@cp solution.sql solution.sql.bak
	@cp reference/solution.sql solution.sql
	@python3 -m unittest $(1); EXIT=$$?; \
	  cp solution.sql.bak solution.sql; \
	  rm -f solution.sql.bak; \
	  exit $$EXIT
endef

test-submission-sorting-ordering:
	$(call _grade,tests_private/test_sorting_ordering.py)

test-submission-group-aggregates:
	$(call _grade,tests_private/test_group_aggregates.py)

clean:
	@rm -rf __pycache__ tests_private/__pycache__ *.pyc *.db solution.sql.bak
