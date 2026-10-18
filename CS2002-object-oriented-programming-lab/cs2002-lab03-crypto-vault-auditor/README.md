# CS2002 Lab 03: Encrypted Security Vault & Friend Audit Inspector

## Overview & Objectives

In modern C++ software design, encapsulation protects internal component state from unauthorized external modification. However, certain security architecture patterns require multi-layered authentication interfaces (achieved via **Function Overloading**) as well as controlled privilege delegation to trusted external auditors and loggers (achieved via **Friend Classes** and **Friend Functions**).

In this lab, you will complete the implementation of:
1. **`CryptoVault`**: A security vault supporting two distinct authentication mechanisms (PIN vs. Token/Signature pair) using C++ function overloading.
2. **`AuditInspector`**: A trusted auditor class declared as a `friend class` inside `CryptoVault`, granting it direct access to private credentials and state counters.
3. **`logSecurityAlert`**: A standalone `friend function` that inspects private vault status and constructs formatted security diagnostic alerts.

---

## Technical Specifications

### 1. `CryptoVault` Class (`crypto_vault.hpp` / `crypto_vault.cpp`)

#### Attributes (Private):
- `int master_pin`: The numeric PIN required for basic authentication.
- `std::string secret_token`: Security token string for multi-factor authentication.
- `std::string token_signature`: Secret cryptographic signature corresponding to the security token.
- `std::string secret_data`: Encrypted data payload stored inside the vault.
- `bool is_unlocked`: Indicates whether the vault is currently unlocked (default `false`).
- `int failed_attempts`: Counter tracking consecutive failed authentication attempts (default `0`).
- `int audit_access_count`: Counter tracking total audit/inspection accesses (default `0`).

#### Member Functions (Public):
- **`CryptoVault(int pin, const std::string& token, const std::string& signature, const std::string& secret)`**:
  Constructs vault object, initializing `master_pin`, `secret_token`, `token_signature`, and `secret_data`. Sets `is_unlocked = false`, `failed_attempts = 0`, and `audit_access_count = 0`.
- **`bool authenticate(int pin)`**:
  Attempts PIN authentication.
  - If `pin == master_pin`: sets `is_unlocked = true`, resets `failed_attempts = 0`, returns `true`.
  - Otherwise: increments `failed_attempts`, sets `is_unlocked = false`, returns `false`.
- **`bool authenticate(const std::string& token, const std::string& signature)`**:
  Overloaded authentication method using token and signature strings.
  - If `token == secret_token` AND `signature == token_signature`: sets `is_unlocked = true`, resets `failed_attempts = 0`, returns `true`.
  - Otherwise: increments `failed_attempts`, sets `is_unlocked = false`, returns `false`.
- **`void lock()`**:
  Sets `is_unlocked = false`.
- **`bool isUnlocked() const`**:
  Returns current `is_unlocked` state.
- **`int getFailedAttempts() const`**:
  Returns `failed_attempts`.
- **`int getAuditAccessCount() const`**:
  Returns `audit_access_count`.
- **`std::string getSecretData() const`**:
  Returns `secret_data` if `is_unlocked` is `true`; otherwise returns `"LOCKED: ACCESS DENIED"`.

---

### 2. `AuditInspector` Class (`crypto_vault.hpp` / `crypto_vault.cpp`)

Declared as a `friend class` inside `CryptoVault`.

#### Member Functions (Public):
- **`std::string inspectVaultKey(CryptoVault& vault) const`**:
  Increments `vault.audit_access_count`.
  Returns string formatted as: `"AUDIT_KEY:[PIN=<master_pin>|TOKEN=<secret_token>]"`.
- **`bool forceBypassLock(CryptoVault& vault, const std::string& master_override_key)`**:
  Increments `vault.audit_access_count`.
  If `master_override_key == "OVERRIDE_MASTER_999"`: sets `vault.is_unlocked = true`, resets `vault.failed_attempts = 0`, returns `true`.
  Otherwise returns `false`.
- **`int getVaultFailedAttempts(CryptoVault& vault) const`**:
  Increments `vault.audit_access_count`.
  Returns `vault.failed_attempts`.

---

### 3. Friend Function `logSecurityAlert` (`crypto_vault.hpp` / `crypto_vault.cpp`)

Declared as a friend function inside `CryptoVault`:
- **`std::string logSecurityAlert(const CryptoVault& vault, const std::string& alert_msg)`**:
  Inspects private members `vault.is_unlocked` and `vault.failed_attempts`.
  Returns string formatted as: `"[ALERT][<alert_msg>] Status: <UNLOCKED|LOCKED> | Failed: <failed_attempts>"`.

---

## Building and Testing Locally

To compile and run public unit tests:
```bash
make test-public
```
or use the helper script:
```bash
./run public
```

To clean build artifacts:
```bash
make clean
```
