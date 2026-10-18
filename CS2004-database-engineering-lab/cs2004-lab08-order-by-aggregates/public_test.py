import unittest
from test_harness import setup_database, execute_view

class TestPublicQueries(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.conn = setup_database("solution.sql")

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()

    def test_q1_sorted_orders(self):
        rows = execute_view(self.conn, "q1_sorted_orders")
        self.assertEqual(len(rows), 5, "Expected 5 completed orders in Query 1")
        
        expected_order_ids = [1001, 1003, 1006, 1002, 1005]
        actual_order_ids = [row["order_id"] for row in rows]
        self.assertEqual(actual_order_ids, expected_order_ids, f"Order IDs sort mismatch. Expected {expected_order_ids}, got {actual_order_ids}")
        
        # Tie breaker assertion: 1001 and 1003 both total 1500.0, 1001 ('2026-01-10') must come before 1003 ('2026-01-15')
        self.assertEqual(rows[0]["order_id"], 1001)
        self.assertEqual(rows[1]["order_id"], 1003)

    def test_q2_rep_commission_summary(self):
        rows = execute_view(self.conn, "q2_rep_commission_summary")
        self.assertEqual(len(rows), 4, "Expected 4 sales reps in Query 2")
        
        expected_rep_ids = [103, 102, 101, 104]
        actual_rep_ids = [row["rep_id"] for row in rows]
        self.assertEqual(actual_rep_ids, expected_rep_ids, f"Rep IDs sort mismatch. Expected {expected_rep_ids}, got {actual_rep_ids}")
        
        # Tie breaker assertion for 0.15 commission rate: Brown (103) before Smith (102)
        self.assertEqual(rows[0]["last_name"], "Brown")
        self.assertEqual(rows[1]["last_name"], "Smith")

    def test_q3_regional_revenue_aggregates(self):
        rows = execute_view(self.conn, "q3_regional_revenue_aggregates")
        self.assertEqual(len(rows), 3, "Expected 3 regional aggregated rows in Query 3")
        
        # Sorted by region_id ASC: 1, 2, 3
        self.assertEqual(rows[0]["region_id"], 1)
        self.assertEqual(rows[0]["order_count"], 2)
        self.assertAlmostEqual(rows[0]["total_revenue"], 3000.0, places=2)
        self.assertAlmostEqual(rows[0]["avg_order_value"], 1500.0, places=2)
        self.assertAlmostEqual(rows[0]["min_order_value"], 1500.0, places=2)
        self.assertAlmostEqual(rows[0]["max_order_value"], 1500.0, places=2)

        self.assertEqual(rows[1]["region_id"], 2)
        self.assertEqual(rows[1]["order_count"], 2)
        self.assertAlmostEqual(rows[1]["total_revenue"], 2000.0, places=2)

        self.assertEqual(rows[2]["region_id"], 3)
        self.assertEqual(rows[2]["order_count"], 1)
        self.assertAlmostEqual(rows[2]["total_revenue"], 450.0, places=2)

    def test_q4_category_revenue_having(self):
        rows = execute_view(self.conn, "q4_category_revenue_having")
        self.assertEqual(len(rows), 2, "Expected 2 categories matching HAVING condition in Query 4")
        
        # Sorted by category_revenue DESC
        self.assertEqual(rows[0]["product_category"], "Enterprise Software")
        self.assertEqual(rows[0]["total_units"], 15)
        self.assertAlmostEqual(rows[0]["category_revenue"], 3000.0, places=2)

        self.assertEqual(rows[1]["product_category"], "Cloud Hosting")
        self.assertEqual(rows[1]["total_units"], 26)
        self.assertAlmostEqual(rows[1]["category_revenue"], 1300.0, places=2)

    def test_q5_tier_metrics_sorted(self):
        rows = execute_view(self.conn, "q5_tier_metrics_sorted")
        self.assertEqual(len(rows), 2, "Expected 2 tiers matching HAVING condition in Query 5")
        
        # Sorted by tier_revenue DESC: Platinum, Gold
        self.assertEqual(rows[0]["customer_tier"], "Platinum")
        self.assertEqual(rows[0]["unique_customers"], 1)
        self.assertEqual(rows[0]["total_orders"], 2)
        self.assertAlmostEqual(rows[0]["tier_revenue"], 3000.0, places=2)

        self.assertEqual(rows[1]["customer_tier"], "Gold")
        self.assertEqual(rows[1]["unique_customers"], 2)
        self.assertEqual(rows[1]["total_orders"], 2)
        self.assertAlmostEqual(rows[1]["tier_revenue"], 2000.0, places=2)

if __name__ == "__main__":
    unittest.main()
