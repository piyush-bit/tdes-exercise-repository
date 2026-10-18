import unittest
import sqlite3
import os
from test_harness import SCHEMA_DDL, execute_view

def seed_private_aggregates_db(conn):
    cursor = conn.cursor()
    cursor.executemany(
        "INSERT INTO sales_regions VALUES (?, ?, ?);",
        [
            (10, 'Region X', 'USA'),
            (20, 'Region Y', 'UK'),
            (30, 'Region Z', 'Japan')
        ]
    )
    
    cursor.executemany(
        "INSERT INTO sales_reps VALUES (?, ?, ?, ?, ?, ?);",
        [
            (1, 'Rep', 'One', 10, 50000.0, 0.10)
        ]
    )
    
    cursor.executemany(
        "INSERT INTO customers VALUES (?, ?, ?, ?);",
        [
            (1, 'Cust A', 'Gold', 10),
            (2, 'Cust B', 'Gold', 10),
            (3, 'Cust C', 'Silver', 20),
            (4, 'Cust D', 'Bronze', 20),
            (5, 'Cust E', 'Platinum', 30)
        ]
    )
    
    cursor.executemany(
        "INSERT INTO orders VALUES (?, ?, ?, ?, ?, ?);",
        [
            (101, 1, 1, '2026-03-01', 'COMPLETED', 2000.0),
            (102, 1, 1, '2026-03-02', 'COMPLETED', 3000.0),
            (103, 2, 1, '2026-03-03', 'COMPLETED', 1000.0),
            (104, 2, 1, '2026-03-04', 'PENDING', 4000.0),
            (105, 3, 1, '2026-03-05', 'COMPLETED', 800.0),
            (106, 4, 1, '2026-03-06', 'COMPLETED', 100.0),
            (107, 5, 1, '2026-03-07', 'COMPLETED', 5000.0)
        ]
    )
    
    cursor.executemany(
        "INSERT INTO order_items VALUES (?, ?, ?, ?, ?, ?);",
        [
            (1, 101, 'Analytics', 12, 100.0, 1200.0),
            (2, 102, 'Analytics', 8, 100.0, 800.0),
            (3, 103, 'Database', 5, 300.0, 1500.0),
            (4, 107, 'Database', 6, 300.0, 1800.0),
            (5, 105, 'Networking', 15, 20.0, 300.0), # Revenue < 500.0 (Excluded)
            (6, 106, 'Security', 4, 500.0, 2000.0)    # Units < 10 (Excluded)
        ]
    )
    conn.commit()


class TestPrivateGroupAggregates(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.conn = sqlite3.connect(":memory:")
        cls.conn.row_factory = sqlite3.Row
        cls.conn.executescript(SCHEMA_DDL)
        seed_private_aggregates_db(cls.conn)
        
        solution_path = "solution.sql"
        if os.path.exists(solution_path):
            with open(solution_path, "r", encoding="utf-8") as f:
                cls.conn.executescript(f.read())

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()

    def test_private_q3_regional_revenue_aggregates(self):
        rows = execute_view(self.conn, "q3_regional_revenue_aggregates")
        self.assertEqual(len(rows), 3, "Query 3 must aggregate 3 regions")
        
        # Region 10: 3 completed orders, total 6000.0, avg 2000.0, min 1000.0, max 3000.0
        self.assertEqual(rows[0]["region_id"], 10)
        self.assertEqual(rows[0]["order_count"], 3)
        self.assertAlmostEqual(rows[0]["total_revenue"], 6000.0, places=2)
        self.assertAlmostEqual(rows[0]["avg_order_value"], 2000.0, places=2)
        self.assertAlmostEqual(rows[0]["min_order_value"], 1000.0, places=2)
        self.assertAlmostEqual(rows[0]["max_order_value"], 3000.0, places=2)

        # Region 20: 2 completed orders, total 900.0
        self.assertEqual(rows[1]["region_id"], 20)
        self.assertEqual(rows[1]["order_count"], 2)
        self.assertAlmostEqual(rows[1]["total_revenue"], 900.0, places=2)

        # Region 30: 1 completed order, total 5000.0
        self.assertEqual(rows[2]["region_id"], 30)
        self.assertEqual(rows[2]["order_count"], 1)
        self.assertAlmostEqual(rows[2]["total_revenue"], 5000.0, places=2)

    def test_private_q4_category_revenue_having(self):
        rows = execute_view(self.conn, "q4_category_revenue_having")
        self.assertEqual(len(rows), 2, "Query 4 must filter out categories failing HAVING thresholds")
        
        # Database revenue 3300.0 comes first (DESC)
        self.assertEqual(rows[0]["product_category"], "Database")
        self.assertEqual(rows[0]["total_units"], 11)
        self.assertAlmostEqual(rows[0]["category_revenue"], 3300.0, places=2)
        self.assertAlmostEqual(rows[0]["avg_unit_price"], 300.0, places=2)

        # Analytics revenue 2000.0 comes second
        self.assertEqual(rows[1]["product_category"], "Analytics")
        self.assertEqual(rows[1]["total_units"], 20)
        self.assertAlmostEqual(rows[1]["category_revenue"], 2000.0, places=2)

    def test_private_q5_tier_metrics_sorted(self):
        rows = execute_view(self.conn, "q5_tier_metrics_sorted")
        self.assertEqual(len(rows), 2, "Query 5 must filter out customer tiers under $1000 threshold")
        
        # Gold tier has 6000.0 revenue -> 1st
        self.assertEqual(rows[0]["customer_tier"], "Gold")
        self.assertEqual(rows[0]["unique_customers"], 2)
        self.assertEqual(rows[0]["total_orders"], 3)
        self.assertAlmostEqual(rows[0]["tier_revenue"], 6000.0, places=2)

        # Platinum tier has 5000.0 revenue -> 2nd
        self.assertEqual(rows[1]["customer_tier"], "Platinum")
        self.assertEqual(rows[1]["unique_customers"], 1)
        self.assertEqual(rows[1]["total_orders"], 1)
        self.assertAlmostEqual(rows[1]["tier_revenue"], 5000.0, places=2)

if __name__ == "__main__":
    unittest.main()
