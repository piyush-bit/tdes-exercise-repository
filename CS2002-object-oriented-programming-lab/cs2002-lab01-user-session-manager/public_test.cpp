#include "user_session.hpp"
#include <iostream>
#include <cassert>

void test_basic_authentication() {
    UserAccount user(101, "alice_w", "alice@example.com", "sha256_pass_hash_123");
    
    assert(!user.getIsLoggedIn());
    
    // Failed authentication attempt with wrong hash
    bool authFailed = user.authenticate("sha256_wrong_hash");
    assert(!authFailed);
    assert(!user.getIsLoggedIn());
    
    // Successful authentication attempt
    bool authSuccess = user.authenticate("sha256_pass_hash_123");
    assert(authSuccess);
    assert(user.getIsLoggedIn());
    
    // Logout session
    user.logout();
    assert(!user.getIsLoggedIn());
    
    std::cout << "[PASS] test_basic_authentication" << std::endl;
}

void test_profile_retrieval() {
    UserAccount user(102, "bob_m", "bob@example.com", "sha256_bob_pass");
    
    std::string expectedLoggedOut = "ID: 102 | User: bob_m | Email: bob@example.com | Status: Logged Out";
    assert(user.getProfileSummary() == expectedLoggedOut);
    
    user.authenticate("sha256_bob_pass");
    std::string expectedLoggedIn = "ID: 102 | User: bob_m | Email: bob@example.com | Status: Logged In";
    assert(user.getProfileSummary() == expectedLoggedIn);
    
    std::cout << "[PASS] test_profile_retrieval" << std::endl;
}

int main() {
    std::cout << "=== Public Test Suite ===" << std::endl;
    test_basic_authentication();
    test_profile_retrieval();
    std::cout << "All public tests passed successfully!" << std::endl;
    return 0;
}
