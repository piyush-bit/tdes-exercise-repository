#include "user_session.hpp"
#include <iostream>
#include <cassert>

void test_update_email_logged_out() {
    UserAccount user(401, "eve_s", "eve@old.com", "hash_eve");
    assert(!user.getIsLoggedIn());

    // Attempt email update while logged out
    bool result = user.updateEmail("eve@new.com");
    assert(!result);
    assert(user.getEmail() == "eve@old.com");
}

void test_update_email_invalid_input() {
    UserAccount user(402, "frank_t", "frank@old.com", "hash_frank");
    user.authenticate("hash_frank");
    assert(user.getIsLoggedIn());

    // Empty email
    assert(!user.updateEmail(""));
    assert(user.getEmail() == "frank@old.com");

    // Invalid email missing '@'
    assert(!user.updateEmail("franknewdomain.com"));
    assert(user.getEmail() == "frank@old.com");
}

void test_update_email_success_and_summary() {
    UserAccount user(403, "grace_h", "grace@old.com", "hash_grace");

    // Initial summary
    std::string expectedInitial = "ID: 403 | User: grace_h | Email: grace@old.com | Status: Logged Out";
    assert(user.getProfileSummary() == expectedInitial);

    // Authenticate
    assert(user.authenticate("hash_grace"));
    std::string expectedLoggedIn = "ID: 403 | User: grace_h | Email: grace@old.com | Status: Logged In";
    assert(user.getProfileSummary() == expectedLoggedIn);

    // Valid email update
    assert(user.updateEmail("grace@new.org"));
    assert(user.getEmail() == "grace@new.org");
    std::string expectedUpdated = "ID: 403 | User: grace_h | Email: grace@new.org | Status: Logged In";
    assert(user.getProfileSummary() == expectedUpdated);

    // Second valid email update
    assert(user.updateEmail("grace.h@company.io"));
    assert(user.getEmail() == "grace.h@company.io");

    // Logout and check summary
    user.logout();
    std::string expectedLoggedOutUpdated = "ID: 403 | User: grace_h | Email: grace.h@company.io | Status: Logged Out";
    assert(user.getProfileSummary() == expectedLoggedOutUpdated);
}

int main() {
    std::cout << "=== Running Private Test Suite: Profile Update ===" << std::endl;
    test_update_email_logged_out();
    test_update_email_invalid_input();
    test_update_email_success_and_summary();
    std::cout << "All profile update private tests passed successfully!" << std::endl;
    return 0;
}
