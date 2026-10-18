import unittest
from test_harness import run_sql_query, is_close, DEFAULT_SAMPLE_DATA

class TestPublicPayroll(unittest.TestCase):
    def setUp(self):
        self.sql_file = "solution.sql"

    def test_output_columns_exist(self):
        columns, _ = run_sql_query(self.sql_file)
        lower_cols = [c.lower() for c in columns]
        
        self.assertIn("employee_id", lower_cols, "Missing column 'employee_id'")
        self.assertIn("gross_salary", lower_cols, "Missing column 'gross_salary'")
        self.assertIn("tax_deduction", lower_cols, "Missing computed column 'tax_deduction'")
        self.assertIn("net_salary", lower_cols, "Missing computed column 'net_salary'")

    def test_payroll_calculations_public_dataset(self):
        columns, rows = run_sql_query(self.sql_file, DEFAULT_SAMPLE_DATA)
        self.assertEqual(len(rows), len(DEFAULT_SAMPLE_DATA), f"Expected {len(DEFAULT_SAMPLE_DATA)} rows, got {len(rows)}")
        
        col_indices = {c.lower(): i for i, c in enumerate(columns)}
        
        for row in rows:
            emp_id = row[col_indices["employee_id"]]
            gross_sal = row[col_indices["gross_salary"]]
            tax = row[col_indices["tax"]]
            bonus = row[col_indices["bonus"]]
            tax_deduction = row[col_indices["tax_deduction"]]
            net_salary = row[col_indices["net_salary"]]
            
            expected_tax_deduction = gross_sal * 0.20
            expected_net_salary = gross_sal - tax + bonus
            
            self.assertTrue(
                is_close(tax_deduction, expected_tax_deduction),
                f"Emp {emp_id}: Expected tax_deduction {expected_tax_deduction}, got {tax_deduction}"
            )
            self.assertTrue(
                is_close(net_salary, expected_net_salary),
                f"Emp {emp_id}: Expected net_salary {expected_net_salary}, got {net_salary}"
            )

if __name__ == "__main__":
    unittest.main()
