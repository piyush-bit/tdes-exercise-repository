import unittest
from test_harness import run_solution_view, DEFAULT_SAMPLE_DATA

class TestPublicSecurityACL(unittest.TestCase):
    def setUp(self):
        self.sql_file = "solution.sql"

    def test_view_1_active_high_clearance_columns(self):
        columns, _ = run_solution_view(self.sql_file, "v_active_high_clearance")
        lower_cols = [c.lower() for c in columns]
        expected_cols = ["user_id", "username", "role", "department", "clearance_level"]
        for col in expected_cols:
            self.assertIn(col, lower_cols, f"v_active_high_clearance missing column '{col}'")

    def test_view_2_privileged_department_access_columns(self):
        columns, _ = run_solution_view(self.sql_file, "v_privileged_department_access")
        lower_cols = [c.lower() for c in columns]
        expected_cols = ["user_id", "username", "role", "department", "clearance_level", "ip_whitelisted"]
        for col in expected_cols:
            self.assertIn(col, lower_cols, f"v_privileged_department_access missing column '{col}'")

    def test_view_3_restricted_audit_exceptions_columns(self):
        columns, _ = run_solution_view(self.sql_file, "v_restricted_audit_exceptions")
        lower_cols = [c.lower() for c in columns]
        expected_cols = ["user_id", "username", "role", "department", "mfa_enabled", "ip_whitelisted"]
        for col in expected_cols:
            self.assertIn(col, lower_cols, f"v_restricted_audit_exceptions missing column '{col}'")

    def test_view_4_critical_system_grants_columns(self):
        columns, _ = run_solution_view(self.sql_file, "v_critical_system_grants")
        lower_cols = [c.lower() for c in columns]
        expected_cols = ["user_id", "username", "role", "department", "clearance_level"]
        for col in expected_cols:
            self.assertIn(col, lower_cols, f"v_critical_system_grants missing column '{col}'")

    def test_public_dataset_sample_results(self):
        _, rows1 = run_solution_view(self.sql_file, "v_active_high_clearance", DEFAULT_SAMPLE_DATA)
        _, rows2 = run_solution_view(self.sql_file, "v_privileged_department_access", DEFAULT_SAMPLE_DATA)
        _, rows3 = run_solution_view(self.sql_file, "v_restricted_audit_exceptions", DEFAULT_SAMPLE_DATA)
        _, rows4 = run_solution_view(self.sql_file, "v_critical_system_grants", DEFAULT_SAMPLE_DATA)

        self.assertEqual(len(rows1), 5, f"v_active_high_clearance expected 5 rows on public dataset, got {len(rows1)}")
        self.assertEqual(len(rows2), 4, f"v_privileged_department_access expected 4 rows on public dataset, got {len(rows2)}")
        self.assertEqual(len(rows3), 3, f"v_restricted_audit_exceptions expected 3 rows on public dataset, got {len(rows3)}")
        self.assertEqual(len(rows4), 3, f"v_critical_system_grants expected 3 rows on public dataset, got {len(rows4)}")

if __name__ == "__main__":
    unittest.main()
