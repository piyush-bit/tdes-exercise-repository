import sys
import os
import unittest

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from test_harness import setup_db, execute_solution_script, assert_insert_update_state

class TestPrivateInsertUpdate(unittest.TestCase):
    def test_private_insert_update_operations(self):
        """Private test suite evaluating INSERT and UPDATE operations."""
        conn = setup_db()
        execute_solution_script(conn, "solution.sql")
        assert_insert_update_state(conn)
        conn.close()

if __name__ == '__main__':
    unittest.main()
