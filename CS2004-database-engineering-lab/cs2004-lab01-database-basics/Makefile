.PHONY: test-public \
        test-submission-catalog-creation \
        test-submission-schema-metadata \
        clean

# Student public local test runner
test-public:
	@python3 -m unittest public_test.py

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

test-submission-catalog-creation:
	$(call _grade,test_catalog_creation)

test-submission-schema-metadata:
	$(call _grade,test_schema_metadata)

clean:
	@rm -rf __pycache__ .pytest_cache *.pyc *.db solution.sql.bak test_private_runner.py
