CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-function-overloading \
        test-submission-friend-audit \
        clean

# Run the public test suite against student's live crypto_vault.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) crypto_vault.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp crypto_vault.cpp crypto_vault.cpp.bak
	@cp reference/crypto_vault.cpp crypto_vault.cpp
	@$(CXX) $(CXXFLAGS) crypto_vault.cpp $(1) -o bin/test_runner; EXIT=$$?; \
	  cp crypto_vault.cpp.bak crypto_vault.cpp; \
	  rm -rf crypto_vault.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-function-overloading:
	$(call _grade,tests_private/test_overloading.cpp)

test-submission-friend-audit:
	$(call _grade,tests_private/test_friend_audit.cpp)

clean:
	@rm -rf bin *.o *.bak crypto_vault.cpp.bak
