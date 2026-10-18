import unittest
from test_harness import run_solution_view, DEFAULT_SAMPLE_DATA

class TestOperatorExpressions(unittest.TestCase):
    def setUp(self):
        self.sql_file = "solution.sql"

    def test_active_high_clearance_default_dataset(self):
        columns, rows = run_solution_view(self.sql_file, "v_active_high_clearance", DEFAULT_SAMPLE_DATA)
        col_indices = {c.lower(): i for i, c in enumerate(columns)}
        
        self.assertEqual(len(rows), 5, f"Expected 5 active high clearance users, got {len(rows)}")
        user_ids = [r[col_indices["user_id"]] for r in rows]
        self.assertEqual(user_ids, [1, 2, 3, 7, 9], f"Incorrect user_ids or ordering: {user_ids}")
        
        # Verify columns & values
        for r in rows:
            self.assertGreaterEqual(r[col_indices["clearance_level"]], 3)

    def test_privileged_department_access_default_dataset(self):
        columns, rows = run_solution_view(self.sql_file, "v_privileged_department_access", DEFAULT_SAMPLE_DATA)
        col_indices = {c.lower(): i for i, c in enumerate(columns)}
        
        self.assertEqual(len(rows), 4, f"Expected 4 privileged department users, got {len(rows)}")
        user_ids = [r[col_indices["user_id"]] for r in rows]
        self.assertEqual(user_ids, [2, 3, 5, 10], f"Incorrect user_ids returned: {user_ids}")

        # Check explicit clearance DESC, user_id ASC ordering
        clearance_levels = [r[col_indices["clearance_level"]] for r in rows]
        self.assertEqual(clearance_levels, [4, 3, 3, 1], f"Incorrect clearance ordering: {clearance_levels}")

    def test_all_blocked_users_edge_case(self):
        blocked_dataset = [
            (101, 'user1', 'SECURITY', 'Security', 5, 1, 1, 1),
            (102, 'user2', 'DEVELOPER', 'Engineering', 4, 1, 1, 1)
        ]
        _, rows1 = run_solution_view(self.sql_file, "v_active_high_clearance", blocked_dataset)
        _, rows2 = run_solution_view(self.sql_file, "v_privileged_department_access", blocked_dataset)
        
        self.assertEqual(len(rows1), 0, "Blocked users must not appear in v_active_high_clearance")
        self.assertEqual(len(rows2), 0, "Blocked users must not appear in v_privileged_department_access")

    def test_custom_operator_filtering(self):
        custom_dataset = [
            (201, 'sec_staff', 'SECURITY', 'Security', 5, 1, 0, 1), # Task 1: Yes, Task 2: Yes
            (202, 'eng_noip', 'DEVELOPER', 'Engineering', 4, 1, 0, 0), # Task 1: Yes, Task 2: No (ip=0)
            (203, 'hr_high', 'ANALYST', 'HR', 4, 1, 0, 1), # Task 1: Yes, Task 2: No (dept=HR)
            (204, 'sec_low', 'SECURITY', 'Security', 2, 1, 0, 1), # Task 1: No (clearance 2<3), Task 2: Yes
            (205, 'eng_blocked', 'DEVELOPER', 'Engineering', 5, 1, 1, 1) # Task 1: No, Task 2: No
        ]
        columns1, rows1 = run_solution_view(self.sql_file, "v_active_high_clearance", custom_dataset)
        col_map1 = {c.lower(): i for i, c in enumerate(columns1)}
        uids1 = [r[col_map1["user_id"]] for r in rows1]
        self.assertEqual(uids1, [201, 202, 203])

        columns2, rows2 = run_solution_view(self.sql_file, "v_privileged_department_access", custom_dataset)
        col_map2 = {c.lower(): i for i, c in enumerate(columns2)}
        uids2 = [r[col_map2["user_id"]] for r in rows2]
        self.assertEqual(uids2, [201, 204])

if __name__ == "__main__":
    unittest.main()
