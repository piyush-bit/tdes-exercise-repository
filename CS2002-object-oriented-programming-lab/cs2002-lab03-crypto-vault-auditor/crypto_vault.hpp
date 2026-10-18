#ifndef CRYPTO_VAULT_HPP
#define CRYPTO_VAULT_HPP

#include <string>

// Forward declaration of AuditInspector
class AuditInspector;

class CryptoVault {
private:
    int master_pin;
    std::string secret_token;
    std::string token_signature;
    std::string secret_data;
    bool is_unlocked;
    int failed_attempts;
    int audit_access_count;

    // Friend class and friend function declarations
    friend class AuditInspector;
    friend std::string logSecurityAlert(const CryptoVault& vault, const std::string& alert_msg);

public:
    CryptoVault(int pin, const std::string& token, const std::string& signature, const std::string& secret);

    // Overloaded authenticate methods
    bool authenticate(int pin);
    bool authenticate(const std::string& token, const std::string& signature);

    void lock();
    bool isUnlocked() const;
    int getFailedAttempts() const;
    int getAuditAccessCount() const;
    std::string getSecretData() const;
};

class AuditInspector {
public:
    AuditInspector() = default;

    // Inspects vault keys, increments vault.audit_access_count
    std::string inspectVaultKey(CryptoVault& vault) const;

    // Force bypass lock with master override key, increments vault.audit_access_count
    bool forceBypassLock(CryptoVault& vault, const std::string& master_override_key);

    // Queries failed attempts via friend privileges, increments vault.audit_access_count
    int getVaultFailedAttempts(CryptoVault& vault) const;
};

// Friend function to log security alerts
std::string logSecurityAlert(const CryptoVault& vault, const std::string& alert_msg);

#endif // CRYPTO_VAULT_HPP
