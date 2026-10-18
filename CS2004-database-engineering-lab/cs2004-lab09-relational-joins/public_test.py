#!/usr/bin/env python3
import sys
import test_harness

def main():
    print("Running public SQL relational join tests...")
    try:
        conn = test_harness.setup_database("solution.sql")
    except Exception as e:
        print(f"FAILED: Error executing solution.sql setup: {e}")
        sys.exit(1)
        
    views = [
        "v_shipped_order_details",
        "v_customer_order_summary",
        "v_all_customers_orders",
        "v_all_products_orders"
    ]
    
    missing_views = []
    for view in views:
        try:
            test_harness.assert_view_exists(conn, view)
        except AssertionError as e:
            missing_views.append(view)
            
    if missing_views:
        print(f"FAILED: The following required views are missing or incomplete: {missing_views}")
        sys.exit(1)

    # Check non-empty result for public test
    rows_shipped = test_harness.fetch_all_rows(conn, "SELECT * FROM v_shipped_order_details;")
    rows_customers = test_harness.fetch_all_rows(conn, "SELECT * FROM v_all_customers_orders;")
    
    if len(rows_shipped) == 0 or len(rows_customers) == 0:
        print("FAILED: Views returned 0 rows. Please implement the SQL join queries in solution.sql.")
        sys.exit(1)

    print("ALL PUBLIC TESTS PASSED!")
    sys.exit(0)

if __name__ == "__main__":
    main()
