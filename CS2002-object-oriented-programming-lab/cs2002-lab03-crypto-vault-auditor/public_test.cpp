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

void test_overloaded_authentication() {
    std::cout << "--- Running Public Test: Overloaded Authentication ---\n";
    CryptoVault vault(1234, "SEC_TOKEN", "SIG_8899", "TOP_SECRET_PAYLOAD");

    ASSERT_TRUE(!vault.isUnlocked(), "Vault starts locked");
    ASSERT_EQ(vault.getSecretData(), std::string("LOCKED: ACCESS DENIED"), "Secret data locked initially");

    // Test PIN authentication failure
    bool auth_fail = vault.authenticate(9999);
    ASSERT_TRUE(!auth_fail, "Wrong PIN returns false");
    ASSERT_EQ(vault.getFailedAttempts(), 1, "Failed attempts count is 1 after wrong PIN");

    // Test PIN authentication success
    bool auth_pass = vault.authenticate(1234);
    ASSERT_TRUE(auth_pass, "Correct PIN returns true");
    ASSERT_TRUE(vault.isUnlocked(), "Vault is unlocked after correct PIN");
    ASSERT_EQ(vault.getFailedAttempts(), 0, "Failed attempts reset to 0 after success");
    ASSERT_EQ(vault.getSecretData(), std::string("TOP_SECRET_PAYLOAD"), "Secret data accessible when unlocked");

    // Lock vault
    vault.lock();
    ASSERT_TRUE(!vault.isUnlocked(), "Vault is locked after lock()");

    // Test Token/Signature overload failure
    bool token_fail = vault.authenticate("SEC_TOKEN", "WRONG_SIG");
    ASSERT_TRUE(!token_fail, "Wrong signature returns false");
    ASSERT_EQ(vault.getFailedAttempts(), 1, "Failed attempts count is 1 after wrong signature");

    // Test Token/Signature overload success
    bool token_pass = vault.authenticate("SEC_TOKEN", "SIG_8899");
    ASSERT_TRUE(token_pass, "Correct token & signature returns true");
    ASSERT_TRUE(vault.isUnlocked(), "Vault unlocked after token authentication");
    ASSERT_EQ(vault.getFailedAttempts(), 0, "Failed attempts reset to 0");
}

void test_friend_inspector_key_audit() {
    std::cout << "--- Running Public Test: Friend Inspector Key Audit ---\n";
    CryptoVault vault(5678, "ALPHA_TOKEN", "SIG_99", "VAULT_DATA");
    AuditInspector inspector;

    ASSERT_EQ(vault.getAuditAccessCount(), 0, "Audit access count starts at 0");

    std::string audit_key = inspector.inspectVaultKey(vault);
    ASSERT_EQ(audit_key, std::string("AUDIT_KEY:[PIN=5678|TOKEN=ALPHA_TOKEN]"), "inspectVaultKey returns formatted key details");
    ASSERT_EQ(vault.getAuditAccessCount(), 1, "Audit access count incremented after key inspection");
}

int main() {
    test_overloaded_authentication();
    test_friend_inspector_key_audit();

    if (failed) {
        std::cerr << "\nPublic tests failed!\n";
        return 1;
    }

    std::cout << "\nAll Public Tests Passed Successfully!\n";
    return 0;
}
