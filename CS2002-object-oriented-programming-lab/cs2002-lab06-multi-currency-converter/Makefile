CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.
BIN_DIR = bin

.PHONY: all test-public test-submission-basic-class-conversion test-submission-class-class-conversion clean

all: test-public

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Public test target (runs against live currency_converter.cpp)
test-public: $(BIN_DIR) currency_converter.cpp currency_converter.hpp public_test.cpp
	$(CXX) $(CXXFLAGS) currency_converter.cpp public_test.cpp -o $(BIN_DIR)/public_test
	@./$(BIN_DIR)/public_test

# Strategy B Inject & Restore macro
define _grade
	@cp currency_converter.cpp currency_converter.cpp.bak
	@cp reference/currency_converter.cpp currency_converter.cpp
	@$(CXX) $(CXXFLAGS) currency_converter.cpp $(1) -o $(BIN_DIR)/test_sub && ./$(BIN_DIR)/test_sub; EXIT=$$?; \
	  cp currency_converter.cpp.bak currency_converter.cpp; \
	  rm -f currency_converter.cpp.bak; exit $$EXIT
endef

# Grading target 1: basic class conversion (5 pts)
test-submission-basic-class-conversion: $(BIN_DIR) currency_converter.hpp tests_private/test_basic_conversion.cpp
	$(call _grade,tests_private/test_basic_conversion.cpp)

# Grading target 2: class-to-class conversion (5 pts)
test-submission-class-class-conversion: $(BIN_DIR) currency_converter.hpp tests_private/test_class_conversion.cpp
	$(call _grade,tests_private/test_class_conversion.cpp)

clean:
	rm -rf $(BIN_DIR) *.o *.bak
