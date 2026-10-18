import unittest
from test_harness import create_db_and_execute_solution, get_table_names, get_view_names

class TestPublicCatalogBasics(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.conn = create_db_and_execute_solution("solution.sql")

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()

    def test_01_tables_and_views_exist(self):
        tables = get_table_names(self.conn)
        views = get_view_names(self.conn)

        self.assertIn("tenants", tables, "Table 'tenants' must be created.")
        self.assertIn("schemas", tables, "Table 'schemas' must be created.")
        self.assertIn("schema_tables", tables, "Table 'schema_tables' must be created.")
        self.assertIn("v_tenant_catalog_summary", views, "View 'v_tenant_catalog_summary' must be created.")

    def test_02_seed_tenants_inserted(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT tenant_id, tenant_name, plan_tier, status FROM tenants ORDER BY tenant_id ASC;")
        rows = cursor.fetchall()
        
        self.assertGreaterEqual(len(rows), 3, "At least 3 seed tenants should be present.")
        tenant_ids = [r[0] for r in rows]
        self.assertIn("t_acme_corp", tenant_ids, "Tenant 't_acme_corp' should be seeded.")
        self.assertIn("t_starter_demo", tenant_ids, "Tenant 't_starter_demo' should be seeded.")
        self.assertIn("t_sys_admin", tenant_ids, "Tenant 't_sys_admin' should be seeded.")

    def test_03_public_view_query(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT tenant_id, total_schemas, total_tables, total_estimated_rows FROM v_tenant_catalog_summary WHERE tenant_id = 't_acme_corp';")
        row = cursor.fetchone()
        
        self.assertIsNotNone(row, "View query for 't_acme_corp' returned no result.")
        tenant_id, schemas, tables, est_rows = row
        self.assertEqual(tenant_id, "t_acme_corp")
        self.assertEqual(schemas, 1, "t_acme_corp should have 1 schema.")
        self.assertEqual(tables, 3, "t_acme_corp should have 3 tables.")
        self.assertEqual(est_rows, 148400, "t_acme_corp estimated rows should be 25000 + 120000 + 3400 = 148400.")

if __name__ == "__main__":
    unittest.main()
