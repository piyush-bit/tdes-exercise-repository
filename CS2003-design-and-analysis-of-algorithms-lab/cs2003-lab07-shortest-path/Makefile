CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-dijkstra \
        test-submission-bellman-ford \
        clean

# Run the public test suite against student's live shortest_path.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) public_test.cpp shortest_path.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp shortest_path.cpp shortest_path.cpp.bak
	@cp reference/shortest_path.cpp shortest_path.cpp
	@$(CXX) $(CXXFLAGS) $(1) shortest_path.cpp -o bin/test_runner; EXIT=$$?; \
	  cp shortest_path.cpp.bak shortest_path.cpp; \
	  rm -rf shortest_path.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-dijkstra:
	$(call _grade,tests_private/test_dijkstra.cpp)

test-submission-bellman-ford:
	$(call _grade,tests_private/test_bellman_ford.cpp)

clean:
	@rm -rf bin *.o *.bak shortest_path.cpp.bak
