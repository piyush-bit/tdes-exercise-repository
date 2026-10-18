CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-lcs-diff \
        test-submission-knapsack-mcm \
        clean

# Run public tests against student's live dynamic_programming.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) public_test.cpp dynamic_programming.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp dynamic_programming.cpp dynamic_programming.cpp.bak
	@cp reference/dynamic_programming.cpp dynamic_programming.cpp
	@$(CXX) $(CXXFLAGS) $(1) dynamic_programming.cpp -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp dynamic_programming.cpp.bak dynamic_programming.cpp; \
	  rm -rf dynamic_programming.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-lcs-diff:
	$(call _grade,tests_private/test_lcs_diff.cpp)

test-submission-knapsack-mcm:
	$(call _grade,tests_private/test_knapsack_mcm.cpp)

clean:
	@rm -rf bin *.o *.bak dynamic_programming.cpp.bak
