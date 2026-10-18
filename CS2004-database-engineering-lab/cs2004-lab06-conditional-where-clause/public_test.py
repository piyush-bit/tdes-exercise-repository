import unittest
import os
from test_harness import create_database, execute_task_query

SQL_FILE = os.path.join(os.path.dirname(__file__), "solution.sql")


class TestPublicSQLQueries(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.conn = create_database()

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()

    def test_task1_equal_operator(self):
        expected = [
            (101, 'Alice', 'Smith', 1, 'Severe Chest Pain'),
            (105, 'Evan', 'Wright', 1, 'Cardiac Arrest'),
            (111, 'Kevin', 'Bacon', 1, 'Unresponsive')
        ]
        results = execute_task_query(SQL_FILE, 1, self.conn)
        self.assertEqual(results, expected, "Task 1 (triage_level = 1) query results mismatch")

    def test_task2_greater_than(self):
        expected = [
            (105, 140, 85),
            (101, 115, 145),
            (115, 112, 115),
            (113, 108, 138),
            (103, 105, 110),
            (107, 102, 160)
        ]
        results = execute_task_query(SQL_FILE, 2, self.conn)
        self.assertEqual(results, expected, "Task 2 (heart_rate > 100) query results mismatch")

    def test_task3_less_than(self):
        expected = [
            (111, 'Kevin', 'Bacon', 85),
            (105, 'Evan', 'Wright', 88),
            (101, 'Alice', 'Smith', 92),
            (110, 'Julia', 'Roberts', 93),
            (102, 'Bob', 'Jones', 94),
            (115, 'Oscar', 'Isaac', 94)
        ]
        results = execute_task_query(SQL_FILE, 3, self.conn)
        self.assertEqual(results, expected, "Task 3 (oxygen_stat < 95) query results mismatch")

    def test_task4_greater_equal(self):
        expected = [
            (111, 'Kevin', 'Bacon', 82),
            (105, 'Evan', 'Wright', 75),
            (114, 'Nora', 'Jones', 70),
            (102, 'Bob', 'Jones', 68),
            (107, 'George', 'Clark', 65)
        ]
        results = execute_task_query(SQL_FILE, 4, self.conn)
        self.assertEqual(results, expected, "Task 4 (age >= 65) query results mismatch")

    def test_task5_less_equal(self):
        expected = [
            (111, 34.9, 'Unresponsive'),
            (105, 35.2, 'Cardiac Arrest')
        ]
        results = execute_task_query(SQL_FILE, 5, self.conn)
        self.assertEqual(results, expected, "Task 5 (body_temp <= 35.5) query results mismatch")

    def test_task6_between_range(self):
        expected = [
            (109, 'Ian', 'Malcolm', 120),
            (112, 'Laura', 'Croft', 122),
            (106, 'Fiona', 'Gallagher', 125),
            (102, 'Bob', 'Jones', 130),
            (113, 'Michael', 'Scott', 138)
        ]
        results = execute_task_query(SQL_FILE, 6, self.conn)
        self.assertEqual(results, expected, "Task 6 (systolic_bp BETWEEN 120 AND 139) query results mismatch")

    def test_task7_in_set(self):
        expected = [
            (101, 'Alice', 'Smith', 'AMB', 1),
            (105, 'Evan', 'Wright', 'AMB', 1),
            (111, 'Kevin', 'Bacon', 'AMB', 1),
            (107, 'George', 'Clark', 'AMB', 2),
            (110, 'Julia', 'Roberts', 'AMB', 2),
            (114, 'Nora', 'Jones', 'XFER', 2),
            (106, 'Fiona', 'Gallagher', 'XFER', 3)
        ]
        results = execute_task_query(SQL_FILE, 7, self.conn)
        self.assertEqual(results, expected, "Task 7 (arrival_code IN ('AMB', 'XFER')) query results mismatch")

    def test_task8_combined_in_between(self):
        expected = [
            (103, 12, 2, 105),
            (108, 5, 3, 98),
            (110, 17, 2, 85)
        ]
        results = execute_task_query(SQL_FILE, 8, self.conn)
        self.assertEqual(results, expected, "Task 8 (age IN (5, 12, 17) AND heart_rate BETWEEN 80 AND 110) query results mismatch")


if __name__ == "__main__":
    unittest.main()
