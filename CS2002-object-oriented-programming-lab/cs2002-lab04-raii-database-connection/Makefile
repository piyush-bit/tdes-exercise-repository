CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-constructors \
        test-submission-raii-destructor \
        clean

# Run the public test suite against student's live db_connection.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) db_connection.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp db_connection.cpp db_connection.cpp.bak
	@cp reference/db_connection.cpp db_connection.cpp
	@$(CXX) $(CXXFLAGS) db_connection.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp db_connection.cpp.bak db_connection.cpp; \
	  rm -rf db_connection.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-constructors:
	$(call _grade,tests_private/test_constructors.cpp)

test-submission-raii-destructor:
	$(call _grade,tests_private/test_raii_destructor.cpp)

clean:
	@rm -rf bin *.o *.bak db_connection.cpp.bak
