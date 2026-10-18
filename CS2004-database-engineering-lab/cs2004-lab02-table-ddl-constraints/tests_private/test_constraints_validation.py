import unittest
import os
from test_harness import init_db, assert_constraints_validation

class TestConstraintsValidation(unittest.TestCase):
    def setUp(self):
        self.sql_path = "solution.sql"
        self.assertTrue(os.path.exists(self.sql_path), "solution.sql file must exist.")
        self.conn = init_db(self.sql_path)

    def tearDown(self):
        if hasattr(self, "conn") and self.conn:
            self.conn.close()

    def test_constraints_validation(self):
        """Validates NOT NULL, UNIQUE, and PRIMARY KEY constraints on user_wallets."""
        assert_constraints_validation(self.conn)

if __name__ == "__main__":
    unittest.main()
