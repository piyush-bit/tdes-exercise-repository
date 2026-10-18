import unittest
from test_harness import create_db_and_execute_solution

class TestSchemaMetadata(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.conn = create_db_and_execute_solution("solution.sql")

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()

    def test_01_seed_tenants_and_schemas(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT tenant_id, schema_name, db_engine, is_isolated FROM schemas ORDER BY schema_id ASC;")
        schemas = cursor.fetchall()
        
        self.assertEqual(len(schemas), 3, "Expected 3 initial seed schemas.")
        self.assertEqual(schemas[0], ("t_sys_admin", "sys_catalog_db", "sqlite", 1))
        self.assertEqual(schemas[1], ("t_acme_corp", "acme_prod_db", "postgresql", 1))
        self.assertEqual(schemas[2], ("t_starter_demo", "demo_shared_db", "sqlite", 0))

    def test_02_seed_tables_and_row_estimates(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT schema_id, table_name, row_count_estimate, is_encrypted FROM schema_tables ORDER BY table_id ASC;")
        tables = cursor.fetchall()
        
        self.assertEqual(len(tables), 6, "Expected 6 initial seed table records.")
        # Check audit_logs
        self.assertEqual(tables[0][1], "audit_logs")
        self.assertEqual(tables[0][2], 1500)
        self.assertEqual(tables[0][3], 1)
        
        # Check orders
        orders_row = [t for t in tables if t[1] == "orders"][0]
        self.assertEqual(orders_row[2], 120000)

    def test_03_view_summary_seeded_data(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT tenant_id, tenant_name, plan_tier, status, total_schemas, total_tables, total_estimated_rows FROM v_tenant_catalog_summary ORDER BY tenant_id ASC;")
        rows = cursor.fetchall()
        
        self.assertGreaterEqual(len(rows), 3)
        row_dict = {r[0]: r for r in rows}
        
        # t_acme_corp
        self.assertIn("t_acme_corp", row_dict)
        r_acme = row_dict["t_acme_corp"]
        self.assertEqual(r_acme[1], "Acme Corporation")
        self.assertEqual(r_acme[2], "pro")
        self.assertEqual(r_acme[3], "active")
        self.assertEqual(r_acme[4], 1) # 1 schema
        self.assertEqual(r_acme[5], 3) # 3 tables
        self.assertEqual(r_acme[6], 148400) # 25000 + 120000 + 3400
        
        # t_sys_admin
        self.assertIn("t_sys_admin", row_dict)
        r_admin = row_dict["t_sys_admin"]
        self.assertEqual(r_admin[4], 1)
        self.assertEqual(r_admin[5], 2)
        self.assertEqual(r_admin[6], 1550) # 1500 + 50
        
        # t_starter_demo
        self.assertIn("t_starter_demo", row_dict)
        r_demo = row_dict["t_starter_demo"]
        self.assertEqual(r_demo[4], 1)
        self.assertEqual(r_demo[5], 1)
        self.assertEqual(r_demo[6], 10)

    def test_04_view_summary_empty_tenant_handling(self):
        conn = create_db_and_execute_solution("solution.sql")
        cursor = conn.cursor()
        
        # Insert tenant with no schema
        cursor.execute("INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier) VALUES ('t_empty', 'Empty Tenant', 'empty.io', 'free');")
        
        # Insert tenant with schema but no table
        cursor.execute("INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier) VALUES ('t_noschema_table', 'No Table Tenant', 'notable.io', 'starter');")
        cursor.execute("INSERT INTO schemas (schema_id, tenant_id, schema_name) VALUES (888, 't_noschema_table', 'empty_schema_db');")
        
        cursor.execute("SELECT tenant_id, total_schemas, total_tables, total_estimated_rows FROM v_tenant_catalog_summary WHERE tenant_id IN ('t_empty', 't_noschema_table') ORDER BY tenant_id ASC;")
        rows = cursor.fetchall()
        
        self.assertEqual(len(rows), 2)
        
        # t_empty
        t_empty = rows[0]
        self.assertEqual(t_empty[0], "t_empty")
        self.assertEqual(t_empty[1], 0, "Tenant with no schema should have total_schemas = 0.")
        self.assertEqual(t_empty[2], 0, "Tenant with no schema should have total_tables = 0.")
        self.assertEqual(t_empty[3], 0, "Tenant with no schema should have total_estimated_rows = 0.")
        
        # t_noschema_table
        t_notable = rows[1]
        self.assertEqual(t_notable[0], "t_noschema_table")
        self.assertEqual(t_notable[1], 1, "Tenant with 1 schema should have total_schemas = 1.")
        self.assertEqual(t_notable[2], 0, "Tenant with no tables should have total_tables = 0.")
        self.assertEqual(t_notable[3], 0, "Tenant with no tables should have total_estimated_rows = 0.")
        
        conn.close()

if __name__ == "__main__":
    unittest.main()
