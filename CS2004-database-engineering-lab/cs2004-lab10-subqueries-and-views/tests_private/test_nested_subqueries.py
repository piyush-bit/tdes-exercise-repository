import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
import test_harness

ALT_SEED_DATA = """
INSERT INTO departments (department_id, department_name, budget) VALUES
(1, 'R&D', 200000.00),
(2, 'Operations', 100000.00),
(3, 'HR', 60000.00);

INSERT INTO employees (employee_id, name, department_id, salary, hire_date) VALUES
(1, 'Zoe', 1, 120000.00, '2022-01-01'),
(2, 'Yash', 1, 100000.00, '2022-02-01'),
(3, 'Xander', 2, 100000.00, '2022-03-01'),
(4, 'William', 3, 50000.00, '2022-04-01');

INSERT INTO products (product_id, product_name, category, price) VALUES
(10, 'Alpha Widget', 'Gadget', 500.00),
(20, 'Beta Service', 'Service', 1000.00),
(30, 'Gamma Plan', 'Service', 1500.00);

INSERT INTO sales (sale_id, employee_id, product_id, quantity, sale_date, total_amount) VALUES
(100, 1, 10, 2, '2024-05-01', 1000.00),
(101, 1, 20, 1, '2024-05-02', 1000.00),
(102, 2, 10, 1, '2024-05-03', 500.00),
(103, 3, 30, 2, '2024-05-04', 3000.00),
(104, 4, 20, 1, '2024-05-05', 1000.00);
"""

def test_above_avg_salary():
    print("Testing Task 1: above_avg_salary_employees...")
    # Dataset 1
    conn = test_harness.init_db()
    test_harness.load_solution(conn)
    
    cols, rows = test_harness.query_view(conn, "above_avg_salary_employees")
    expected_cols = ["employee_id", "name", "department_id", "salary"]
    assert [c.lower() for c in cols] == expected_cols, f"Column mismatch for Task 1: got {cols}, expected {expected_cols}"
    
    # Overall avg salary = (95k+80k+70k+65k+50k+45k)/6 = 67500.0
    expected_rows_d1 = [
        (101, 'Alice Smith', 1, 95000.0),
        (102, 'Bob Jones', 1, 80000.0),
        (103, 'Charlie Brown', 2, 70000.0)
    ]
    assert rows == expected_rows_d1, f"Task 1 Dataset 1 failed.\nGot: {rows}\nExpected: {expected_rows_d1}"
    
    # Dataset 2 (Alternative data with tie in salary)
    conn2 = test_harness.init_db(ALT_SEED_DATA)
    test_harness.load_solution(conn2)
    cols2, rows2 = test_harness.query_view(conn2, "above_avg_salary_employees")
    # Avg salary = (120k + 100k + 100k + 50k)/4 = 92500.0
    # Employees > 92500: Zoe (120k, id 1), Yash (100k, id 2), Xander (100k, id 3)
    # Ordered by salary DESC, employee_id ASC -> Zoe (120k, 1), Yash (100k, 2), Xander (100k, 3)
    expected_rows_d2 = [
        (1, 'Zoe', 1, 120000.0),
        (2, 'Yash', 1, 100000.0),
        (3, 'Xander', 2, 100000.0)
    ]
    assert rows2 == expected_rows_d2, f"Task 1 Dataset 2 failed.\nGot: {rows2}\nExpected: {expected_rows_d2}"
    print("✓ Task 1 passed.")


def test_products_in_high_budget_depts():
    print("Testing Task 2: products_sold_in_high_budget_depts...")
    # Dataset 1
    conn = test_harness.init_db()
    test_harness.load_solution(conn)
    
    cols, rows = test_harness.query_view(conn, "products_sold_in_high_budget_depts")
    expected_cols = ["product_id", "product_name", "category"]
    assert [c.lower() for c in cols] == expected_cols, f"Column mismatch for Task 2: got {cols}, expected {expected_cols}"
    
    # High budget depts (> 100000): Dept 1 (150k), Dept 2 (120k)
    # Products sold in Dept 1 or 2: 201, 202, 203, 204
    expected_rows_d1 = [
        (201, 'Enterprise Server', 'Hardware'),
        (202, 'Cloud Subscription', 'Software'),
        (203, 'Developer Laptop', 'Hardware'),
        (204, 'Marketing Automation Suite', 'Software')
    ]
    assert rows == expected_rows_d1, f"Task 2 Dataset 1 failed.\nGot: {rows}\nExpected: {expected_rows_d1}"
    
    # Dataset 2 (Dept 2 has budget = 100000 exact -> budget > 100000 excludes Dept 2)
    conn2 = test_harness.init_db(ALT_SEED_DATA)
    test_harness.load_solution(conn2)
    cols2, rows2 = test_harness.query_view(conn2, "products_sold_in_high_budget_depts")
    # Only Dept 1 (R&D, 200k) has budget > 100000.
    # Sales in Dept 1: Products 10, 20.
    expected_rows_d2 = [
        (10, 'Alpha Widget', 'Gadget'),
        (20, 'Beta Service', 'Service')
    ]
    assert rows2 == expected_rows_d2, f"Task 2 Dataset 2 failed.\nGot: {rows2}\nExpected: {expected_rows_d2}"
    print("✓ Task 2 passed.")


def test_sales_above_dept_avg():
    print("Testing Task 3: sales_above_dept_avg...")
    # Dataset 1
    conn = test_harness.init_db()
    test_harness.load_solution(conn)
    
    cols, rows = test_harness.query_view(conn, "sales_above_dept_avg")
    expected_cols = ["sale_id", "employee_id", "product_id", "total_amount", "sale_date"]
    assert [c.lower() for c in cols] == expected_cols, f"Column mismatch for Task 3: got {cols}, expected {expected_cols}"
    
    # Dept 1 sales: 10000, 2500, 3600 -> avg = 5366.67 -> Sale 1 (10000.0)
    # Dept 2 sales: 6000, 1600, 800 -> avg = 2800.0 -> Sale 4 (6000.0)
    # Dept 3 sales: 800 -> avg = 800.0 -> none strictly greater
    expected_rows_d1 = [
        (1, 101, 201, 10000.0, '2024-01-15'),
        (4, 103, 202, 6000.0, '2024-02-10')
    ]
    assert rows == expected_rows_d1, f"Task 3 Dataset 1 failed.\nGot: {rows}\nExpected: {expected_rows_d1}"
    
    # Dataset 2
    conn2 = test_harness.init_db(ALT_SEED_DATA)
    test_harness.load_solution(conn2)
    cols2, rows2 = test_harness.query_view(conn2, "sales_above_dept_avg")
    # Dept 1 sales: 100 (1000.0), 101 (1000.0), 102 (500.0) -> avg = 833.33 -> Sales 100, 101
    # Dept 2 sales: 103 (3000.0) -> avg = 3000.0 -> none
    # Dept 3 sales: 104 (1000.0) -> avg = 1000.0 -> none
    expected_rows_d2 = [
        (100, 1, 10, 1000.0, '2024-05-01'),
        (101, 1, 20, 1000.0, '2024-05-02')
    ]
    assert rows2 == expected_rows_d2, f"Task 3 Dataset 2 failed.\nGot: {rows2}\nExpected: {expected_rows_d2}"
    print("✓ Task 3 passed.")


def main():
    print("Executing Private Tests: test_nested_subqueries")
    try:
        test_above_avg_salary()
        test_products_in_high_budget_depts()
        test_sales_above_dept_avg()
        print("ALL SUBQUERY PRIVATE TESTS PASSED!")
        sys.exit(0)
    except AssertionError as ae:
        print(f"FAIL: {ae}")
        sys.exit(1)
    except Exception as e:
        print(f"ERROR: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
