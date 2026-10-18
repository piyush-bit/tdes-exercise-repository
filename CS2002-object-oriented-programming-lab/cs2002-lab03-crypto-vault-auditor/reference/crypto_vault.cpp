#include "crypto_vault.hpp"

CryptoVault::CryptoVault(int pin, const std::string& token, const std::string& signature, const std::string& secret)
    : master_pin(pin),
      secret_token(token),
      token_signature(signature),
      secret_data(secret),
      is_unlocked(false),
      failed_attempts(0),
      audit_access_count(0) {}

bool CryptoVault::authenticate(int pin) {
    if (pin == master_pin) {
        is_unlocked = true;
        failed_attempts = 0;
        return true;
    }
    failed_attempts++;
    is_unlocked = false;
    return false;
}

bool CryptoVault::authenticate(const std::string& token, const std::string& signature) {
    if (token == secret_token && signature == token_signature) {
        is_unlocked = true;
        failed_attempts = 0;
        return true;
    }
    failed_attempts++;
    is_unlocked = false;
    return false;
}

void CryptoVault::lock() {
    is_unlocked = false;
}

bool CryptoVault::isUnlocked() const {
    return is_unlocked;
}

int CryptoVault::getFailedAttempts() const {
    return failed_attempts;
}

int CryptoVault::getAuditAccessCount() const {
    return audit_access_count;
}

std::string CryptoVault::getSecretData() const {
    if (is_unlocked) {
        return secret_data;
    }
    return "LOCKED: ACCESS DENIED";
}

std::string AuditInspector::inspectVaultKey(CryptoVault& vault) const {
    vault.audit_access_count++;
    return "AUDIT_KEY:[PIN=" + std::to_string(vault.master_pin) + "|TOKEN=" + vault.secret_token + "]";
}

bool AuditInspector::forceBypassLock(CryptoVault& vault, const std::string& master_override_key) {
    vault.audit_access_count++;
    if (master_override_key == "OVERRIDE_MASTER_999") {
        vault.is_unlocked = true;
        vault.failed_attempts = 0;
        return true;
    }
    return false;
}

int AuditInspector::getVaultFailedAttempts(CryptoVault& vault) const {
    vault.audit_access_count++;
    return vault.failed_attempts;
}

std::string logSecurityAlert(const CryptoVault& vault, const std::string& alert_msg) {
    std::string status = vault.is_unlocked ? "UNLOCKED" : "LOCKED";
    return "[ALERT][" + alert_msg + "] Status: " + status + " | Failed: " + std::to_string(vault.failed_attempts);
}
