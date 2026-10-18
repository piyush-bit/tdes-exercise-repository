PYTHON = python3

.PHONY: test-public \
        test-submission-complex-boolean \
        test-submission-operator-expressions \
        clean

# Run public tests against student's live solution.sql
test-public:
	@$(PYTHON) test_harness.py public_test.py

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@cp solution.sql solution.sql.bak
	@cp reference/solution.sql solution.sql
	@$(PYTHON) test_harness.py $(1); EXIT=$$?; \
	  if [ -f solution.sql.bak ]; then mv -f solution.sql.bak solution.sql; fi; \
	  exit $$EXIT
endef

test-submission-complex-boolean:
	$(call _grade,tests_private/test_complex_boolean.py)

test-submission-operator-expressions:
	$(call _grade,tests_private/test_operator_expressions.py)

clean:
	@rm -rf *.pyc __pycache__ *.bak
