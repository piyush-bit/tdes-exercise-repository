import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
import test_harness

ALT_SEED_DATA = """
INSERT INTO departments (department_id, department_name, budget) VALUES
(1, 'R&D', 200000.00),
(2, 'Operations', 100000.00),
(3, 'HR', 60000.00),
(4, 'Legal', 90000.00);

INSERT INTO employees (employee_id, name, department_id, salary, hire_date) VALUES
(1, 'Zoe', 1, 120000.00, '2022-01-01'),
(2, 'Yash', 1, 100000.00, '2022-02-01'),
(3, 'Xander', 2, 100000.00, '2022-03-01');
-- Note: Dept 3 (HR) and Dept 4 (Legal) have 0 employees

INSERT INTO products (product_id, product_name, category, price) VALUES
(10, 'Alpha Widget', 'Gadget', 500.00),
(20, 'Beta Service', 'Service', 1000.00);

INSERT INTO sales (sale_id, employee_id, product_id, quantity, sale_date, total_amount) VALUES
(100, 1, 10, 2, '2024-05-01', 1000.00),
(101, 2, 20, 1, '2024-05-02', 1000.00);
"""

def test_executive_sales_summary():
    print("Testing Task 4: executive_sales_summary...")
    conn = test_harness.init_db()
    test_harness.load_solution(conn)
    
    cols, rows = test_harness.query_view(conn, "executive_sales_summary")
    expected_cols = [
        "sale_id", "employee_name", "department_name", "product_name",
        "category", "quantity", "total_amount", "sale_date"
    ]
    assert [c.lower() for c in cols] == expected_cols, f"Column mismatch for Task 4: got {cols}, expected {expected_cols}"
    
    expected_rows_d1 = [
        (7, 'Evan Wright', 'Marketing', 'Marketing Automation Suite', 'Software', 1, 800.0, '2024-03-01'),
        (6, 'Diana Prince', 'Sales', 'Marketing Automation Suite', 'Software', 1, 800.0, '2024-02-20'),
        (5, 'Charlie Brown', 'Sales', 'Marketing Automation Suite', 'Software', 2, 1600.0, '2024-02-15'),
        (4, 'Charlie Brown', 'Sales', 'Cloud Subscription', 'Software', 5, 6000.0, '2024-02-10'),
        (3, 'Bob Jones', 'Engineering', 'Cloud Subscription', 'Software', 3, 3600.0, '2024-02-01'),
        (2, 'Alice Smith', 'Engineering', 'Developer Laptop', 'Hardware', 1, 2500.0, '2024-01-20'),
        (1, 'Alice Smith', 'Engineering', 'Enterprise Server', 'Hardware', 2, 10000.0, '2024-01-15')
    ]
    assert len(rows) == len(expected_rows_d1), f"Row count mismatch: got {len(rows)}, expected {len(expected_rows_d1)}"
    for r_actual, r_exp in zip(rows, expected_rows_d1):
        assert r_actual == r_exp, f"Mismatch in row:\nGot: {r_actual}\nExpected: {r_exp}"
    print("✓ Task 4 passed.")


def test_department_performance_dashboard():
    print("Testing Task 5: department_performance_dashboard...")
    # Dataset 1
    conn = test_harness.init_db()
    test_harness.load_solution(conn)
    
    cols, rows = test_harness.query_view(conn, "department_performance_dashboard")
    expected_cols = [
        "department_id", "department_name", "total_employees",
        "total_sales_count", "total_revenue", "avg_sale_amount"
    ]
    assert [c.lower() for c in cols] == expected_cols, f"Column mismatch for Task 5: got {cols}, expected {expected_cols}"
    
    assert len(rows) == 4, f"Expected 4 departments in dashboard, got {len(rows)}"
    
    # Check Dept 1 (Engineering)
    r1 = rows[0]
    assert r1[0] == 1 and r1[1] == 'Engineering', f"Expected top dept Engineering, got {r1[:2]}"
    assert r1[2] == 2, f"Engineering expected 2 employees, got {r1[2]}"
    assert r1[3] == 3, f"Engineering expected 3 sales, got {r1[3]}"
    assert abs(r1[4] - 16100.0) < 1e-4, f"Engineering total_revenue expected 16100.0, got {r1[4]}"
    assert abs(r1[5] - (16100.0 / 3)) < 1e-4, f"Engineering avg_sale_amount expected {16100.0/3}, got {r1[5]}"
    
    # Check Dept 4 (Support - 0 sales)
    r4 = rows[3]
    assert r4[0] == 4 and r4[1] == 'Support', f"Expected bottom dept Support, got {r4[:2]}"
    assert r4[2] == 1, f"Support expected 1 employee, got {r4[2]}"
    assert r4[3] == 0, f"Support expected 0 sales, got {r4[3]}"
    assert r4[4] == 0.0, f"Support expected total_revenue 0.0, got {r4[4]}"
    assert r4[5] == 0.0, f"Support expected avg_sale_amount 0.0, got {r4[5]}"
    
    # Dataset 2 (Testing departments with 0 employees and 0 sales)
    conn2 = test_harness.init_db(ALT_SEED_DATA)
    test_harness.load_solution(conn2)
    cols2, rows2 = test_harness.query_view(conn2, "department_performance_dashboard")
    assert len(rows2) == 4, f"Expected 4 departments in Dataset 2 dashboard, got {len(rows2)}"
    
    # R&D has total_revenue = 2000.0 (sales 100 & 101)
    # Operations has 0 sales -> revenue 0.0, total_employees = 1
    # HR has 0 employees, 0 sales -> revenue 0.0, total_employees = 0
    # Legal has 0 employees, 0 sales -> revenue 0.0, total_employees = 0
    depts_dict = {r[0]: r for r in rows2}
    assert depts_dict[1][4] == 2000.0, f"R&D revenue expected 2000.0, got {depts_dict[1][4]}"
    assert depts_dict[3][2] == 0 and depts_dict[3][4] == 0.0, f"HR expected 0 employees & 0.0 revenue, got {depts_dict[3]}"
    assert depts_dict[4][2] == 0 and depts_dict[4][4] == 0.0, f"Legal expected 0 employees & 0.0 revenue, got {depts_dict[4]}"
    print("✓ Task 5 passed.")


def main():
    print("Executing Private Tests: test_reporting_views")
    try:
        test_executive_sales_summary()
        test_department_performance_dashboard()
        print("ALL REPORTING VIEW PRIVATE TESTS PASSED!")
        sys.exit(0)
    except AssertionError as ae:
        print(f"FAIL: {ae}")
        sys.exit(1)
    except Exception as e:
        print(f"ERROR: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
