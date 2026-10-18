import sqlite3
import os
import sys

SCHEMA_SQL = """
CREATE TABLE customers (
    customer_id INTEGER PRIMARY KEY,
    company_name TEXT NOT NULL,
    contact_name TEXT NOT NULL,
    city TEXT NOT NULL
);

CREATE TABLE products (
    product_id INTEGER PRIMARY KEY,
    product_name TEXT NOT NULL,
    category TEXT NOT NULL,
    unit_price REAL NOT NULL
);

CREATE TABLE orders (
    order_id INTEGER PRIMARY KEY,
    customer_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    order_date TEXT NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);
"""

SEED_DATA_SQL = """
INSERT INTO customers (customer_id, company_name, contact_name, city) VALUES
(1, 'Apex Logistics', 'Alice Smith', 'Chicago'),
(2, 'Beacon Retail', 'Bob Jones', 'New York'),
(3, 'Crestline Manufacturing', 'Charlie Brown', 'Seattle'),
(4, 'Delta Wholesale', 'Diana Prince', 'Austin'),
(5, 'Echo Enterprises', 'Evan Wright', 'Miami');

INSERT INTO products (product_id, product_name, category, unit_price) VALUES
(101, 'Industrial Pallet', 'Storage', 45.00),
(102, 'Forklift Battery', 'Equipment', 1200.00),
(103, 'Barcode Scanner', 'Electronics', 150.00),
(104, 'Hydraulic Jack', 'Equipment', 350.00),
(105, 'Thermal Label Roll', 'Supplies', 25.00);

INSERT INTO orders (order_id, customer_id, product_id, quantity, order_date) VALUES
(5001, 1, 101, 10, '2026-01-10'),
(5002, 1, 103, 2, '2026-01-12'),
(5003, 2, 102, 1, '2026-01-15'),
(5004, 2, 101, 5, '2026-01-18'),
(5005, 3, 103, 4, '2026-01-20');
"""

def setup_database(sql_file_path="solution.sql"):
    """
    Initializes an in-memory SQLite database with schema and seed data,
    then executes the given SQL script (e.g. solution.sql).
    """
    conn = sqlite3.connect(":memory:")
    cursor = conn.cursor()
    
    # Enable Foreign Keys
    cursor.execute("PRAGMA foreign_keys = ON;")
    
    # Setup tables and seed data
    cursor.executescript(SCHEMA_SQL)
    cursor.executescript(SEED_DATA_SQL)
    
    if not os.path.exists(sql_file_path):
        raise FileNotFoundError(f"SQL solution file not found: {sql_file_path}")
        
    with open(sql_file_path, "r", encoding="utf-8") as f:
        solution_sql = f.read()
        
    cursor.executescript(solution_sql)
    conn.commit()
    return conn

def get_view_columns(conn, view_name):
    """Returns column names for a given view/table."""
    cursor = conn.cursor()
    cursor.execute(f"PRAGMA table_info({view_name});")
    columns = [row[1] for row in cursor.fetchall()]
    return columns

def fetch_all_rows(conn, query):
    """Executes a query and returns all fetched tuple rows."""
    cursor = conn.cursor()
    cursor.execute(query)
    return cursor.fetchall()

def assert_view_exists(conn, view_name):
    """Verifies that the requested view exists in the database."""
    cursor = conn.cursor()
    cursor.execute(
        "SELECT type, name FROM sqlite_master WHERE type IN ('view', 'table') AND name = ?;",
        (view_name,)
    )
    res = cursor.fetchone()
    assert res is not None, f"View or table '{view_name}' does not exist."
