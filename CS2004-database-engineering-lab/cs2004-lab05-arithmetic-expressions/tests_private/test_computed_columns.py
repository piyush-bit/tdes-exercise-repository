import unittest
from test_harness import run_sql_query

class TestComputedColumns(unittest.TestCase):
    def setUp(self):
        self.sql_file = "solution.sql"

    def test_exact_computed_column_aliases(self):
        columns, _ = run_sql_query(self.sql_file)
        cols_lower = [c.lower() for c in columns]
        
        self.assertIn("tax_deduction", cols_lower, "Column alias 'tax_deduction' must be present in output.")
        self.assertIn("net_salary", cols_lower, "Column alias 'net_salary' must be present in output.")

    def test_all_schema_columns_present(self):
        columns, _ = run_sql_query(self.sql_file)
        cols_lower = [c.lower() for c in columns]
        expected_columns = [
            "employee_id", "employee_name", "department",
            "gross_salary", "tax", "bonus", "tax_deduction", "net_salary"
        ]
        for expected in expected_columns:
            self.assertIn(expected, cols_lower, f"Required column '{expected}' is missing from SELECT query output.")

    def test_computed_columns_row_count_and_ordering(self):
        dataset = [
            (10, 'Alpha', 'Exec', 200000.0, 40000.0, 50000.0),
            (20, 'Beta', 'Ops', 60000.0, 10000.0, 5000.0),
            (30, 'Gamma', 'Eng', 110000.0, 20000.0, 15000.0),
        ]
        columns, rows = run_sql_query(self.sql_file, dataset)
        self.assertEqual(len(rows), 3, "Query output row count must match input table row count.")
        
        col_map = {c.lower(): i for i, c in enumerate(columns)}
        emp_ids = [row[col_map["employee_id"]] for row in rows]
        self.assertEqual(emp_ids, sorted(emp_ids), "Output rows should be ordered deterministically by employee_id.")

if __name__ == "__main__":
    unittest.main()
