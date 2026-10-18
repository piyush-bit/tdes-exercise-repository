-- CS2004 Lab 01: SaaS Multi-Tenant Catalog Initialization
-- Author your DDL statements, Views, and DML seed insertions below.

-- TODO: Task 1 - Create `tenants` table with columns:
-- tenant_id (TEXT PRIMARY KEY), tenant_name (TEXT NOT NULL), domain (TEXT UNIQUE NOT NULL),
-- plan_tier (CHECK 'free','starter','pro','enterprise'), status (CHECK 'active','suspended','pending', DEFAULT 'pending'),
-- created_at (DEFAULT CURRENT_TIMESTAMP).


-- TODO: Task 2 - Create `schemas` table with columns:
-- schema_id (INTEGER PRIMARY KEY AUTOINCREMENT), tenant_id (FOREIGN KEY -> tenants(tenant_id) ON DELETE CASCADE),
-- schema_name (TEXT UNIQUE NOT NULL), db_engine (CHECK 'sqlite','postgresql','mysql', DEFAULT 'sqlite'),
-- is_isolated (CHECK 0 or 1, DEFAULT 0), created_at (DEFAULT CURRENT_TIMESTAMP).


-- TODO: Task 3 - Create `schema_tables` table with columns:
-- table_id (INTEGER PRIMARY KEY AUTOINCREMENT), schema_id (FOREIGN KEY -> schemas(schema_id) ON DELETE CASCADE),
-- table_name (TEXT NOT NULL), row_count_estimate (INTEGER >= 0, DEFAULT 0), is_encrypted (CHECK 0 or 1, DEFAULT 0),
-- UNIQUE(schema_id, table_name).


-- TODO: Task 4 - Create View `v_tenant_catalog_summary` aggregating tenant catalog stats:
-- tenant_id, tenant_name, plan_tier, status, total_schemas, total_tables, total_estimated_rows.


-- TODO: Task 5 - Insert seed records into `tenants`, `schemas`, and `schema_tables` for:
-- 1. 't_sys_admin'
-- 2. 't_acme_corp'
-- 3. 't_starter_demo'
