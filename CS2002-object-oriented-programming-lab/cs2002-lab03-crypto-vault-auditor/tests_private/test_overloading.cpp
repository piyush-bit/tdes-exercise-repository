#include "crypto_vault.hpp"
#include <iostream>
#include <string>

static int failed = 0;

#define ASSERT_TRUE(condition, msg) \
    do { \
        if (!(condition)) { \
            std::cerr << "[FAIL] " << msg << std::endl; \
            failed = 1; \
        } else { \
            std::cout << "[PASS] " << msg << std::endl; \
        } \
    } while (0)

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            std::cerr << "[FAIL] " << msg << ": Expected '" << (expected) << "', got '" << (actual) << "'" << std::endl; \
            failed = 1; \
        } else { \
            std::cout << "[PASS] " << msg << std::endl; \
        } \
    } while (0)

void test_pin_overload_thorough() {
    std::cout << "--- Private Test: PIN Authentication Overload ---\n";
    CryptoVault vault(4321, "TOK_BETA", "SIG_4321", "CONFIDENTIAL_PAYLOAD");

    ASSERT_TRUE(!vault.isUnlocked(), "Vault initial state locked");
    ASSERT_EQ(vault.getFailedAttempts(), 0, "Initial failed attempts is 0");

    // Attempt 1: wrong PIN
    ASSERT_TRUE(!vault.authenticate(1111), "Wrong PIN 1111 fails");
    ASSERT_EQ(vault.getFailedAttempts(), 1, "Failed attempts incremented to 1");

    // Attempt 2: wrong PIN
    ASSERT_TRUE(!vault.authenticate(2222), "Wrong PIN 2222 fails");
    ASSERT_EQ(vault.getFailedAttempts(), 2, "Failed attempts incremented to 2");

    // Attempt 3: correct PIN
    ASSERT_TRUE(vault.authenticate(4321), "Correct PIN 4321 succeeds");
    ASSERT_TRUE(vault.isUnlocked(), "Vault state is unlocked");
    ASSERT_EQ(vault.getFailedAttempts(), 0, "Failed attempts reset to 0 upon success");
    ASSERT_EQ(vault.getSecretData(), std::string("CONFIDENTIAL_PAYLOAD"), "Secret payload accessible");

    // Lock vault
    vault.lock();
    ASSERT_TRUE(!vault.isUnlocked(), "Vault locked after lock()");
    ASSERT_EQ(vault.getSecretData(), std::string("LOCKED: ACCESS DENIED"), "Secret payload denied after lock()");
}

void test_token_signature_overload_thorough() {
    std::cout << "--- Private Test: Token/Signature Authentication Overload ---\n";
    CryptoVault vault(9999, "TOKEN_GAMMA", "SIG_777", "RESTRICTED_DATA");

    // Attempt with wrong token
    ASSERT_TRUE(!vault.authenticate("WRONG_TOKEN", "SIG_777"), "Wrong token fails");
    ASSERT_EQ(vault.getFailedAttempts(), 1, "Failed attempts incremented to 1");

    // Attempt with wrong signature
    ASSERT_TRUE(!vault.authenticate("TOKEN_GAMMA", "WRONG_SIG"), "Wrong signature fails");
    ASSERT_EQ(vault.getFailedAttempts(), 2, "Failed attempts incremented to 2");

    // Attempt with correct token and signature
    ASSERT_TRUE(vault.authenticate("TOKEN_GAMMA", "SIG_777"), "Correct token and signature succeeds");
    ASSERT_TRUE(vault.isUnlocked(), "Vault state is unlocked");
    ASSERT_EQ(vault.getFailedAttempts(), 0, "Failed attempts reset to 0");
    ASSERT_EQ(vault.getSecretData(), std::string("RESTRICTED_DATA"), "Secret data unlocked");
}

int main() {
    test_pin_overload_thorough();
    test_token_signature_overload_thorough();

    if (failed) {
        std::cerr << "\nPrivate Overloading Tests Failed!\n";
        return 1;
    }

    std::cout << "\nAll Private Overloading Tests Passed Successfully!\n";
    return 0;
}
