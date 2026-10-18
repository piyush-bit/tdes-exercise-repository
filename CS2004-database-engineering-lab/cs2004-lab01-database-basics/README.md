# CS2004 Lab 01: SaaS Multi-Tenant Catalog Initialization

## Problem Statement

In a multi-tenant Software-as-a-Service (SaaS) platform, maintaining a centralized metadata catalog is critical for tracking tenant organizations, dedicated database schemas, isolated table definitions, and capacity metrics.

Your task in this lab is to author `solution.sql` to initialize the multi-tenant catalog database. You will write DDL statements to construct relational catalog tables with strict integrity constraints, construct an aggregate catalog view, and populate the database with initial seed catalog records.

---

## Technical Specifications

### 1. Catalog Tables DDL

Write SQL DDL statements to create the following three tables with foreign key constraints, default values, check constraints, and unique indexes:

#### `tenants` Table
- `tenant_id` (TEXT, PRIMARY KEY, NOT NULL): Unique tenant string key.
- `tenant_name` (TEXT, NOT NULL): Organization display name.
- `domain` (TEXT, UNIQUE, NOT NULL): Fully-qualified domain name.
- `plan_tier` (TEXT, NOT NULL): Subscription tier. Must be restricted to: `'free'`, `'starter'`, `'pro'`, or `'enterprise'`.
- `status` (TEXT, NOT NULL, DEFAULT `'pending'`): Account status. Must be restricted to: `'active'`, `'suspended'`, or `'pending'`.
- `created_at` (TEXT, NOT NULL, DEFAULT `CURRENT_TIMESTAMP`): Registration timestamp.

#### `schemas` Table
- `schema_id` (INTEGER, PRIMARY KEY AUTOINCREMENT): Surrogate key.
- `tenant_id` (TEXT, NOT NULL): Foreign key referencing `tenants(tenant_id)` with `ON DELETE CASCADE`.
- `schema_name` (TEXT, UNIQUE, NOT NULL): Physical database/schema identifier.
- `db_engine` (TEXT, NOT NULL, DEFAULT `'sqlite'`): Database engine. Must be restricted to: `'sqlite'`, `'postgresql'`, or `'mysql'`.
- `is_isolated` (INTEGER, NOT NULL, DEFAULT 0): Isolation flag (0 = shared infrastructure, 1 = dedicated). Must be restricted to `0` or `1`.
- `created_at` (TEXT, NOT NULL, DEFAULT `CURRENT_TIMESTAMP`): Schema provisioning timestamp.

#### `schema_tables` Table
- `table_id` (INTEGER, PRIMARY KEY AUTOINCREMENT): Surrogate key.
- `schema_id` (INTEGER, NOT NULL): Foreign key referencing `schemas(schema_id)` with `ON DELETE CASCADE`.
- `table_name` (TEXT, NOT NULL): Table name.
- `row_count_estimate` (INTEGER, NOT NULL, DEFAULT 0): Estimated row count (`row_count_estimate >= 0`).
- `is_encrypted` (INTEGER, NOT NULL, DEFAULT 0): Encryption status (0 = unencrypted, 1 = encrypted). Must be restricted to `0` or `1`.
- Composite `UNIQUE` constraint on `(schema_id, table_name)`.

---

### 2. Catalog View `v_tenant_catalog_summary`

Create a view named `v_tenant_catalog_summary` that aggregates tenant catalog metrics across all tenants.

The view must return the following columns for every tenant:
1. `tenant_id` (TEXT)
2. `tenant_name` (TEXT)
3. `plan_tier` (TEXT)
4. `status` (TEXT)
5. `total_schemas` (INTEGER): Count of schemas provisioned for the tenant.
6. `total_tables` (INTEGER): Count of total tables defined across all tenant schemas.
7. `total_estimated_rows` (INTEGER): Sum of `row_count_estimate` across all tables owned by the tenant (0 if the tenant has no tables).

---

### 3. Seed Catalog Insertion (DML)

Populate the database with the following system tenant catalog data:

1. **System Administrator Tenant (`t_sys_admin`)**:
   - `tenants`: `('t_sys_admin', 'System Admin', 'admin.saas.internal', 'enterprise', 'active')`
   - `schemas`: `('t_sys_admin', 'sys_catalog_db', 'sqlite', 1)`
   - `schema_tables` under `sys_catalog_db`:
     - `('audit_logs', 1500, 1)`
     - `('feature_flags', 50, 0)`

2. **Pro Corporate Tenant (`t_acme_corp`)**:
   - `tenants`: `('t_acme_corp', 'Acme Corporation', 'acme.saas.io', 'pro', 'active')`
   - `schemas`: `('t_acme_corp', 'acme_prod_db', 'postgresql', 1)`
   - `schema_tables` under `acme_prod_db`:
     - `('users', 25000, 1)`
     - `('orders', 120000, 1)`
     - `('products', 3400, 0)`

3. **Free Demo Tenant (`t_starter_demo`)**:
   - `tenants`: `('t_starter_demo', 'Demo Startup', 'demo.saas.io', 'free', 'pending')`
   - `schemas`: `('t_starter_demo', 'demo_shared_db', 'sqlite', 0)`
   - `schema_tables` under `demo_shared_db`:
     - `('sandbox_items', 10, 0)`

---

## Instructions & Local Verification

- Work strictly inside `solution.sql`.
- Run tests locally using the helper script or Makefile:
  ```bash
  ./run public
  # or
  make test-public
  ```
