import sqlite3
from typing import List, Tuple, Optional

DEFAULT_SAMPLE_DATA = [
    (1, 'alice_admin', 'ADMIN', 'IT', 5, 1, 0, 1),
    (2, 'bob_sec', 'SECURITY', 'Security', 4, 1, 0, 1),
    (3, 'charlie_dev', 'DEVELOPER', 'Engineering', 3, 1, 0, 1),
    (4, 'diana_blocked_sec', 'SECURITY', 'Security', 5, 1, 1, 1),
    (5, 'eve_nomfa_dev', 'DEVELOPER', 'Engineering', 3, 0, 0, 1),
    (6, 'frank_guest', 'GUEST', 'HR', 1, 0, 0, 0),
    (7, 'grace_it', 'ANALYST', 'IT', 4, 1, 0, 1),
    (8, 'heidi_noip_sec', 'SECURITY', 'Security', 2, 0, 0, 0),
    (9, 'ivan_audit', 'AUDITOR', 'Finance', 3, 1, 0, 0),
    (10, 'judy_low_clearance', 'DEVELOPER', 'Engineering', 1, 1, 0, 1)
]

def setup_database(conn: sqlite3.Connection, rows: Optional[List[Tuple]] = None) -> None:
    cursor = conn.cursor()
    cursor.execute("DROP TABLE IF EXISTS security_acls;")
    cursor.execute("""
        CREATE TABLE security_acls (
            user_id INTEGER PRIMARY KEY,
            username TEXT NOT NULL,
            role TEXT NOT NULL,
            department TEXT NOT NULL,
            clearance_level INTEGER NOT NULL,
            mfa_enabled INTEGER NOT NULL,
            is_blocked INTEGER NOT NULL,
            ip_whitelisted INTEGER NOT NULL
        );
    """)
    data_to_insert = rows if rows is not None else DEFAULT_SAMPLE_DATA
    cursor.executemany("""
        INSERT INTO security_acls (user_id, username, role, department, clearance_level, mfa_enabled, is_blocked, ip_whitelisted)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?);
    """, data_to_insert)
    conn.commit()

def run_sql_script(sql_file_path: str, conn: sqlite3.Connection) -> None:
    with open(sql_file_path, "r", encoding="utf-8") as f:
        script = f.read()
    conn.executescript(script)
    conn.commit()

def query_view(conn: sqlite3.Connection, view_name: str) -> Tuple[List[str], List[Tuple]]:
    cursor = conn.cursor()
    cursor.execute(f"SELECT * FROM {view_name};")
    rows = cursor.fetchall()
    columns = [desc[0] for desc in cursor.description] if cursor.description else []
    return columns, rows

def run_solution_view(sql_file_path: str, view_name: str, dataset: Optional[List[Tuple]] = None) -> Tuple[List[str], List[Tuple]]:
    conn = sqlite3.connect(":memory:")
    setup_database(conn, dataset)
    run_sql_script(sql_file_path, conn)
    columns, rows = query_view(conn, view_name)
    conn.close()
    return columns, rows
