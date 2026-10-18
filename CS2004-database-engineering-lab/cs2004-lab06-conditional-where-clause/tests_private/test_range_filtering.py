import unittest
import os
import sys

# Add parent directory to path to import test_harness
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from test_harness import create_database, execute_task_query, DEFAULT_RECORDS

SQL_FILE = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "solution.sql"))


class TestRangeFiltering(unittest.TestCase):

    def setUp(self):
        self.conn_default = create_database(DEFAULT_RECORDS)

        # Custom dataset to test BETWEEN bounds (120 & 139 inclusive), IN set membership, and combined conditions
        self.range_records = [
            (301, 'Range', 'One', 5, 'M', 1, 'Child Low HR Bound', 80, 119, 98, 36.8, 'AMB'),
            (302, 'Range', 'Two', 12, 'F', 2, 'Child High HR Bound', 110, 120, 97, 36.9, 'XFER'),
            (303, 'Range', 'Three', 17, 'M', 3, 'Child HR Out of Range', 79, 139, 96, 37.0, 'WALK'),
            (304, 'Range', 'Four', 18, 'F', 4, 'Adult Age Out of Set', 90, 140, 99, 36.5, 'AMB')
        ]
        self.conn_range = create_database(self.range_records)

    def tearDown(self):
        self.conn_default.close()
        self.conn_range.close()

    def test_task6_between_range_default(self):
        expected = [
            (109, 'Ian', 'Malcolm', 120),
            (112, 'Laura', 'Croft', 122),
            (106, 'Fiona', 'Gallagher', 125),
            (102, 'Bob', 'Jones', 130),
            (113, 'Michael', 'Scott', 138)
        ]
        results = execute_task_query(SQL_FILE, 6, self.conn_default)
        self.assertEqual(results, expected, "Task 6 standard dataset failed")

    def test_task6_between_range_boundary(self):
        # 119 excluded, 120 included, 139 included, 140 excluded
        expected = [
            (302, 'Range', 'Two', 120),
            (303, 'Range', 'Three', 139)
        ]
        results = execute_task_query(SQL_FILE, 6, self.conn_range)
        self.assertEqual(results, expected, "Task 6 inclusive BETWEEN bounds failed")

    def test_task7_in_set_default(self):
        expected = [
            (101, 'Alice', 'Smith', 'AMB', 1),
            (105, 'Evan', 'Wright', 'AMB', 1),
            (111, 'Kevin', 'Bacon', 'AMB', 1),
            (107, 'George', 'Clark', 'AMB', 2),
            (110, 'Julia', 'Roberts', 'AMB', 2),
            (114, 'Nora', 'Jones', 'XFER', 2),
            (106, 'Fiona', 'Gallagher', 'XFER', 3)
        ]
        results = execute_task_query(SQL_FILE, 7, self.conn_default)
        self.assertEqual(results, expected, "Task 7 standard dataset failed")

    def test_task7_in_set_boundary(self):
        # 301 AMB (triage 1), 302 XFER (triage 2), 304 AMB (triage 4), 303 WALK excluded
        expected = [
            (301, 'Range', 'One', 'AMB', 1),
            (302, 'Range', 'Two', 'XFER', 2),
            (304, 'Range', 'Four', 'AMB', 4)
        ]
        results = execute_task_query(SQL_FILE, 7, self.conn_range)
        self.assertEqual(results, expected, "Task 7 IN set membership failed")

    def test_task8_combined_in_between_default(self):
        expected = [
            (103, 12, 2, 105),
            (108, 5, 3, 98),
            (110, 17, 2, 85)
        ]
        results = execute_task_query(SQL_FILE, 8, self.conn_default)
        self.assertEqual(results, expected, "Task 8 standard dataset failed")

    def test_task8_combined_in_between_boundary(self):
        # 301: age=5, hr=80 -> match!
        # 302: age=12, hr=110 -> match!
        # 303: age=17, hr=79 -> HR out of 80..110 range, excluded!
        # 304: age=18, hr=90 -> age not in (5, 12, 17), excluded!
        expected = [
            (301, 5, 1, 80),
            (302, 12, 2, 110)
        ]
        results = execute_task_query(SQL_FILE, 8, self.conn_range)
        self.assertEqual(results, expected, "Task 8 combined IN and BETWEEN failed")


if __name__ == "__main__":
    unittest.main()
