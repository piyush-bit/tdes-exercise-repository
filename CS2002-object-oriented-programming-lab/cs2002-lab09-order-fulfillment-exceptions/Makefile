CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-custom-exceptions \
        test-submission-catch-all-handler \
        clean

# Run the public test suite against student's live order_fulfillment.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) order_fulfillment.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp order_fulfillment.cpp order_fulfillment.cpp.bak
	@cp reference/order_fulfillment.cpp order_fulfillment.cpp
	@$(CXX) $(CXXFLAGS) order_fulfillment.cpp $(1) -o bin/test_runner; EXIT=$$?; \
	  cp order_fulfillment.cpp.bak order_fulfillment.cpp; \
	  rm -rf order_fulfillment.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-custom-exceptions:
	$(call _grade,tests_private/test_custom_exceptions.cpp)

test-submission-catch-all-handler:
	$(call _grade,tests_private/test_catch_all.cpp)

clean:
	@rm -rf bin *.o *.bak order_fulfillment.cpp.bak
