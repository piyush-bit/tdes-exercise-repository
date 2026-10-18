.PHONY: test-public test-submission-nested-subqueries test-submission-reporting-views clean

define _grade
	@cp solution.sql solution.sql.bak
	@cp reference/solution.sql solution.sql
	@python3 $(1); EXIT=$$?; \
	cp solution.sql.bak solution.sql; \
	rm -f solution.sql.bak; exit $$EXIT
endef

test-public:
	python3 public_test.py

test-submission-nested-subqueries:
	$(call _grade,tests_private/test_nested_subqueries.py)

test-submission-reporting-views:
	$(call _grade,tests_private/test_reporting_views.py)

clean:
	rm -f *.pyc *.bak
	rm -rf __pycache__ tests_private/__pycache__
