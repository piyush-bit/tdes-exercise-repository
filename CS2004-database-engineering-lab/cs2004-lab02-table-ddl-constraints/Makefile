.PHONY: test-public \
        test-submission-table-structure \
        test-submission-constraints-validation \
        clean

# Public test suite run against student's solution.sql
test-public:
	@python3 public_test.py

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@cp solution.sql solution.sql.bak
	@cp reference/solution.sql solution.sql
	@cp tests_private/$(1).py test_private_runner.py
	@python3 -m unittest test_private_runner.py; EXIT=$$?; \
	  cp solution.sql.bak solution.sql; \
	  rm -f solution.sql.bak test_private_runner.py; \
	  exit $$EXIT
endef

test-submission-table-structure:
	$(call _grade,test_table_structure)

test-submission-constraints-validation:
	$(call _grade,test_constraints_validation)

clean:
	@rm -rf __pycache__ .pytest_cache *.pyc solution.sql.bak test_private_runner.py
