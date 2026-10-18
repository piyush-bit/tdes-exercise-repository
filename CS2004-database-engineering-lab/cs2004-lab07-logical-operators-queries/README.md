# CS2004 Lab 07: Security Access Control List (ACL) Filter Engine

## Overview

In modern cybersecurity architectures, Access Control Lists (ACLs) determine system entry by evaluating multi-layered policy rules against incoming user session metadata. In SQL, policy engines rely heavily on combining logical operators—`AND`, `OR`, and `NOT`—along with parenthetical grouping `()` to govern precedence.

In this lab, you will author SQL queries to build four security filter views on an organization's central access control database table.

---

## Database Schema

All queries operate on a single table named `security_acls`:

```sql
CREATE TABLE security_acls (
    user_id INTEGER PRIMARY KEY,
    username TEXT NOT NULL,
    role TEXT NOT NULL,
    department TEXT NOT NULL,
    clearance_level INTEGER NOT NULL,
    mfa_enabled INTEGER NOT NULL,
    is_blocked INTEGER NOT NULL,
    ip_whitelisted INTEGER NOT NULL
);
```

### Column Descriptions

- `user_id`: Unique integer ID for each account.
- `username`: Account identifier (e.g. `'alice_sec'`, `'bob_dev'`).
- `role`: System role (`'ADMIN'`, `'SECURITY'`, `'DEVELOPER'`, `'ANALYST'`, `'GUEST'`, `'AUDITOR'`).
- `department`: Organizational department (`'Engineering'`, `'Security'`, `'Finance'`, `'HR'`, `'IT'`).
- `clearance_level`: Integer security clearance rating from 1 (lowest) to 5 (highest).
- `mfa_enabled`: Multi-Factor Authentication status (`1` = enabled, `0` = disabled).
- `is_blocked`: Account lockout status (`1` = blocked, `0` = active).
- `ip_whitelisted`: IP address verification status (`1` = whitelisted, `0` = non-whitelisted).

---

## Tasks & Specifications

Write all SQL statements inside `solution.sql`. You must create four SQL views using `CREATE VIEW`:

### Task 1: Active High-Clearance Users View (`v_active_high_clearance`)

Create a view named `v_active_high_clearance` that identifies all active, non-blocked accounts that have multi-factor authentication enabled and hold a security clearance level of 3 or higher.

- **Logical Rules:**
  - Account is NOT blocked (`is_blocked = 0`)
  - MFA is enabled (`mfa_enabled = 1`)
  - Clearance level is at least 3 (`clearance_level >= 3`)
- **Required Columns:** `user_id`, `username`, `role`, `department`, `clearance_level`
- **Ordering:** `ORDER BY user_id ASC`

---

### Task 2: Privileged Department Access View (`v_privileged_department_access`)

Create a view named `v_privileged_department_access` that lists active personnel in core security or engineering units operating from whitelisted network locations.

- **Logical Rules:**
  - Department is either `'Security'` OR `'Engineering'`
  - IP address is whitelisted (`ip_whitelisted = 1`)
  - Account is NOT blocked (`is_blocked = 0`)
- **Required Columns:** `user_id`, `username`, `role`, `department`, `clearance_level`, `ip_whitelisted`
- **Ordering:** `ORDER BY clearance_level DESC, user_id ASC`

---

### Task 3: Restricted Audit Exceptions View (`v_restricted_audit_exceptions`)

Create a view named `v_restricted_audit_exceptions` that flags active non-guest users with elevated access (clearance level >= 2) who present potential security gaps (missing MFA or un-whitelisted IP).

- **Logical Rules:**
  - Account is NOT blocked (`is_blocked = 0`)
  - Role is NOT `'GUEST'` (`NOT role = 'GUEST'`)
  - Clearance level is at least 2 (`clearance_level >= 2`)
  - EITHER MFA is disabled (`mfa_enabled = 0`) OR IP is NOT whitelisted (`ip_whitelisted = 0`)
- **Required Columns:** `user_id`, `username`, `role`, `department`, `mfa_enabled`, `ip_whitelisted`
- **Ordering:** `ORDER BY user_id ASC`

---

### Task 4: Critical System Grants View (`v_critical_system_grants`)

Create a view named `v_critical_system_grants` that implements an enterprise emergency and root access matrix. An account is granted critical system access if it satisfies **ANY** of the following three policy rules:

- **Policy Rule A (Active Admin):**
  `role = 'ADMIN'` AND `mfa_enabled = 1` AND `is_blocked = 0`

- **Policy Rule B (Senior Security Specialist Compliance):**
  `role = 'SECURITY'` AND `clearance_level >= 4` AND NOT (`is_blocked = 1` OR `mfa_enabled = 0`)

- **Policy Rule C (Trusted IT Operations):**
  `department = 'IT'` AND `ip_whitelisted = 1` AND `clearance_level >= 3` AND NOT `is_blocked = 1`

- **Required Columns:** `user_id`, `username`, `role`, `department`, `clearance_level`
- **Ordering:** `ORDER BY user_id ASC`

---

## Local Verification

Run the public test suite to test your live solution in `solution.sql`:

```bash
make test-public
# or using the run wrapper:
./run
```

To run all private grading targets locally (requires reference solution in `reference/solution.sql`):

```bash
make test-submission-operator-expressions
make test-submission-complex-boolean
```
