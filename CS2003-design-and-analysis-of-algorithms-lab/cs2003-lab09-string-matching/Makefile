CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-naive-matcher \
        test-submission-rabin-karp-matcher \
        clean

# Run public tests against student's live string_matching.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) string_matching.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp string_matching.cpp string_matching.cpp.bak
	@cp reference/string_matching.cpp string_matching.cpp
	@$(CXX) $(CXXFLAGS) string_matching.cpp $(1) -o bin/test_runner; EXIT=$$?; \
	  if [ -f string_matching.cpp.bak ]; then mv -f string_matching.cpp.bak string_matching.cpp; fi; \
	  rm -rf bin/test_runner; \
	  exit $$EXIT
endef

test-submission-naive-matcher:
	$(call _grade,tests_private/test_naive.cpp)

test-submission-rabin-karp-matcher:
	$(call _grade,tests_private/test_rabin_karp.cpp)

clean:
	@rm -rf bin *.o *.bak string_matching.cpp.bak
