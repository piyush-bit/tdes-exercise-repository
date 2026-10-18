CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-basic-sort-analysis \
        test-submission-heap-sort-analysis \
        clean

# Run the public test suite against student's live sorting_benchmark.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) sorting_benchmark.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp sorting_benchmark.cpp sorting_benchmark.cpp.bak
	@cp reference/sorting_benchmark.cpp sorting_benchmark.cpp
	@$(CXX) $(CXXFLAGS) sorting_benchmark.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp sorting_benchmark.cpp.bak sorting_benchmark.cpp; \
	  rm -rf sorting_benchmark.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-basic-sort-analysis:
	$(call _grade,tests_private/test_basic_sorts.cpp)

test-submission-heap-sort-analysis:
	$(call _grade,tests_private/test_heap_sort.cpp)

clean:
	@rm -rf bin *.o *.bak sorting_benchmark.cpp.bak
