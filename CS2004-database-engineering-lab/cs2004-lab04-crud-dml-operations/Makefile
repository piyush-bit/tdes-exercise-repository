.PHONY: test-public \
        test-submission-insert-update \
        test-submission-delete-select \
        clean

test-public:
	@python3 -m unittest public_test.py

define _grade
	@cp solution.sql solution.sql.bak
	@cp reference/solution.sql solution.sql
	@python3 tests_private/$(1).py; EXIT=$$?; \
	  cp solution.sql.bak solution.sql; \
	  rm -f solution.sql.bak; \
	  exit $$EXIT
endef

test-submission-insert-update:
	$(call _grade,test_insert_update)

test-submission-delete-select:
	$(call _grade,test_delete_select)

clean:
	@rm -rf __pycache__ tests_private/__pycache__ *.pyc solution.sql.bak
