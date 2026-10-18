CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-multilevel-inheritance \
        test-submission-multiple-inheritance \
        clean

# Run public tests against student's live fleet_hierarchy.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) fleet_hierarchy.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp fleet_hierarchy.cpp fleet_hierarchy.cpp.bak
	@cp reference/fleet_hierarchy.cpp fleet_hierarchy.cpp
	@$(CXX) $(CXXFLAGS) fleet_hierarchy.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp fleet_hierarchy.cpp.bak fleet_hierarchy.cpp; \
	  rm -rf fleet_hierarchy.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-multilevel-inheritance:
	$(call _grade,tests_private/test_multilevel.cpp)

test-submission-multiple-inheritance:
	$(call _grade,tests_private/test_multiple.cpp)

clean:
	@rm -rf bin *.o *.bak fleet_hierarchy.cpp.bak
