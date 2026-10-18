import os
import sqlite3

DEFAULT_RECORDS = [
    (101, 'Alice', 'Smith', 45, 'F', 1, 'Severe Chest Pain', 115, 145, 92, 37.2, 'AMB'),
    (102, 'Bob', 'Jones', 68, 'M', 3, 'Shortness of Breath', 95, 130, 94, 36.8, 'WALK'),
    (103, 'Charlie', 'Brown', 12, 'M', 2, 'High Fever', 105, 110, 98, 39.1, 'WALK'),
    (104, 'Diana', 'Prince', 29, 'F', 4, 'Sprained Ankle', 72, 118, 99, 36.6, 'WALK'),
    (105, 'Evan', 'Wright', 75, 'M', 1, 'Cardiac Arrest', 140, 85, 88, 35.2, 'AMB'),
    (106, 'Fiona', 'Gallagher', 52, 'F', 3, 'Abdominal Pain', 88, 125, 97, 37.0, 'XFER'),
    (107, 'George', 'Clark', 65, 'M', 2, 'Acute Stroke Symptoms', 102, 160, 95, 36.9, 'AMB'),
    (108, 'Hannah', 'Abbott', 5, 'F', 3, 'Persistent Cough', 98, 105, 96, 38.0, 'WALK'),
    (109, 'Ian', 'Malcolm', 50, 'M', 5, 'Prescription Refill', 68, 120, 99, 36.5, 'WALK'),
    (110, 'Julia', 'Roberts', 17, 'F', 2, 'Allergic Reaction', 85, 115, 93, 37.1, 'AMB'),
    (111, 'Kevin', 'Bacon', 82, 'M', 1, 'Unresponsive', 48, 78, 85, 34.9, 'AMB'),
    (112, 'Laura', 'Croft', 34, 'F', 4, 'Laceration on Hand', 78, 122, 98, 36.7, 'WALK'),
    (113, 'Michael', 'Scott', 42, 'M', 3, 'Migraine', 108, 138, 97, 37.4, 'WALK'),
    (114, 'Nora', 'Jones', 70, 'F', 2, 'Hypertensive Crisis', 92, 185, 96, 36.8, 'XFER'),
    (115, 'Oscar', 'Isaac', 12, 'M', 4, 'Mild Asthma Flare', 112, 115, 94, 37.0, 'WALK')
]


def create_database(records=None):
    """
    Initializes an in-memory SQLite database and populates patient_triage.
    """
    if records is None:
        records = DEFAULT_RECORDS

    conn = sqlite3.connect(":memory:")
    cursor = conn.cursor()

    cursor.execute("""
        CREATE TABLE patient_triage (
            patient_id INTEGER PRIMARY KEY,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            age INTEGER NOT NULL,
            gender TEXT NOT NULL,
            triage_level INTEGER NOT NULL,
            chief_complaint TEXT NOT NULL,
            heart_rate INTEGER NOT NULL,
            systolic_bp INTEGER NOT NULL,
            oxygen_stat INTEGER NOT NULL,
            body_temp REAL NOT NULL,
            arrival_code TEXT NOT NULL
        );
    """)

    cursor.executemany("""
        INSERT INTO patient_triage (
            patient_id, first_name, last_name, age, gender, triage_level,
            chief_complaint, heart_rate, systolic_bp, oxygen_stat, body_temp, arrival_code
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    """, records)

    conn.commit()
    return conn


def extract_query(sql_file_path, task_id):
    """
    Extracts the SQL query string for a specific task_id from sql_file_path.
    """
    if not os.path.exists(sql_file_path):
        raise FileNotFoundError(f"SQL file not found at: {sql_file_path}")

    with open(sql_file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    start_marker = f"-- TASK_{task_id}_START"
    end_marker = f"-- TASK_{task_id}_END"

    if start_marker not in content or end_marker not in content:
        raise ValueError(f"Task markers {start_marker} and/or {end_marker} not found in {sql_file_path}")

    block = content.split(start_marker)[1].split(end_marker)[0]

    clean_lines = []
    for line in block.splitlines():
        stripped = line.strip()
        if stripped.startswith("--"):
            continue
        clean_lines.append(line)

    query = "\n".join(clean_lines).strip()
    if not query:
        raise ValueError(f"No valid SQL query content found for Task {task_id} in {sql_file_path}")

    return query


def execute_task_query(sql_file_path, task_id, conn):
    """
    Extracts and runs query for task_id against sqlite3 connection conn.
    Returns list of result tuples.
    """
    query = extract_query(sql_file_path, task_id)
    cursor = conn.cursor()
    cursor.execute(query)
    return cursor.fetchall()
