import sqlite3
import unittest
from test_harness import create_db_and_execute_solution, get_table_columns, get_foreign_keys

class TestCatalogCreation(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.conn = create_db_and_execute_solution("solution.sql")

    @classmethod
    def tearDownClass(cls):
        cls.conn.close()

    def test_01_tenants_columns_and_constraints(self):
        cols = get_table_columns(self.conn, "tenants")
        self.assertIn("tenant_id", cols)
        self.assertTrue(cols["tenant_id"]["pk"], "tenant_id should be primary key.")
        self.assertTrue(cols["tenant_name"]["notnull"], "tenant_name must be NOT NULL.")
        self.assertTrue(cols["domain"]["notnull"], "domain must be NOT NULL.")
        self.assertTrue(cols["plan_tier"]["notnull"], "plan_tier must be NOT NULL.")
        self.assertTrue(cols["status"]["notnull"], "status must be NOT NULL.")

    def test_02_tenant_check_constraints(self):
        cursor = self.conn.cursor()
        
        # Test invalid plan_tier
        with self.assertRaises(sqlite3.IntegrityError, msg="Inserting invalid plan_tier should raise IntegrityError."):
            cursor.execute(
                "INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier) VALUES (?, ?, ?, ?);",
                ("t_bad_plan", "Bad Organization", "badplan.io", "ultra_vip")
            )
            
        # Test invalid status
        with self.assertRaises(sqlite3.IntegrityError, msg="Inserting invalid status should raise IntegrityError."):
            cursor.execute(
                "INSERT INTO tenants (tenant_id, tenant_name, domain, status) VALUES (?, ?, ?, ?);",
                ("t_bad_status", "Bad Status Org", "badstatus.io", "archived")
            )

    def test_03_tenant_domain_unique_constraint(self):
        cursor = self.conn.cursor()
        with self.assertRaises(sqlite3.IntegrityError, msg="Inserting duplicate domain should violate UNIQUE constraint."):
            cursor.execute(
                "INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier) VALUES (?, ?, ?, ?);",
                ("t_dup_domain", "Duplicate Domain Org", "acme.saas.io", "starter")
            )

    def test_04_schemas_foreign_keys_and_checks(self):
        fks = get_foreign_keys(self.conn, "schemas")
        fk_tables = [fk[2].lower() for fk in fks]
        self.assertIn("tenants", fk_tables, "schemas table must have foreign key to tenants.")
        
        cursor = self.conn.cursor()
        # Invalid FK tenant_id
        with self.assertRaises(sqlite3.IntegrityError, msg="Inserting schema with non-existent tenant_id should fail FK check."):
            cursor.execute(
                "INSERT INTO schemas (tenant_id, schema_name, db_engine) VALUES (?, ?, ?);",
                ("non_existent_tenant", "orphan_schema", "sqlite")
            )
            
        # Invalid db_engine
        with self.assertRaises(sqlite3.IntegrityError, msg="Inserting schema with invalid db_engine should fail check."):
            cursor.execute(
                "INSERT INTO schemas (tenant_id, schema_name, db_engine) VALUES (?, ?, ?);",
                ("t_sys_admin", "bad_engine_schema", "oracle")
            )

    def test_05_schema_tables_composite_unique_and_checks(self):
        cursor = self.conn.cursor()
        # Test negative row_count_estimate
        with self.assertRaises(sqlite3.IntegrityError, msg="Negative row_count_estimate should fail CHECK constraint."):
            cursor.execute(
                "INSERT INTO schema_tables (schema_id, table_name, row_count_estimate) VALUES (1, 'negative_rows', -5);"
            )
            
        # Test duplicate table_name per schema_id
        with self.assertRaises(sqlite3.IntegrityError, msg="Duplicate (schema_id, table_name) should fail UNIQUE constraint."):
            cursor.execute(
                "INSERT INTO schema_tables (schema_id, table_name) VALUES (1, 'audit_logs');"
            )

    def test_06_foreign_key_cascade_deletion(self):
        conn = create_db_and_execute_solution("solution.sql")
        cursor = conn.cursor()
        
        # Insert test tenant, schema, table
        cursor.execute("INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier) VALUES ('t_cascade', 'Cascade Org', 'cascade.io', 'starter');")
        cursor.execute("INSERT INTO schemas (schema_id, tenant_id, schema_name) VALUES (999, 't_cascade', 'cascade_db');")
        cursor.execute("INSERT INTO schema_tables (schema_id, table_name) VALUES (999, 'cascade_table');")
        
        # Delete tenant
        cursor.execute("DELETE FROM tenants WHERE tenant_id = 't_cascade';")
        
        # Verify schema and table were cascade deleted
        cursor.execute("SELECT COUNT(*) FROM schemas WHERE schema_id = 999;")
        self.assertEqual(cursor.fetchone()[0], 0, "Schema should be cascade deleted when tenant is deleted.")
        
        cursor.execute("SELECT COUNT(*) FROM schema_tables WHERE schema_id = 999;")
        self.assertEqual(cursor.fetchone()[0], 0, "Schema tables should be cascade deleted when schema is deleted.")
        conn.close()

if __name__ == "__main__":
    unittest.main()
