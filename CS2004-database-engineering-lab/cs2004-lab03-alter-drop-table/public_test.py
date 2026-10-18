import unittest
from test_harness import setup_db, execute_solution_script, assert_alter_table_state, assert_drop_table_state

class TestPublicSchemaMigration(unittest.TestCase):
    def test_public_alter_and_drop_table(self):
        conn = setup_db()
        execute_solution_script(conn, "solution.sql")
        assert_alter_table_state(conn)
        assert_drop_table_state(conn)
        conn.close()

if __name__ == "__main__":
    unittest.main()
