import sqlite3
import os
import re

SEED_DATA = [
    (1, 101, '2024-01-10', 150.00, 'PENDING', '100 Main St'),
    (2, 102, '2024-01-12', 200.50, 'SHIPPED', '200 Oak Ave'),
    (3, 103, '2024-01-15', 50.00, 'CANCELLED', '300 Pine Rd'),
    (4, 101, '2024-01-18', 320.00, 'PENDING', '100 Main St'),
    (5, 104, '2024-01-20', 45.00, 'CANCELLED', '400 Elm St')
]

def setup_db():
    """Initializes in-memory SQLite DB with orders table and seed data."""
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE orders (
            order_id INTEGER PRIMARY KEY AUTOINCREMENT,
            customer_id INTEGER NOT NULL,
            order_date TEXT NOT NULL,
            total_amount REAL NOT NULL,
            status TEXT NOT NULL,
            shipping_address TEXT NOT NULL
        );
    """)
    cursor.executemany("""
        INSERT INTO orders (order_id, customer_id, order_date, total_amount, status, shipping_address)
        VALUES (?, ?, ?, ?, ?, ?);
    """, SEED_DATA)
    conn.commit()
    return conn

def execute_solution_script(conn, sql_file_path="solution.sql"):
    """Executes the student's solution.sql script on the database connection."""
    if not os.path.exists(sql_file_path):
        raise FileNotFoundError(f"Solution script file not found: {sql_file_path}")
    with open(sql_file_path, 'r', encoding='utf-8') as f:
        sql_content = f.read()
    conn.executescript(sql_content)
    conn.commit()
    return sql_content

def clean_statement(stmt):
    """Strips comments and normalizes whitespace in an SQL statement."""
    lines = [re.sub(r'--.*$', '', line).strip() for line in stmt.split('\n')]
    return ' '.join([l for l in lines if l])

def extract_select_queries(sql_content):
    """Extracts SELECT query statements from the SQL script content."""
    raw_statements = [s.strip() for s in sql_content.split(';') if s.strip()]
    select_statements = []
    for stmt in raw_statements:
        cleaned = clean_statement(stmt)
        if cleaned.upper().startswith('SELECT'):
            select_statements.append(cleaned)
    return select_statements

def assert_insert_update_state(conn):
    """Asserts that INSERT and UPDATE operations produced the correct table state."""
    cursor = conn.cursor()
    
    # Verify customer 105 inserted record
    cursor.execute("SELECT customer_id, order_date, total_amount, status, shipping_address FROM orders WHERE customer_id = 105;")
    c105 = cursor.fetchone()
    assert c105 is not None, "INSERT failed: Order for customer 105 not found."
    assert c105[0] == 105, f"Expected customer_id 105, got {c105[0]}"
    assert c105[1] == '2024-02-01', f"Expected order_date '2024-02-01', got '{c105[1]}'"
    # Note: total_amount was 500.00, updated by 10% discount to 450.00
    assert abs(c105[2] - 450.00) < 1e-4, f"Expected total_amount 450.00 (after 10% discount on 500.00), got {c105[2]}"
    assert c105[3] == 'PENDING', f"Expected status 'PENDING', got '{c105[3]}'"
    assert c105[4] == '500 Maple Dr', f"Expected shipping_address '500 Maple Dr', got '{c105[4]}'"

    # Verify customer 102 second inserted record ('2024-02-02')
    cursor.execute("SELECT customer_id, order_date, total_amount, status, shipping_address FROM orders WHERE customer_id = 102 AND order_date = '2024-02-02';")
    c102 = cursor.fetchone()
    assert c102 is not None, "INSERT failed: Second order for customer 102 not found."
    assert abs(c102[2] - 75.25) < 1e-4, f"Expected total_amount 75.25, got {c102[2]}"
    assert c102[3] == 'PROCESSING', f"Expected status 'PROCESSING', got '{c102[3]}'"

    # Verify UPDATE 1: Order 1 status changed from PENDING to PROCESSING
    cursor.execute("SELECT status FROM orders WHERE order_id = 1;")
    o1_status = cursor.fetchone()
    assert o1_status is not None, "Order 1 not found."
    assert o1_status[0] == 'PROCESSING', f"UPDATE failed: Order 1 status expected 'PROCESSING', got '{o1_status[0]}'"

    # Verify UPDATE 2: Order 4 total_amount discounted from 320.00 to 288.00
    cursor.execute("SELECT total_amount FROM orders WHERE order_id = 4;")
    o4_amount = cursor.fetchone()
    assert o4_amount is not None, "Order 4 not found."
    assert abs(o4_amount[0] - 288.00) < 1e-4, f"UPDATE failed: Order 4 total_amount expected 288.00, got {o4_amount[0]}"

def assert_delete_select_state(conn, sql_content):
    """Asserts that DELETE and SELECT operations produced the correct states."""
    cursor = conn.cursor()

    # Verify DELETE: No CANCELLED orders remaining
    cursor.execute("SELECT COUNT(*) FROM orders WHERE status = 'CANCELLED';")
    cancelled_count = cursor.fetchone()[0]
    assert cancelled_count == 0, f"DELETE failed: Expected 0 CANCELLED orders, found {cancelled_count}"

    # Extract and run SELECT query from solution.sql
    select_queries = extract_select_queries(sql_content)
    assert len(select_queries) > 0, "SELECT failed: No SELECT statement found in solution.sql script."
    
    # Run the last SELECT query
    last_select = select_queries[-1]
    cursor.execute(last_select)
    results = cursor.fetchall()

    # Expected ordered results:
    # 1. order 6 (or order with total 450.00): customer 105, total 450.00, PENDING
    # 2. order 4: customer 101, total 288.00, PENDING
    # 3. order 2: customer 102, total 200.50, SHIPPED
    # 4. order 1: customer 101, total 150.00, PROCESSING
    # 5. order 7: customer 102, total 75.25, PROCESSING
    assert len(results) == 5, f"SELECT failed: Expected 5 active order rows, got {len(results)}"
    
    expected_totals = [450.00, 288.00, 200.50, 150.00, 75.25]
    actual_totals = [r[2] for r in results]
    for i, (exp, act) in enumerate(zip(expected_totals, actual_totals)):
        assert abs(exp - act) < 1e-4, f"SELECT failed: Row {i+1} total_amount expected {exp}, got {act}"

    expected_statuses = ['PENDING', 'PENDING', 'SHIPPED', 'PROCESSING', 'PROCESSING']
    actual_statuses = [r[3] for r in results]
    for i, (exp, act) in enumerate(zip(expected_statuses, actual_statuses)):
        assert exp == act, f"SELECT failed: Row {i+1} status expected '{exp}', got '{act}'"
