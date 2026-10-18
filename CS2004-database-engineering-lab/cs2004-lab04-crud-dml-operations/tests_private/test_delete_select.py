import sys
import os
import unittest

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from test_harness import setup_db, execute_solution_script, assert_delete_select_state

class TestPrivateDeleteSelect(unittest.TestCase):
    def test_private_delete_select_operations(self):
        """Private test suite evaluating DELETE and SELECT operations."""
        conn = setup_db()
        sql_content = execute_solution_script(conn, "solution.sql")
        assert_delete_select_state(conn, sql_content)
        conn.close()

if __name__ == '__main__':
    unittest.main()
