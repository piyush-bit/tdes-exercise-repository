import unittest
import os
from test_harness import init_db, assert_table_exists, get_table_columns

class PublicWalletTableTest(unittest.TestCase):
    def setUp(self):
        self.sql_path = "solution.sql"
        self.assertTrue(os.path.exists(self.sql_path), "solution.sql file must exist.")
        self.conn = init_db(self.sql_path)

    def tearDown(self):
        if hasattr(self, "conn") and self.conn:
            self.conn.close()

    def test_table_exists(self):
        """Verify user_wallets table is created by solution.sql."""
        assert_table_exists(self.conn, "user_wallets")

    def test_columns_exist(self):
        """Verify all required columns exist in user_wallets."""
        columns = get_table_columns(self.conn, "user_wallets")
        required_cols = {"wallet_id", "user_id", "account_number", "balance", "currency"}
        missing = required_cols - set(columns.keys())
        self.assertEqual(len(missing), 0, f"Missing required columns in user_wallets: {missing}")

    def test_basic_insert_select(self):
        """Verify basic row insertion and selection works."""
        cursor = self.conn.cursor()
        cursor.execute(
            "INSERT INTO user_wallets (user_id, account_number, balance, currency) VALUES (?, ?, ?, ?);",
            (10, "ACC1001", 150.75, "USD")
        )
        self.conn.commit()

        cursor.execute("SELECT wallet_id, user_id, account_number, balance, currency FROM user_wallets WHERE user_id = 10;")
        row = cursor.fetchone()
        self.assertIsNotNone(row, "Inserted record could not be retrieved.")
        self.assertEqual(row[1], 10)
        self.assertEqual(row[2], "ACC1001")
        self.assertAlmostEqual(float(row[3]), 150.75)
        self.assertEqual(row[4], "USD")

if __name__ == "__main__":
    unittest.main()
