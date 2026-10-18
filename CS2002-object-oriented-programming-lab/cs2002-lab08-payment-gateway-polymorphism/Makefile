CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-virtual-dispatch \
        test-submission-gateway-implementations \
        clean

# Run public tests against student's live payment_gateway.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) payment_gateway.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp payment_gateway.cpp payment_gateway.cpp.bak
	@cp reference/payment_gateway.cpp payment_gateway.cpp
	@$(CXX) $(CXXFLAGS) payment_gateway.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp payment_gateway.cpp.bak payment_gateway.cpp; \
	  rm -rf payment_gateway.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-virtual-dispatch:
	$(call _grade,tests_private/test_virtual_dispatch.cpp)

test-submission-gateway-implementations:
	$(call _grade,tests_private/test_gateways.cpp)

clean:
	@rm -rf bin *.o *.bak payment_gateway.cpp.bak
