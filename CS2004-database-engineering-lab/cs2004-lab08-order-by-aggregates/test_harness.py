import sqlite3
import os

SCHEMA_DDL = """
CREATE TABLE sales_regions (
    region_id INTEGER PRIMARY KEY,
    region_name TEXT NOT NULL,
    country TEXT NOT NULL
);

CREATE TABLE sales_reps (
    rep_id INTEGER PRIMARY KEY,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    region_id INTEGER NOT NULL,
    base_salary REAL NOT NULL,
    commission_rate REAL NOT NULL,
    FOREIGN KEY (region_id) REFERENCES sales_regions(region_id)
);

CREATE TABLE customers (
    customer_id INTEGER PRIMARY KEY,
    customer_name TEXT NOT NULL,
    customer_tier TEXT NOT NULL,
    region_id INTEGER NOT NULL,
    FOREIGN KEY (region_id) REFERENCES sales_regions(region_id)
);

CREATE TABLE orders (
    order_id INTEGER PRIMARY KEY,
    customer_id INTEGER NOT NULL,
    rep_id INTEGER NOT NULL,
    order_date TEXT NOT NULL,
    status TEXT NOT NULL,
    total_amount REAL NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
    FOREIGN KEY (rep_id) REFERENCES sales_reps(rep_id)
);

CREATE TABLE order_items (
    item_id INTEGER PRIMARY KEY,
    order_id INTEGER NOT NULL,
    product_category TEXT NOT NULL,
    quantity INTEGER NOT NULL,
    unit_price REAL NOT NULL,
    total_price REAL NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id)
);
"""

def seed_public_db(conn):
    cursor = conn.cursor()
    
    cursor.executemany(
        "INSERT INTO sales_regions VALUES (?, ?, ?);",
        [
            (1, 'North America', 'USA'),
            (2, 'Europe', 'UK'),
            (3, 'Asia Pacific', 'Japan')
        ]
    )
    
    cursor.executemany(
        "INSERT INTO sales_reps VALUES (?, ?, ?, ?, ?, ?);",
        [
            (101, 'Alice', 'Smith', 1, 60000.0, 0.12),
            (102, 'Bob', 'Smith', 2, 55000.0, 0.15),
            (103, 'Charlie', 'Brown', 1, 70000.0, 0.15),
            (104, 'David', 'Adams', 3, 50000.0, 0.10)
        ]
    )
    
    cursor.executemany(
        "INSERT INTO customers VALUES (?, ?, ?, ?);",
        [
            (201, 'Acme Corp', 'Platinum', 1),
            (202, 'Beta Ltd', 'Gold', 2),
            (203, 'Gamma Inc', 'Silver', 1),
            (204, 'Delta Co', 'Bronze', 3),
            (205, 'Epsilon LLC', 'Gold', 2)
        ]
    )
    
    cursor.executemany(
        "INSERT INTO orders VALUES (?, ?, ?, ?, ?, ?);",
        [
            (1001, 201, 101, '2026-01-10', 'COMPLETED', 1500.00),
            (1002, 202, 102, '2026-01-12', 'COMPLETED', 800.00),
            (1003, 201, 101, '2026-01-15', 'COMPLETED', 1500.00),
            (1004, 203, 103, '2026-01-18', 'PENDING', 2500.00),
            (1005, 204, 104, '2026-01-20', 'COMPLETED', 450.00),
            (1006, 205, 102, '2026-01-22', 'COMPLETED', 1200.00),
            (1007, 202, 102, '2026-01-25', 'CANCELLED', 950.00)
        ]
    )
    
    cursor.executemany(
        "INSERT INTO order_items VALUES (?, ?, ?, ?, ?, ?);",
        [
            (1, 1001, 'Enterprise Software', 5, 200.0, 1000.0),
            (2, 1001, 'Cloud Hosting', 10, 50.0, 500.0),
            (3, 1002, 'Cloud Hosting', 8, 50.0, 400.0),
            (4, 1002, 'Hardware Support', 4, 100.0, 400.0),
            (5, 1003, 'Enterprise Software', 6, 200.0, 1200.0),
            (6, 1005, 'Hardware Support', 2, 100.0, 200.0),
            (7, 1006, 'Enterprise Software', 4, 200.0, 800.0),
            (8, 1006, 'Cloud Hosting', 8, 50.0, 400.0)
        ]
    )
    conn.commit()


def setup_database(solution_path="solution.sql", seed_fn=seed_public_db):
    conn = sqlite3.connect(":memory:")
    conn.row_factory = sqlite3.Row
    conn.executescript(SCHEMA_DDL)
    
    if seed_fn:
        seed_fn(conn)
        
    if os.path.exists(solution_path):
        with open(solution_path, "r", encoding="utf-8") as f:
            sql_script = f.read()
        conn.executescript(sql_script)
        
    return conn


def execute_view(conn, view_name):
    cursor = conn.cursor()
    cursor.execute(f"SELECT * FROM {view_name};")
    return cursor.fetchall()
