#include "user_session.hpp"
#include <iostream>
#include <cassert>

void test_initial_state() {
    UserAccount user(201, "charlie_k", "charlie@domain.org", "secret_hash_99");
    assert(user.getUserId() == 201);
    assert(user.getUsername() == "charlie_k");
    assert(user.getEmail() == "charlie@domain.org");
    assert(user.getPasswordHash() == "secret_hash_99");
    assert(!user.getIsLoggedIn());
}

void test_authentication_flow() {
    UserAccount user(202, "diana_p", "diana@domain.org", "diana_secure_hash");

    // Invalid attempts
    assert(!user.authenticate(""));
    assert(!user.getIsLoggedIn());
    assert(!user.authenticate("wrong_hash"));
    assert(!user.getIsLoggedIn());

    // Valid authentication
    assert(user.authenticate("diana_secure_hash"));
    assert(user.getIsLoggedIn());

    // Re-authenticating while logged in
    assert(user.authenticate("diana_secure_hash"));
    assert(user.getIsLoggedIn());

    // Logout
    user.logout();
    assert(!user.getIsLoggedIn());

    // Failed attempt after logout
    assert(!user.authenticate("bad_hash"));
    assert(!user.getIsLoggedIn());

    // Successful relogin
    assert(user.authenticate("diana_secure_hash"));
    assert(user.getIsLoggedIn());
}

void test_multiple_accounts_isolation() {
    UserAccount user1(301, "account1", "acc1@test.com", "hash1");
    UserAccount user2(302, "account2", "acc2@test.com", "hash2");

    assert(user1.authenticate("hash1"));
    assert(user1.getIsLoggedIn());
    assert(!user2.getIsLoggedIn());

    assert(!user2.authenticate("hash1")); // cross account hash mismatch
    assert(!user2.getIsLoggedIn());

    assert(user2.authenticate("hash2"));
    assert(user2.getIsLoggedIn());

    user1.logout();
    assert(!user1.getIsLoggedIn());
    assert(user2.getIsLoggedIn());
}

int main() {
    std::cout << "=== Running Private Test Suite: User Auth ===" << std::endl;
    test_initial_state();
    test_authentication_flow();
    test_multiple_accounts_isolation();
    std::cout << "All user auth private tests passed successfully!" << std::endl;
    return 0;
}
