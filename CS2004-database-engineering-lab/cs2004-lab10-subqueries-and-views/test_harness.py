import sqlite3
import os
import sys

SCHEMA_DDL = """
PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS sales;
DROP TABLE IF EXISTS products;
DROP TABLE IF EXISTS employees;
DROP TABLE IF EXISTS departments;

CREATE TABLE departments (
    department_id INTEGER PRIMARY KEY,
    department_name TEXT NOT NULL,
    budget REAL NOT NULL
);

CREATE TABLE employees (
    employee_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    department_id INTEGER NOT NULL,
    salary REAL NOT NULL,
    hire_date TEXT NOT NULL,
    FOREIGN KEY (department_id) REFERENCES departments(department_id)
);

CREATE TABLE products (
    product_id INTEGER PRIMARY KEY,
    product_name TEXT NOT NULL,
    category TEXT NOT NULL,
    price REAL NOT NULL
);

CREATE TABLE sales (
    sale_id INTEGER PRIMARY KEY,
    employee_id INTEGER NOT NULL,
    product_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    sale_date TEXT NOT NULL,
    total_amount REAL NOT NULL,
    FOREIGN KEY (employee_id) REFERENCES employees(employee_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);
"""

DEFAULT_SEED_DATA = """
INSERT INTO departments (department_id, department_name, budget) VALUES
(1, 'Engineering', 150000.00),
(2, 'Sales', 120000.00),
(3, 'Marketing', 80000.00),
(4, 'Support', 50000.00);

INSERT INTO employees (employee_id, name, department_id, salary, hire_date) VALUES
(101, 'Alice Smith', 1, 95000.00, '2021-03-15'),
(102, 'Bob Jones', 1, 80000.00, '2020-06-01'),
(103, 'Charlie Brown', 2, 70000.00, '2019-11-12'),
(104, 'Diana Prince', 2, 65000.00, '2022-01-10'),
(105, 'Evan Wright', 3, 50000.00, '2023-04-20'),
(106, 'Fiona Gallagher', 4, 45000.00, '2023-08-15');

INSERT INTO products (product_id, product_name, category, price) VALUES
(201, 'Enterprise Server', 'Hardware', 5000.00),
(202, 'Cloud Subscription', 'Software', 1200.00),
(203, 'Developer Laptop', 'Hardware', 2500.00),
(204, 'Marketing Automation Suite', 'Software', 800.00),
(205, 'Technical Support Pass', 'Services', 300.00);

INSERT INTO sales (sale_id, employee_id, product_id, quantity, sale_date, total_amount) VALUES
(1, 101, 201, 2, '2024-01-15', 10000.00),
(2, 101, 203, 1, '2024-01-20', 2500.00),
(3, 102, 202, 3, '2024-02-01', 3600.00),
(4, 103, 202, 5, '2024-02-10', 6000.00),
(5, 103, 204, 2, '2024-02-15', 1600.00),
(6, 104, 204, 1, '2024-02-20', 800.00),
(7, 105, 204, 1, '2024-03-01', 800.00);
"""


def init_db(seed_sql=DEFAULT_SEED_DATA):
    """Creates an in-memory SQLite database populated with schema and seed data."""
    conn = sqlite3.connect(":memory:")
    conn.execute("PRAGMA foreign_keys = ON;")
    conn.executescript(SCHEMA_DDL)
    if seed_sql:
        conn.executescript(seed_sql)
    return conn


def load_solution(conn, sql_file="solution.sql"):
    """Executes the target SQL solution script against the SQLite database."""
    if not os.path.exists(sql_file):
        raise FileNotFoundError(f"Solution file '{sql_file}' not found.")
    with open(sql_file, "r", encoding="utf-8") as f:
        sql_script = f.read()
    conn.executescript(sql_script)


def query_view(conn, view_name):
    """Executes SELECT * FROM view_name and returns (columns, rows)."""
    cursor = conn.cursor()
    cursor.execute(f"SELECT * FROM {view_name}")
    columns = [desc[0] for desc in cursor.description]
    rows = cursor.fetchall()
    return columns, rows


def view_exists(conn, view_name):
    """Checks if a view exists in sqlite_master."""
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='view' AND name=?", (view_name,))
    return cursor.fetchone() is not None
