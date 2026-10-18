import unittest
from test_harness import setup_db, execute_solution_script, assert_insert_update_state, assert_delete_select_state

class TestPublicDMLOperations(unittest.TestCase):
    def test_public_all_dml_operations(self):
        """Public test suite verifying overall DML script execution."""
        conn = setup_db()
        sql_content = execute_solution_script(conn, "solution.sql")
        assert_insert_update_state(conn)
        assert_delete_select_state(conn, sql_content)
        conn.close()

if __name__ == '__main__':
    unittest.main()
