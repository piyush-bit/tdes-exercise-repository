-- CS2004 Lab 07: Security Access Control List (ACL) Filter Engine
-- Reference Solution

-- Task 1: Active High-Clearance Users View
DROP VIEW IF EXISTS v_active_high_clearance;
CREATE VIEW v_active_high_clearance AS
SELECT user_id, username, role, department, clearance_level
FROM security_acls
WHERE is_blocked = 0
  AND mfa_enabled = 1
  AND clearance_level >= 3
ORDER BY user_id ASC;

-- Task 2: Privileged Department Access View
DROP VIEW IF EXISTS v_privileged_department_access;
CREATE VIEW v_privileged_department_access AS
SELECT user_id, username, role, department, clearance_level, ip_whitelisted
FROM security_acls
WHERE (department = 'Security' OR department = 'Engineering')
  AND ip_whitelisted = 1
  AND is_blocked = 0
ORDER BY clearance_level DESC, user_id ASC;

-- Task 3: Restricted Audit Exceptions View
DROP VIEW IF EXISTS v_restricted_audit_exceptions;
CREATE VIEW v_restricted_audit_exceptions AS
SELECT user_id, username, role, department, mfa_enabled, ip_whitelisted
FROM security_acls
WHERE is_blocked = 0
  AND NOT role = 'GUEST'
  AND clearance_level >= 2
  AND (mfa_enabled = 0 OR ip_whitelisted = 0)
ORDER BY user_id ASC;

-- Task 4: Critical System Grants View
DROP VIEW IF EXISTS v_critical_system_grants;
CREATE VIEW v_critical_system_grants AS
SELECT user_id, username, role, department, clearance_level
FROM security_acls
WHERE (role = 'ADMIN' AND mfa_enabled = 1 AND is_blocked = 0)
   OR (role = 'SECURITY' AND clearance_level >= 4 AND NOT (is_blocked = 1 OR mfa_enabled = 0))
   OR (department = 'IT' AND ip_whitelisted = 1 AND clearance_level >= 3 AND NOT is_blocked = 1)
ORDER BY user_id ASC;
