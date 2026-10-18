import unittest
from test_harness import run_sql_query, is_close

class TestArithmeticCalculations(unittest.TestCase):
    def setUp(self):
        self.sql_file = "solution.sql"

    def test_tax_deduction_arithmetic_custom_dataset(self):
        dataset = [
            (201, 'Emp One', 'IT', 100000.00, 20000.00, 10000.00),
            (202, 'Emp Two', 'HR', 55555.55, 5000.00, 2500.00),
            (203, 'Emp Three', 'Sales', 77777.77, 12000.00, 0.00),
        ]
        columns, rows = run_sql_query(self.sql_file, dataset)
        col_map = {c.lower(): i for i, c in enumerate(columns)}
        
        for row in rows:
            gross = row[col_map["gross_salary"]]
            actual_tax_deduction = row[col_map["tax_deduction"]]
            expected_tax_deduction = gross * 0.20
            self.assertTrue(
                is_close(actual_tax_deduction, expected_tax_deduction),
                f"Tax deduction incorrect for gross {gross}: expected {expected_tax_deduction}, got {actual_tax_deduction}"
            )

    def test_net_salary_arithmetic_custom_dataset(self):
        dataset = [
            (301, 'User A', 'DevOps', 90000.00, 15000.00, 8000.00),
            (302, 'User B', 'QA', 45000.25, 4500.00, 1500.50),
            (303, 'User C', 'Design', 120000.00, 30000.00, 15000.00),
        ]
        columns, rows = run_sql_query(self.sql_file, dataset)
        col_map = {c.lower(): i for i, c in enumerate(columns)}
        
        for row in rows:
            gross = row[col_map["gross_salary"]]
            tax = row[col_map["tax"]]
            bonus = row[col_map["bonus"]]
            actual_net = row[col_map["net_salary"]]
            expected_net = gross - tax + bonus
            self.assertTrue(
                is_close(actual_net, expected_net),
                f"Net salary incorrect: gross={gross}, tax={tax}, bonus={bonus}: expected {expected_net}, got {actual_net}"
            )

    def test_floating_point_precision_and_zero_values(self):
        dataset = [
            (401, 'Zero Bonus', 'Legal', 80000.00, 10000.00, 0.00),
            (402, 'Zero Tax', 'Support', 30000.00, 0.00, 2000.00),
            (403, 'Decimal Precision', 'R&D', 123456.789, 23456.78, 9876.54),
        ]
        columns, rows = run_sql_query(self.sql_file, dataset)
        col_map = {c.lower(): i for i, c in enumerate(columns)}
        
        for row in rows:
            gross = row[col_map["gross_salary"]]
            tax = row[col_map["tax"]]
            bonus = row[col_map["bonus"]]
            tax_deduction = row[col_map["tax_deduction"]]
            net_salary = row[col_map["net_salary"]]
            
            self.assertTrue(is_close(tax_deduction, gross * 0.20))
            self.assertTrue(is_close(net_salary, gross - tax + bonus))

if __name__ == "__main__":
    unittest.main()
