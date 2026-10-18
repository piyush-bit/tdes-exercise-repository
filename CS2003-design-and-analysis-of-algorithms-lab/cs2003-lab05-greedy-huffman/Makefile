CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-fractional-knapsack \
        test-submission-huffman-compression \
        clean

# Run the public test suite against student's live greedy_huffman.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) greedy_huffman.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp greedy_huffman.cpp greedy_huffman.cpp.bak
	@cp reference/greedy_huffman.cpp greedy_huffman.cpp
	@$(CXX) $(CXXFLAGS) greedy_huffman.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp greedy_huffman.cpp.bak greedy_huffman.cpp; \
	  rm -rf greedy_huffman.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-fractional-knapsack:
	$(call _grade,tests_private/test_fractional_knapsack.cpp)

test-submission-huffman-compression:
	$(call _grade,tests_private/test_huffman_compression.cpp)

clean:
	@rm -rf bin *.o *.bak greedy_huffman.cpp.bak
