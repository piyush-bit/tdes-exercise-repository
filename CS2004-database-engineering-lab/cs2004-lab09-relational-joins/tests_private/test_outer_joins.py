#!/usr/bin/env python3
import sys
import os

# Add parent directory to sys.path to import test_harness
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
import test_harness

def test_all_customers_orders(conn):
    print("Testing v_all_customers_orders...")
    test_harness.assert_view_exists(conn, "v_all_customers_orders")
    
    cols = test_harness.get_view_columns(conn, "v_all_customers_orders")
    expected_cols = ["customer_id", "company_name", "order_id", "product_id", "quantity"]
    assert cols == expected_cols, f"Column mismatch in v_all_customers_orders. Got {cols}, expected {expected_cols}"
    
    rows = test_harness.fetch_all_rows(conn, "SELECT customer_id, company_name, order_id, product_id, quantity FROM v_all_customers_orders;")
    
    expected_rows = [
        (1, "Apex Logistics", 5001, 101, 10),
        (1, "Apex Logistics", 5002, 103, 2),
        (2, "Beacon Retail", 5003, 102, 1),
        (2, "Beacon Retail", 5004, 101, 5),
        (3, "Crestline Manufacturing", 5005, 103, 4),
        (4, "Delta Wholesale", None, None, None),
        (5, "Echo Enterprises", None, None, None)
    ]
    
    assert len(rows) == len(expected_rows), f"Row count mismatch in v_all_customers_orders. Got {len(rows)}, expected {len(expected_rows)}"
    
    for i, (actual, expected) in enumerate(zip(rows, expected_rows)):
        assert actual == expected, f"Row {i} mismatch in v_all_customers_orders. Got {actual}, expected {expected}"
        
    # Verify explicit NULL padding for unmatched left join rows
    unmatched_rows = [r for r in rows if r[0] in (4, 5)]
    assert len(unmatched_rows) == 2, f"Expected 2 unmatched customer outer join rows, found {len(unmatched_rows)}"
    for r in unmatched_rows:
        assert r[2] is None, f"Expected order_id to be NULL for unmatched customer {r[1]}"
        assert r[3] is None, f"Expected product_id to be NULL for unmatched customer {r[1]}"
        assert r[4] is None, f"Expected quantity to be NULL for unmatched customer {r[1]}"
        
    print("PASS: v_all_customers_orders (with NULL padding verification)")

def test_all_products_orders(conn):
    print("Testing v_all_products_orders...")
    test_harness.assert_view_exists(conn, "v_all_products_orders")
    
    cols = test_harness.get_view_columns(conn, "v_all_products_orders")
    expected_cols = ["product_id", "product_name", "order_id", "quantity"]
    assert cols == expected_cols, f"Column mismatch in v_all_products_orders. Got {cols}, expected {expected_cols}"
    
    rows = test_harness.fetch_all_rows(conn, "SELECT product_id, product_name, order_id, quantity FROM v_all_products_orders;")
    
    expected_rows = [
        (101, "Industrial Pallet", 5001, 10),
        (101, "Industrial Pallet", 5004, 5),
        (102, "Forklift Battery", 5003, 1),
        (103, "Barcode Scanner", 5002, 2),
        (103, "Barcode Scanner", 5005, 4),
        (104, "Hydraulic Jack", None, None),
        (105, "Thermal Label Roll", None, None)
    ]
    
    assert len(rows) == len(expected_rows), f"Row count mismatch in v_all_products_orders. Got {len(rows)}, expected {len(expected_rows)}"
    
    for i, (actual, expected) in enumerate(zip(rows, expected_rows)):
        assert actual == expected, f"Row {i} mismatch in v_all_products_orders. Got {actual}, expected {expected}"
        
    # Verify explicit NULL padding for unmatched product outer join rows
    unmatched_products = [r for r in rows if r[0] in (104, 105)]
    assert len(unmatched_products) == 2, f"Expected 2 unmatched product outer join rows, found {len(unmatched_products)}"
    for r in unmatched_products:
        assert r[2] is None, f"Expected order_id to be NULL for unmatched product {r[1]}"
        assert r[3] is None, f"Expected quantity to be NULL for unmatched product {r[1]}"

    print("PASS: v_all_products_orders (with NULL padding verification)")

def main():
    try:
        conn = test_harness.setup_database("solution.sql")
        test_all_customers_orders(conn)
        test_all_products_orders(conn)
        print("ALL PRIVATE OUTER JOIN TESTS PASSED!")
        sys.exit(0)
    except Exception as e:
        print(f"FAILED: Private outer join tests: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
