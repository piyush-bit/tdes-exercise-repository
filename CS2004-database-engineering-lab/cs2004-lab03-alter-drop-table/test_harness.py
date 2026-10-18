import sqlite3
import os
from typing import Dict, Any

SEED_PRODUCTS = [
    (1, 'Laptop', 999.99, 15),
    (2, 'Wireless Mouse', 25.50, 100),
    (3, 'Mechanical Keyboard', 89.00, 45)
]

SEED_LEGACY_ORDERS = [
    (1, 101, 'Legacy order #1 details'),
    (2, 102, 'Legacy order #2 details')
]

def setup_db() -> sqlite3.Connection:
    """Initializes an in-memory SQLite DB with base products and legacy_orders tables and seed data."""
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE products (
            product_id INTEGER PRIMARY KEY AUTOINCREMENT,
            product_name TEXT NOT NULL,
            price REAL NOT NULL,
            stock_quantity INTEGER DEFAULT 0
        );
    """)
    cursor.executemany("""
        INSERT INTO products (product_id, product_name, price, stock_quantity)
        VALUES (?, ?, ?, ?);
    """, SEED_PRODUCTS)

    cursor.execute("""
        CREATE TABLE legacy_orders (
            order_id INTEGER PRIMARY KEY AUTOINCREMENT,
            customer_id INTEGER NOT NULL,
            order_details TEXT
        );
    """)
    cursor.executemany("""
        INSERT INTO legacy_orders (order_id, customer_id, order_details)
        VALUES (?, ?, ?);
    """, SEED_LEGACY_ORDERS)

    conn.commit()
    return conn

def execute_solution_script(conn: sqlite3.Connection, sql_file_path: str = "solution.sql") -> str:
    """Executes the student's solution.sql script on the database connection."""
    if not os.path.exists(sql_file_path):
        raise FileNotFoundError(f"Solution script file not found: {sql_file_path}")
    with open(sql_file_path, 'r', encoding='utf-8') as f:
        sql_content = f.read()
    conn.executescript(sql_content)
    conn.commit()
    return sql_content

def get_table_columns(conn: sqlite3.Connection, table_name: str) -> Dict[str, Dict[str, Any]]:
    """Retrieves column metadata for table_name via PRAGMA table_info."""
    cursor = conn.cursor()
    cursor.execute(f"PRAGMA table_info('{table_name}');")
    rows = cursor.fetchall()
    columns = {}
    for cid, name, col_type, notnull, dflt_value, pk in rows:
        columns[name] = {
            "cid": cid,
            "name": name,
            "type": col_type.upper(),
            "notnull": bool(notnull),
            "default": dflt_value,
            "pk": bool(pk)
        }
    return columns

def table_exists(conn: sqlite3.Connection, table_name: str) -> bool:
    """Checks if table_name exists in the database schema catalog."""
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name=?;", (table_name,))
    return cursor.fetchone() is not None

def assert_alter_table_state(conn: sqlite3.Connection):
    """Asserts that ALTER TABLE operations (ADD COLUMN category, RENAME COLUMN stock_quantity TO stock) succeeded."""
    if not table_exists(conn, "products"):
        raise AssertionError("Table 'products' does not exist in the database.")
    
    columns = get_table_columns(conn, "products")
    
    # 1. Assert 'category' column exists and is TEXT
    if "category" not in columns:
        raise AssertionError("ALTER TABLE failed: Column 'category' was not added to 'products' table.")
    
    cat_type = columns["category"]["type"]
    if "TEXT" not in cat_type:
        raise AssertionError(f"ALTER TABLE failed: Column 'category' expected type TEXT, got '{cat_type}'.")
    
    # 2. Assert 'stock' column exists and 'stock_quantity' no longer exists
    if "stock" not in columns:
        raise AssertionError("ALTER TABLE failed: Column 'stock' does not exist in 'products' table. Did you rename 'stock_quantity' to 'stock'?")
    
    if "stock_quantity" in columns:
        raise AssertionError("ALTER TABLE failed: Old column 'stock_quantity' still exists in 'products' table after rename.")
    
    # 3. Assert existing rows preserved data under renamed column 'stock'
    cursor = conn.cursor()
    cursor.execute("SELECT product_id, product_name, price, stock FROM products WHERE product_id = 1;")
    row = cursor.fetchone()
    if not row:
        raise AssertionError("Failed to retrieve existing product record after schema alteration.")
    if row[3] != 15:
        raise AssertionError(f"Data corruption or loss after RENAME COLUMN: expected stock=15 for product 1, got {row[3]}")
    
    # 4. Assert new records can be inserted with category and stock columns
    try:
        cursor.execute("INSERT INTO products (product_name, price, stock, category) VALUES (?, ?, ?, ?);",
                       ('Smart Watch', 199.99, 20, 'Electronics'))
        conn.commit()
    except Exception as e:
        raise AssertionError(f"Failed to insert row with altered schema (category, stock): {e}")

def assert_drop_table_state(conn: sqlite3.Connection):
    """Asserts that DROP TABLE operation removed 'legacy_orders' table."""
    if table_exists(conn, "legacy_orders"):
        raise AssertionError("DROP TABLE failed: Table 'legacy_orders' still exists in the database.")
    
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT COUNT(*) FROM legacy_orders;")
        raise AssertionError("DROP TABLE failed: Querying 'legacy_orders' succeeded, but table should be dropped.")
    except sqlite3.OperationalError:
        pass  # Expected: no such table: legacy_orders
