import unittest
from test_harness import run_solution_view, DEFAULT_SAMPLE_DATA

class TestComplexBoolean(unittest.TestCase):
    def setUp(self):
        self.sql_file = "solution.sql"

    def test_restricted_audit_exceptions_default_dataset(self):
        columns, rows = run_solution_view(self.sql_file, "v_restricted_audit_exceptions", DEFAULT_SAMPLE_DATA)
        col_indices = {c.lower(): i for i, c in enumerate(columns)}
        
        self.assertEqual(len(rows), 3, f"Expected 3 restricted audit exceptions, got {len(rows)}")
        user_ids = [r[col_indices["user_id"]] for r in rows]
        self.assertEqual(user_ids, [5, 8, 9], f"Incorrect audit exception user_ids: {user_ids}")
        
        # Verify no GUEST role or blocked users present
        for r in rows:
            self.assertNotEqual(r[col_indices["role"]], "GUEST")

    def test_critical_system_grants_default_dataset(self):
        columns, rows = run_solution_view(self.sql_file, "v_critical_system_grants", DEFAULT_SAMPLE_DATA)
        col_indices = {c.lower(): i for i, c in enumerate(columns)}
        
        self.assertEqual(len(rows), 3, f"Expected 3 critical system grants, got {len(rows)}")
        user_ids = [r[col_indices["user_id"]] for r in rows]
        self.assertEqual(user_ids, [1, 2, 7], f"Incorrect critical system grant user_ids: {user_ids}")

    def test_policy_rule_isolation(self):
        rule_dataset = [
            # Rule A match only: ADMIN, mfa=1, blocked=0
            (301, 'admin_rule_a', 'ADMIN', 'HR', 1, 1, 0, 0),
            # Rule A fail: ADMIN, mfa=0, blocked=0
            (302, 'admin_nomfa', 'ADMIN', 'HR', 1, 0, 0, 0),
            # Rule B match only: SECURITY, clearance=4, NOT(blocked=1 OR mfa=0) => blocked=0, mfa=1
            (303, 'sec_rule_b', 'SECURITY', 'Security', 4, 1, 0, 0),
            # Rule B fail: SECURITY, clearance=4, mfa=0
            (304, 'sec_nomfa', 'SECURITY', 'Security', 4, 0, 0, 0),
            # Rule C match only: IT, ip=1, clearance=3, blocked=0
            (305, 'it_rule_c', 'ANALYST', 'IT', 3, 0, 0, 1),
            # Rule C fail: IT, ip=1, clearance=2, blocked=0
            (306, 'it_low_clearance', 'ANALYST', 'IT', 2, 0, 0, 1)
        ]

        columns, rows = run_solution_view(self.sql_file, "v_critical_system_grants", rule_dataset)
        col_indices = {c.lower(): i for i, c in enumerate(columns)}
        user_ids = [r[col_indices["user_id"]] for r in rows]
        
        self.assertEqual(user_ids, [301, 303, 305], f"Policy rule isolation failed. Expected [301, 303, 305], got {user_ids}")

    def test_audit_exceptions_parentheses_precedence(self):
        precedence_dataset = [
            # Guest with missing MFA & clearance 5 -> excluded because NOT role = 'GUEST'
            (401, 'guest_user', 'GUEST', 'HR', 5, 0, 0, 0),
            # Non-guest, clearance 2, mfa=1, ip=1 -> excluded because neither mfa=0 nor ip=0
            (402, 'compliant_user', 'ANALYST', 'Finance', 2, 1, 0, 1),
            # Non-guest, clearance 1, mfa=0, ip=0 -> excluded because clearance < 2
            (403, 'low_clearance_user', 'ANALYST', 'Finance', 1, 0, 0, 0),
            # Non-guest, clearance 2, mfa=1, ip=0 -> included
            (404, 'audit_target_1', 'ANALYST', 'Finance', 2, 1, 0, 0),
            # Non-guest, clearance 3, mfa=0, ip=1 -> included
            (405, 'audit_target_2', 'DEVELOPER', 'Engineering', 3, 0, 0, 1)
        ]

        columns, rows = run_solution_view(self.sql_file, "v_restricted_audit_exceptions", precedence_dataset)
        col_indices = {c.lower(): i for i, c in enumerate(columns)}
        user_ids = [r[col_indices["user_id"]] for r in rows]

        self.assertEqual(user_ids, [404, 405], f"Audit precedence check failed. Expected [404, 405], got {user_ids}")

if __name__ == "__main__":
    unittest.main()
