CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-static-pool \
        test-submission-inline-metrics \
        clean

# Run public tests against student's live microservice_pool.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) microservice_pool.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp microservice_pool.cpp microservice_pool.cpp.bak
	@cp reference/microservice_pool.cpp microservice_pool.cpp
	@$(CXX) $(CXXFLAGS) microservice_pool.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp microservice_pool.cpp.bak microservice_pool.cpp; \
	  rm -rf microservice_pool.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-static-pool:
	$(call _grade,tests_private/test_static_pool.cpp)

test-submission-inline-metrics:
	$(call _grade,tests_private/test_inline_metrics.cpp)

clean:
	@rm -rf bin *.o *.bak microservice_pool.cpp.bak
