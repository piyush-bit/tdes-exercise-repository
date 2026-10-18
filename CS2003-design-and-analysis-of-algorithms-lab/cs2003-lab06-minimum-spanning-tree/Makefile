CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-kruskal-mst \
        test-submission-prim-mst \
        clean

# Run public test suite against live student mst_optimizer.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) mst_optimizer.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp mst_optimizer.cpp mst_optimizer.cpp.bak
	@cp reference/mst_optimizer.cpp mst_optimizer.cpp
	@$(CXX) $(CXXFLAGS) mst_optimizer.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp mst_optimizer.cpp.bak mst_optimizer.cpp; \
	  rm -rf mst_optimizer.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-kruskal-mst:
	$(call _grade,tests_private/test_kruskal.cpp)

test-submission-prim-mst:
	$(call _grade,tests_private/test_prim.cpp)

clean:
	@rm -rf bin *.o *.bak mst_optimizer.cpp.bak
