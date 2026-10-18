.PHONY: test-public \
        test-submission-arithmetic-calculations \
        test-submission-computed-columns \
        clean

# Run public tests against student's solution.sql at live path
test-public:
	@python3 -m unittest public_test.py

# ---------------------------------------------------------------------------
# Grading targets — one per private test group (Strategy B: Inject & Restore)
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

test-submission-arithmetic-calculations:
	$(call _grade,test_arithmetic_calculations)

test-submission-computed-columns:
	$(call _grade,test_computed_columns)

clean:
	@rm -rf __pycache__ .pytest_cache *.pyc solution.sql.bak test_private_runner.py *.db
