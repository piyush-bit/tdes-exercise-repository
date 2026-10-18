import sqlite3
import os

def init_db(sql_file_path: str = "solution.sql") -> sqlite3.Connection:
    """
    Creates an in-memory SQLite connection and executes the DDL script.
    """
    if not os.path.exists(sql_file_path):
        raise FileNotFoundError(f"Target SQL file does not exist: {sql_file_path}")
    
    conn = sqlite3.connect(":memory:")
    with open(sql_file_path, "r", encoding="utf-8") as f:
        sql_content = f.read()
    
    conn.executescript(sql_content)
    return conn

def get_table_columns(conn: sqlite3.Connection, table_name: str = "user_wallets") -> dict:
    """
    Retrieves PRAGMA table_info for the specified table.
    Returns dict mapping column name -> {cid, name, type, notnull, default, pk}
    """
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

def assert_table_exists(conn: sqlite3.Connection, table_name: str = "user_wallets"):
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name=?;", (table_name,))
    row = cursor.fetchone()
    if not row:
        raise AssertionError(f"Table '{table_name}' does not exist in the database.")

def assert_table_structure(conn: sqlite3.Connection):
    """
    Validates column existence, data types, and default values for user_wallets.
    """
    assert_table_exists(conn, "user_wallets")
    columns = get_table_columns(conn, "user_wallets")
    
    required_cols = {"wallet_id", "user_id", "account_number", "balance", "currency"}
    missing = required_cols - set(columns.keys())
    if missing:
        raise AssertionError(f"Table 'user_wallets' is missing required columns: {missing}")

    # Check wallet_id is primary key
    if not columns["wallet_id"]["pk"]:
        raise AssertionError("Column 'wallet_id' must be configured as PRIMARY KEY.")

    # Check defaults by inserting a minimal row
    cursor = conn.cursor()
    cursor.execute("INSERT INTO user_wallets (user_id, account_number) VALUES (?, ?);", (1, "ACC_DEFAULT_TEST"))
    conn.commit()

    cursor.execute("SELECT balance, currency FROM user_wallets WHERE account_number = ?;", ("ACC_DEFAULT_TEST",))
    row = cursor.fetchone()
    if not row:
        raise AssertionError("Failed to retrieve inserted row to verify default values.")
    
    balance, currency = row
    if float(balance) != 0.0:
        raise AssertionError(f"Expected default balance to be 0.00, got: {balance}")
    if currency != "USD":
        raise AssertionError(f"Expected default currency to be 'USD', got: '{currency}'")

def assert_constraints_validation(conn: sqlite3.Connection):
    """
    Validates NOT NULL on user_id and account_number, UNIQUE on account_number, and PRIMARY KEY uniqueness.
    """
    assert_table_exists(conn, "user_wallets")
    cursor = conn.cursor()

    # 1. Test NOT NULL on user_id
    try:
        cursor.execute("INSERT INTO user_wallets (user_id, account_number) VALUES (NULL, 'ACC_NOT_NULL_1');")
        conn.commit()
        raise AssertionError("Inserting NULL into 'user_id' should have raised sqlite3.IntegrityError.")
    except sqlite3.IntegrityError:
        pass  # Expected constraint violation

    # 2. Test NOT NULL on account_number
    try:
        cursor.execute("INSERT INTO user_wallets (user_id, account_number) VALUES (100, NULL);")
        conn.commit()
        raise AssertionError("Inserting NULL into 'account_number' should have raised sqlite3.IntegrityError.")
    except sqlite3.IntegrityError:
        pass  # Expected constraint violation

    # 3. Test UNIQUE constraint on account_number
    cursor.execute("INSERT INTO user_wallets (user_id, account_number) VALUES (101, 'ACC_UNIQUE_TEST');")
    conn.commit()

    try:
        cursor.execute("INSERT INTO user_wallets (user_id, account_number) VALUES (102, 'ACC_UNIQUE_TEST');")
        conn.commit()
        raise AssertionError("Inserting duplicate 'account_number' should have raised sqlite3.IntegrityError.")
    except sqlite3.IntegrityError:
        pass  # Expected constraint violation

    # 4. Test PRIMARY KEY constraint on wallet_id
    cursor.execute("INSERT INTO user_wallets (wallet_id, user_id, account_number) VALUES (999, 103, 'ACC_PK_TEST_1');")
    conn.commit()

    try:
        cursor.execute("INSERT INTO user_wallets (wallet_id, user_id, account_number) VALUES (999, 104, 'ACC_PK_TEST_2');")
        conn.commit()
        raise AssertionError("Inserting duplicate 'wallet_id' primary key should have raised sqlite3.IntegrityError.")
    except sqlite3.IntegrityError:
        pass  # Expected constraint violation
