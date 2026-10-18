import unittest
import os
from test_harness import init_db, assert_table_structure, get_table_columns

class TestTableStructure(unittest.TestCase):
    def setUp(self):
        self.sql_path = "solution.sql"
        self.assertTrue(os.path.exists(self.sql_path), "solution.sql file must exist.")
        self.conn = init_db(self.sql_path)

    def tearDown(self):
        if hasattr(self, "conn") and self.conn:
            self.conn.close()

    def test_table_structure(self):
        """Validates user_wallets table existence, column definitions, primary key, and default values."""
        assert_table_structure(self.conn)

    def test_column_types(self):
        """Validates that column data types are declared appropriately."""
        columns = get_table_columns(self.conn, "user_wallets")
        
        # Check wallet_id is integer primary key
        self.assertIn("INT", columns["wallet_id"]["type"])
        # Check user_id type contains INT
        self.assertIn("INT", columns["user_id"]["type"])
        # Check account_number type is TEXT or VARCHAR
        self.assertTrue("TEXT" in columns["account_number"]["type"] or "CHAR" in columns["account_number"]["type"])
        # Check balance type is REAL, NUMERIC, or DECIMAL
        self.assertTrue(any(t in columns["balance"]["type"] for t in ["REAL", "NUMERIC", "DECIMAL", "FLOAT", "DOUBLE"]))
        # Check currency type is TEXT or VARCHAR
        self.assertTrue("TEXT" in columns["currency"]["type"] or "CHAR" in columns["currency"]["type"])

if __name__ == "__main__":
    unittest.main()
