import unittest
import sqlite3
import os
from test_harness import SCHEMA_DDL, execute_view

def seed_private_sorting_db(conn):
    cursor = conn.cursor()
    cursor.executemany(
        "INSERT INTO sales_regions VALUES (?, ?, ?);",
        [
            (1, 'Region A', 'USA'),
            (2, 'Region B', 'UK'),
            (3, 'Region C', 'Canada')
        ]
    )
    
    # Reps designed to test multi-column tie breaking:
    # 204 has highest comm rate (0.25).
    # 201, 202, 203 all have comm rate 0.20 and last_name 'Taylor'.
    # first_names are Alice (202), Bob (203), Zachary (201).
    # 205 has lowest comm rate (0.10).
    cursor.executemany(
        "INSERT INTO sales_reps VALUES (?, ?, ?, ?, ?, ?);",
        [
            (201, 'Zachary', 'Taylor', 1, 60000.0, 0.20),
            (202, 'Alice', 'Taylor', 1, 60000.0, 0.20),
            (203, 'Bob', 'Taylor', 1, 60000.0, 0.20),
            (204, 'Aaron', 'Zimmerman', 2, 50000.0, 0.25),
            (205, 'Charles', 'Abbot', 3, 40000.0, 0.10)
        ]
    )
    
    cursor.executemany(
        "INSERT INTO customers VALUES (?, ?, ?, ?);",
        [
            (10, 'Cust 10', 'Gold', 1),
            (11, 'Cust 11', 'Platinum', 2),
            (12, 'Cust 12', 'Silver', 1),
            (13, 'Cust 13', 'Bronze', 3)
        ]
    )
    
    # Orders designed to test total_amount DESC, order_date ASC with ties:
    # 5004 total_amount 7500.0 (Highest -> 1st)
    # 5002, 5005, 5001 total_amount 5000.0 (Tied! Dates: 2026-05-01, 2026-05-05, 2026-05-10)
    # 5006 total_amount 1000.0 (Lowest -> last)
    # 5003 total_amount 9000.0 CANCELLED (Excluded!)
    cursor.executemany(
        "INSERT INTO orders VALUES (?, ?, ?, ?, ?, ?);",
        [
            (5001, 10, 201, '2026-05-10', 'COMPLETED', 5000.0),
            (5002, 10, 201, '2026-05-01', 'COMPLETED', 5000.0),
            (5003, 10, 201, '2026-05-15', 'CANCELLED', 9000.0),
            (5004, 11, 202, '2026-04-01', 'COMPLETED', 7500.0),
            (5005, 12, 203, '2026-05-05', 'COMPLETED', 5000.0),
            (5006, 13, 204, '2026-06-01', 'COMPLETED', 1000.0)
        ]
    )
    conn.commit()


class TestPrivateSortingOrdering(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.conn = sqlite3.connect(":memory:")
        cls.conn.row_factory = sqlite3.Row
        cls.conn.executescript(SCHEMA_DDL)
        seed_private_sorting_db(cls.conn)
        
        solution_path = "solution.sql"
        if os.path.exists(solution_path):
            with open(solution_path, "r", encoding="utf-8") as f:
                cls.conn.executescript(f.read())

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()

    def test_private_q1_sorted_orders(self):
        rows = execute_view(self.conn, "q1_sorted_orders")
        self.assertEqual(len(rows), 5, "Query 1 must return 5 completed orders")
        
        expected_ids = [5004, 5002, 5005, 5001, 5006]
        actual_ids = [r["order_id"] for r in rows]
        self.assertEqual(actual_ids, expected_ids, f"Ordering failed. Expected {expected_ids}, got {actual_ids}")

        # Check total amount sequence
        amounts = [r["total_amount"] for r in rows]
        self.assertEqual(amounts, [7500.0, 5000.0, 5000.0, 5000.0, 1000.0])

        # Check order_date tie breaking sequence for 5000.0 orders
        dates = [r["order_date"] for r in rows[1:4]]
        self.assertEqual(dates, ['2026-05-01', '2026-05-05', '2026-05-10'])

    def test_private_q2_rep_commission_summary(self):
        rows = execute_view(self.conn, "q2_rep_commission_summary")
        self.assertEqual(len(rows), 5, "Query 2 must return 5 sales reps")
        
        expected_rep_ids = [204, 202, 203, 201, 205]
        actual_rep_ids = [r["rep_id"] for r in rows]
        self.assertEqual(actual_rep_ids, expected_rep_ids, f"Rep ordering failed. Expected {expected_rep_ids}, got {actual_rep_ids}")

        # Verify tie-breaker among 0.20 rate: Alice Taylor, Bob Taylor, Zachary Taylor
        taylor_first_names = [r["first_name"] for r in rows[1:4]]
        self.assertEqual(taylor_first_names, ['Alice', 'Bob', 'Zachary'])

if __name__ == "__main__":
    unittest.main()
