CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-function-templates \
        test-submission-class-templates \
        clean

# Run the public test suite against student's live generic_cache.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp generic_cache.cpp generic_cache.cpp.bak
	@cp reference/generic_cache.cpp generic_cache.cpp
	@$(CXX) $(CXXFLAGS) $(1) -o bin/test_runner; EXIT=$$?; \
	  cp generic_cache.cpp.bak generic_cache.cpp; \
	  rm -rf generic_cache.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-function-templates:
	$(call _grade,tests_private/test_function_templates.cpp)

test-submission-class-templates:
	$(call _grade,tests_private/test_class_templates.cpp)

clean:
	@rm -rf bin *.o *.bak generic_cache.cpp.bak
