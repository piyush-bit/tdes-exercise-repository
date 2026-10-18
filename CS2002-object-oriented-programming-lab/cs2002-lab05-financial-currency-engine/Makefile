CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-binary-operators \
        test-submission-unary-operators \
        clean

# Run public tests against student's live currency_engine.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) currency_engine.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp currency_engine.cpp currency_engine.cpp.bak
	@cp reference/currency_engine.cpp currency_engine.cpp
	@$(CXX) $(CXXFLAGS) currency_engine.cpp $(1) -o bin/test_runner; EXIT=$$?; \
	  if [ -f currency_engine.cpp.bak ]; then mv -f currency_engine.cpp.bak currency_engine.cpp; fi; \
	  rm -rf bin/test_runner; \
	  exit $$EXIT
endef

test-submission-binary-operators:
	$(call _grade,tests_private/test_binary_ops.cpp)

test-submission-unary-operators:
	$(call _grade,tests_private/test_unary_ops.cpp)

clean:
	@rm -rf bin *.o *.bak currency_engine.cpp.bak
