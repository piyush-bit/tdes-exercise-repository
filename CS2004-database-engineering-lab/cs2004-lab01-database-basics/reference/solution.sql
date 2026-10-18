-- CS2004 Lab 01: SaaS Multi-Tenant Catalog Initialization Reference Solution

PRAGMA foreign_keys = ON;

-- 1. Create `tenants` table
CREATE TABLE IF NOT EXISTS tenants (
    tenant_id TEXT PRIMARY KEY NOT NULL,
    tenant_name TEXT NOT NULL,
    domain TEXT UNIQUE NOT NULL,
    plan_tier TEXT NOT NULL CHECK (plan_tier IN ('free', 'starter', 'pro', 'enterprise')),
    status TEXT NOT NULL DEFAULT 'pending' CHECK (status IN ('active', 'suspended', 'pending')),
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- 2. Create `schemas` table
CREATE TABLE IF NOT EXISTS schemas (
    schema_id INTEGER PRIMARY KEY AUTOINCREMENT,
    tenant_id TEXT NOT NULL,
    schema_name TEXT UNIQUE NOT NULL,
    db_engine TEXT NOT NULL DEFAULT 'sqlite' CHECK (db_engine IN ('sqlite', 'postgresql', 'mysql')),
    is_isolated INTEGER NOT NULL DEFAULT 0 CHECK (is_isolated IN (0, 1)),
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (tenant_id) REFERENCES tenants(tenant_id) ON DELETE CASCADE
);

-- 3. Create `schema_tables` table
CREATE TABLE IF NOT EXISTS schema_tables (
    table_id INTEGER PRIMARY KEY AUTOINCREMENT,
    schema_id INTEGER NOT NULL,
    table_name TEXT NOT NULL,
    row_count_estimate INTEGER NOT NULL DEFAULT 0 CHECK (row_count_estimate >= 0),
    is_encrypted INTEGER NOT NULL DEFAULT 0 CHECK (is_encrypted IN (0, 1)),
    FOREIGN KEY (schema_id) REFERENCES schemas(schema_id) ON DELETE CASCADE,
    CONSTRAINT uq_schema_table UNIQUE (schema_id, table_name)
);

-- 4. Create View `v_tenant_catalog_summary`
CREATE VIEW IF NOT EXISTS v_tenant_catalog_summary AS
SELECT 
    t.tenant_id,
    t.tenant_name,
    t.plan_tier,
    t.status,
    COUNT(DISTINCT s.schema_id) AS total_schemas,
    COUNT(st.table_id) AS total_tables,
    COALESCE(SUM(st.row_count_estimate), 0) AS total_estimated_rows
FROM tenants t
LEFT JOIN schemas s ON t.tenant_id = s.tenant_id
LEFT JOIN schema_tables st ON s.schema_id = st.schema_id
GROUP BY t.tenant_id, t.tenant_name, t.plan_tier, t.status
ORDER BY t.tenant_id ASC;

-- 5. Seed Catalog Insertions

-- System Admin Tenant
INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier, status)
VALUES ('t_sys_admin', 'System Admin', 'admin.saas.internal', 'enterprise', 'active');

INSERT INTO schemas (schema_id, tenant_id, schema_name, db_engine, is_isolated)
VALUES (1, 't_sys_admin', 'sys_catalog_db', 'sqlite', 1);

INSERT INTO schema_tables (schema_id, table_name, row_count_estimate, is_encrypted)
VALUES 
    (1, 'audit_logs', 1500, 1),
    (1, 'feature_flags', 50, 0);

-- Acme Corporation Tenant
INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier, status)
VALUES ('t_acme_corp', 'Acme Corporation', 'acme.saas.io', 'pro', 'active');

INSERT INTO schemas (schema_id, tenant_id, schema_name, db_engine, is_isolated)
VALUES (2, 't_acme_corp', 'acme_prod_db', 'postgresql', 1);

INSERT INTO schema_tables (schema_id, table_name, row_count_estimate, is_encrypted)
VALUES 
    (2, 'users', 25000, 1),
    (2, 'orders', 120000, 1),
    (2, 'products', 3400, 0);

-- Demo Startup Tenant
INSERT INTO tenants (tenant_id, tenant_name, domain, plan_tier, status)
VALUES ('t_starter_demo', 'Demo Startup', 'demo.saas.io', 'free', 'pending');

INSERT INTO schemas (schema_id, tenant_id, schema_name, db_engine, is_isolated)
VALUES (3, 't_starter_demo', 'demo_shared_db', 'sqlite', 0);

INSERT INTO schema_tables (schema_id, table_name, row_count_estimate, is_encrypted)
VALUES 
    (3, 'sandbox_items', 10, 0);
