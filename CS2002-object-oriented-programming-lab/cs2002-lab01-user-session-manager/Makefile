CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

.PHONY: test-public \
        test-submission-user-auth \
        test-submission-profile-update \
        clean

# Run the public test suite against student's live user_session.cpp
test-public:
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) user_session.cpp public_test.cpp -o bin/public_test
	@./bin/public_test

# ---------------------------------------------------------------------------
# Grading targets — Strategy B (Inject & Restore)
# ---------------------------------------------------------------------------

define _grade
	@mkdir -p bin
	@cp user_session.cpp user_session.cpp.bak
	@cp reference/user_session.cpp user_session.cpp
	@$(CXX) $(CXXFLAGS) user_session.cpp $(1) -o bin/test_runner && ./bin/test_runner; EXIT=$$?; \
	  cp user_session.cpp.bak user_session.cpp; \
	  rm -rf user_session.cpp.bak bin/test_runner; \
	  exit $$EXIT
endef

test-submission-user-auth:
	$(call _grade,tests_private/test_user_auth.cpp)

test-submission-profile-update:
	$(call _grade,tests_private/test_profile_update.cpp)

clean:
	@rm -rf bin *.o *.bak user_session.cpp.bak
