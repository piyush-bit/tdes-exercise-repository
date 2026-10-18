import sqlite3
import os

def create_db_and_execute_solution(solution_path="solution.sql"):
    """
    Initializes an in-memory SQLite database, enables foreign key constraints,
    executes the student's solution.sql script, and returns the database connection.
    """
    if not os.path.exists(solution_path):
        raise FileNotFoundError(f"Solution file '{solution_path}' not found.")
    
    conn = sqlite3.connect(":memory:")
    conn.isolation_level = None  # autocommit mode for script execution
    conn.execute("PRAGMA foreign_keys = ON;")
    
    with open(solution_path, "r", encoding="utf-8") as f:
        sql_script = f.read()
        
    conn.executescript(sql_script)
    return conn

def get_table_names(conn):
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%';")
    return [row[0] for row in cursor.fetchall()]

def get_view_names(conn):
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='view';")
    return [row[0] for row in cursor.fetchall()]

def get_table_columns(conn, table_name):
    cursor = conn.cursor()
    cursor.execute(f"PRAGMA table_info('{table_name}');")
    # returns list of (cid, name, type, notnull, dflt_value, pk)
    return {row[1]: {"type": row[2].upper(), "notnull": bool(row[3]), "dflt_value": row[4], "pk": bool(row[5])} for row in cursor.fetchall()}

def get_foreign_keys(conn, table_name):
    cursor = conn.cursor()
    cursor.execute(f"PRAGMA foreign_key_list('{table_name}');")
    # returns (id, seq, table, from, to, on_update, on_delete, match)
    return cursor.fetchall()
