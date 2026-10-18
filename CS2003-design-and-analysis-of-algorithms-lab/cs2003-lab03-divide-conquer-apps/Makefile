CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-trade-merging \
        test-submission-price-threshold \
        clean

# Run the public test suite against student's live divide_conquer_apps.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) divide_conquer_apps.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp divide_conquer_apps.cpp divide_conquer_apps.cpp.bak
	@cp reference/divide_conquer_apps.cpp divide_conquer_apps.cpp
	@$(CXX) $(CXXFLAGS) divide_conquer_apps.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp divide_conquer_apps.cpp.bak divide_conquer_apps.cpp; \
	  rm -rf divide_conquer_apps.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-trade-merging:
	$(call _grade,tests_private/test_trade_merging.cpp)

test-submission-price-threshold:
	$(call _grade,tests_private/test_price_threshold.cpp)

clean:
	@rm -rf bin *.o *.bak divide_conquer_apps.cpp.bak
