CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-mst-preorder-tour \
        test-submission-tsp-approx-bound \
        clean

# Run the public test suite against student's live approx_tsp.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) approx_tsp.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp approx_tsp.cpp approx_tsp.cpp.bak
	@cp reference/approx_tsp.cpp approx_tsp.cpp
	@$(CXX) $(CXXFLAGS) approx_tsp.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp approx_tsp.cpp.bak approx_tsp.cpp; \
	  rm -rf approx_tsp.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-mst-preorder-tour:
	$(call _grade,tests_private/test_mst_tour.cpp)

test-submission-tsp-approx-bound:
	$(call _grade,tests_private/test_approx_bound.cpp)

clean:
	@rm -rf bin *.o *.bak approx_tsp.cpp.bak
