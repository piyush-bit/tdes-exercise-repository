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

void test_audit_inspector_friend_class() {
    std::cout << "--- Private Test: AuditInspector Friend Class ---\n";
    CryptoVault vault(7788, "TOKEN_DELTA", "SIG_DELTA_100", "CLASSIFIED_INFO");
    AuditInspector inspector;

    ASSERT_EQ(vault.getAuditAccessCount(), 0, "Audit count is 0 initially");

    // 1. inspectVaultKey
    std::string key_info = inspector.inspectVaultKey(vault);
    ASSERT_EQ(key_info, std::string("AUDIT_KEY:[PIN=7788|TOKEN=TOKEN_DELTA]"), "inspectVaultKey correctly reads private PIN and TOKEN");
    ASSERT_EQ(vault.getAuditAccessCount(), 1, "Audit count incremented to 1");

    // Fail authentication to populate failed_attempts
    vault.authenticate(0000);
    vault.authenticate(1111);
    ASSERT_EQ(vault.getFailedAttempts(), 2, "Failed attempts count is 2");

    // 2. getVaultFailedAttempts via inspector
    int inspector_failed = inspector.getVaultFailedAttempts(vault);
    ASSERT_EQ(inspector_failed, 2, "Inspector retrieves correct failed attempts");
    ASSERT_EQ(vault.getAuditAccessCount(), 2, "Audit count incremented to 2");

    // 3. forceBypassLock failure
    bool bypass_fail = inspector.forceBypassLock(vault, "INVALID_KEY");
    ASSERT_TRUE(!bypass_fail, "Force bypass fails with wrong override key");
    ASSERT_TRUE(!vault.isUnlocked(), "Vault remains locked after failed bypass");
    ASSERT_EQ(vault.getAuditAccessCount(), 3, "Audit count incremented to 3");

    // 4. forceBypassLock success
    bool bypass_pass = inspector.forceBypassLock(vault, "OVERRIDE_MASTER_999");
    ASSERT_TRUE(bypass_pass, "Force bypass succeeds with OVERRIDE_MASTER_999");
    ASSERT_TRUE(vault.isUnlocked(), "Vault unlocked after successful bypass");
    ASSERT_EQ(vault.getFailedAttempts(), 0, "Failed attempts reset to 0 after bypass");
    ASSERT_EQ(vault.getAuditAccessCount(), 4, "Audit count incremented to 4");
}

void test_log_security_alert_friend_function() {
    std::cout << "--- Private Test: logSecurityAlert Friend Function ---\n";
    CryptoVault vault(3344, "OMEGA_TOK", "SIG_OMEGA", "SENSITIVE_DOCS");

    // Locked state alert with failed attempts
    vault.authenticate(123);
    vault.authenticate(456);

    std::string alert1 = logSecurityAlert(vault, "UNAUTHORIZED_ACCESS");
    ASSERT_EQ(alert1, std::string("[ALERT][UNAUTHORIZED_ACCESS] Status: LOCKED | Failed: 2"), "Security alert matches expected format for locked vault");

    // Unlocked state alert
    vault.authenticate(3344);
    std::string alert2 = logSecurityAlert(vault, "ROUTINE_CHECK");
    ASSERT_EQ(alert2, std::string("[ALERT][ROUTINE_CHECK] Status: UNLOCKED | Failed: 0"), "Security alert matches expected format for unlocked vault");
}

int main() {
    test_audit_inspector_friend_class();
    test_log_security_alert_friend_function();

    if (failed) {
        std::cerr << "\nPrivate Friend Audit Tests Failed!\n";
        return 1;
    }

    std::cout << "\nAll Private Friend Audit Tests Passed Successfully!\n";
    return 0;
}
