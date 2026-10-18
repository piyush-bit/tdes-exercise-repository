import unittest
from test_harness import setup_db, execute_solution_script, assert_drop_table_state

class TestDropTable(unittest.TestCase):
    def test_drop_table_migration(self):
        conn = setup_db()
        execute_solution_script(conn, "solution.sql")
        assert_drop_table_state(conn)
        conn.close()

if __name__ == "__main__":
    unittest.main()
