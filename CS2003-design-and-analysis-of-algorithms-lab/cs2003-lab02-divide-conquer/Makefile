CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-sort-dc \
        test-submission-search-dc \
        clean

# Public test target — runs public_test against live divide_conquer.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) public_test.cpp divide_conquer.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp divide_conquer.cpp divide_conquer.cpp.bak
	@cp reference/divide_conquer.cpp divide_conquer.cpp
	@$(CXX) $(CXXFLAGS) $(1) divide_conquer.cpp -o bin/test_runner; EXIT=$$?; \
	  cp divide_conquer.cpp.bak divide_conquer.cpp; \
	  rm -f divide_conquer.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-sort-dc:
	$(call _grade,tests_private/test_sort_dc.cpp)

test-submission-search-dc:
	$(call _grade,tests_private/test_search_dc.cpp)

clean:
	@rm -rf bin *.o *.bak divide_conquer.cpp.bak
