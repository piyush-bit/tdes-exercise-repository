import sqlite3
import math
from typing import List, Tuple, Optional

DEFAULT_SAMPLE_DATA = [
    (101, 'Alice Smith', 'Engineering', 85000.00, 12000.00, 5000.00),
    (102, 'Bob Jones', 'Marketing', 62000.00, 8500.00, 3000.00),
    (103, 'Charlie Brown', 'Finance', 95000.00, 15000.00, 7500.00),
    (104, 'Diana Prince', 'Executive', 150000.00, 25000.00, 20000.00),
    (105, 'Evan Wright', 'Operations', 48000.50, 6000.00, 0.00)
]

def setup_database(conn: sqlite3.Connection, rows: Optional[List[Tuple]] = None) -> None:
    cursor = conn.cursor()
    cursor.execute("DROP TABLE IF EXISTS employees;")
    cursor.execute("""
        CREATE TABLE employees (
            employee_id INTEGER PRIMARY KEY,
            employee_name TEXT NOT NULL,
            department TEXT NOT NULL,
            gross_salary REAL NOT NULL,
            tax REAL NOT NULL,
            bonus REAL NOT NULL
        );
    """)
    data_to_insert = rows if rows is not None else DEFAULT_SAMPLE_DATA
    cursor.executemany("""
        INSERT INTO employees (employee_id, employee_name, department, gross_salary, tax, bonus)
        VALUES (?, ?, ?, ?, ?, ?);
    """, data_to_insert)
    conn.commit()

def run_sql_query(sql_file_path: str, dataset: Optional[List[Tuple]] = None) -> Tuple[List[str], List[Tuple]]:
    conn = sqlite3.connect(":memory:")
    setup_database(conn, dataset)
    
    with open(sql_file_path, "r", encoding="utf-8") as f:
        query = f.read().strip()
        
    cursor = conn.cursor()
    cursor.execute(query)
    rows = cursor.fetchall()
    columns = [desc[0] for desc in cursor.description] if cursor.description else []
    conn.close()
    return columns, rows

def is_close(val1: float, val2: float, rel_tol: float = 1e-4, abs_tol: float = 1e-4) -> bool:
    return math.isclose(float(val1), float(val2), rel_tol=rel_tol, abs_tol=abs_tol)
