import sys
import os
import test_harness

EXPECTED_VIEWS = [
    "above_avg_salary_employees",
    "products_sold_in_high_budget_depts",
    "sales_above_dept_avg",
    "executive_sales_summary",
    "department_performance_dashboard"
]

def main():
    print("Running public tests for CS2004 Lab 10...")
    
    if not os.path.exists("solution.sql"):
        print("FAIL: solution.sql file missing.")
        sys.exit(1)
        
    try:
        conn = test_harness.init_db()
        test_harness.load_solution(conn, "solution.sql")
    except Exception as e:
        print(f"FAIL: Error executing solution.sql: {e}")
        sys.exit(1)

    # 1. Verify existence of all required views
    missing_views = []
    for v in EXPECTED_VIEWS:
        if not test_harness.view_exists(conn, v):
            missing_views.append(v)
            
    if missing_views:
        print(f"FAIL: Missing views in solution.sql: {missing_views}")
        sys.exit(1)
        
    print("✓ All 5 required views exist in database schema.")

    # 2. Check row counts for public test dataset
    view_expectations = {
        "above_avg_salary_employees": 3,
        "products_sold_in_high_budget_depts": 4,
        "sales_above_dept_avg": 2,
        "executive_sales_summary": 7,
        "department_performance_dashboard": 4
    }

    errors = []
    for view_name, expected_min_rows in view_expectations.items():
        try:
            cols, rows = test_harness.query_view(conn, view_name)
            if len(rows) != expected_min_rows:
                errors.append(f"View '{view_name}' returned {len(rows)} rows, expected {expected_min_rows}.")
            else:
                print(f"✓ View '{view_name}' returned {len(rows)} expected rows.")
        except Exception as e:
            errors.append(f"Error querying view '{view_name}': {e}")

    if errors:
        print("\nPublic Test Failures:")
        for err in errors:
            print(f"  - {err}")
        sys.exit(1)

    print("\nPASS: All public tests passed successfully!")
    sys.exit(0)

if __name__ == "__main__":
    main()
