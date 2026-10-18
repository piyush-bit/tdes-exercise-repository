import unittest
import os
import sys

# Add parent directory to path to import test_harness
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from test_harness import create_database, execute_task_query, DEFAULT_RECORDS

SQL_FILE = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "solution.sql"))


class TestComparisonFiltering(unittest.TestCase):

    def setUp(self):
        self.conn_default = create_database(DEFAULT_RECORDS)

        # Custom boundary dataset to test exact boundary conditions for comparison operators
        self.boundary_records = [
            (201, 'Border', 'Alpha', 65, 'M', 1, 'Triage Level 1 Test', 100, 120, 95, 35.5, 'AMB'),
            (202, 'Border', 'Beta', 64, 'F', 2, 'Tachycardia Test', 101, 130, 94, 35.6, 'WALK'),
            (203, 'Border', 'Gamma', 66, 'M', 5, 'Hypoxia Test', 99, 110, 94, 35.4, 'XFER'),
            (204, 'Border', 'Delta', 18, 'F', 1, 'Cold Temp Test', 150, 90, 98, 35.5, 'AMB')
        ]
        self.conn_boundary = create_database(self.boundary_records)

    def tearDown(self):
        self.conn_default.close()
        self.conn_boundary.close()

    def test_task1_equal_operator_default(self):
        expected = [
            (101, 'Alice', 'Smith', 1, 'Severe Chest Pain'),
            (105, 'Evan', 'Wright', 1, 'Cardiac Arrest'),
            (111, 'Kevin', 'Bacon', 1, 'Unresponsive')
        ]
        results = execute_task_query(SQL_FILE, 1, self.conn_default)
        self.assertEqual(results, expected, "Task 1 standard dataset failed")

    def test_task1_equal_operator_boundary(self):
        expected = [
            (201, 'Border', 'Alpha', 1, 'Triage Level 1 Test'),
            (204, 'Border', 'Delta', 1, 'Cold Temp Test')
        ]
        results = execute_task_query(SQL_FILE, 1, self.conn_boundary)
        self.assertEqual(results, expected, "Task 1 boundary dataset failed")

    def test_task2_greater_than_default(self):
        expected = [
            (105, 140, 85),
            (101, 115, 145),
            (115, 112, 115),
            (113, 108, 138),
            (103, 105, 110),
            (107, 102, 160)
        ]
        results = execute_task_query(SQL_FILE, 2, self.conn_default)
        self.assertEqual(results, expected, "Task 2 standard dataset failed")

    def test_task2_greater_than_boundary(self):
        # 100 bpm should be excluded, only > 100 should be present (101, 150)
        expected = [
            (204, 150, 90),
            (202, 101, 130)
        ]
        results = execute_task_query(SQL_FILE, 2, self.conn_boundary)
        self.assertEqual(results, expected, "Task 2 boundary strict greater-than failed")

    def test_task3_less_than_default(self):
        expected = [
            (111, 'Kevin', 'Bacon', 85),
            (105, 'Evan', 'Wright', 88),
            (101, 'Alice', 'Smith', 92),
            (110, 'Julia', 'Roberts', 93),
            (102, 'Bob', 'Jones', 94),
            (115, 'Oscar', 'Isaac', 94)
        ]
        results = execute_task_query(SQL_FILE, 3, self.conn_default)
        self.assertEqual(results, expected, "Task 3 standard dataset failed")

    def test_task3_less_than_boundary(self):
        # 95 oxygen stat should be excluded, only < 95 (94, 94)
        expected = [
            (202, 'Border', 'Beta', 94),
            (203, 'Border', 'Gamma', 94)
        ]
        results = execute_task_query(SQL_FILE, 3, self.conn_boundary)
        self.assertEqual(results, expected, "Task 3 boundary strict less-than failed")

    def test_task4_greater_equal_default(self):
        expected = [
            (111, 'Kevin', 'Bacon', 82),
            (105, 'Evan', 'Wright', 75),
            (114, 'Nora', 'Jones', 70),
            (102, 'Bob', 'Jones', 68),
            (107, 'George', 'Clark', 65)
        ]
        results = execute_task_query(SQL_FILE, 4, self.conn_default)
        self.assertEqual(results, expected, "Task 4 standard dataset failed")

    def test_task4_greater_equal_boundary(self):
        # age 65 and 66 included, 64 excluded
        expected = [
            (203, 'Border', 'Gamma', 66),
            (201, 'Border', 'Alpha', 65)
        ]
        results = execute_task_query(SQL_FILE, 4, self.conn_boundary)
        self.assertEqual(results, expected, "Task 4 boundary greater-than-or-equal failed")

    def test_task5_less_equal_default(self):
        expected = [
            (111, 34.9, 'Unresponsive'),
            (105, 35.2, 'Cardiac Arrest')
        ]
        results = execute_task_query(SQL_FILE, 5, self.conn_default)
        self.assertEqual(results, expected, "Task 5 standard dataset failed")

    def test_task5_less_equal_boundary(self):
        # 35.4 and 35.5 included, 35.6 excluded
        expected = [
            (203, 35.4, 'Hypoxia Test'),
            (201, 35.5, 'Triage Level 1 Test'),
            (204, 35.5, 'Cold Temp Test')
        ]
        results = execute_task_query(SQL_FILE, 5, self.conn_boundary)
        self.assertEqual(results, expected, "Task 5 boundary less-than-or-equal failed")


if __name__ == "__main__":
    unittest.main()
