CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-nqueens-solver \
        test-submission-branch-bound-pruning \
        clean

# Run the public test suite against student's live nqueens_solver.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) nqueens_solver.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp nqueens_solver.cpp nqueens_solver.cpp.bak
	@cp reference/nqueens_solver.cpp nqueens_solver.cpp
	@$(CXX) $(CXXFLAGS) nqueens_solver.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp nqueens_solver.cpp.bak nqueens_solver.cpp; \
	  rm -rf nqueens_solver.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-nqueens-solver:
	$(call _grade,tests_private/test_nqueens.cpp)

test-submission-branch-bound-pruning:
	$(call _grade,tests_private/test_branch_bound.cpp)

clean:
	@rm -rf bin *.o *.bak nqueens_solver.cpp.bak
