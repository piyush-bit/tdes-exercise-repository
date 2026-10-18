#!/usr/bin/env python3
import sys
import os

# Add parent directory to sys.path to import test_harness
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
import test_harness

def test_shipped_order_details(conn):
    print("Testing v_shipped_order_details...")
    test_harness.assert_view_exists(conn, "v_shipped_order_details")
    
    cols = test_harness.get_view_columns(conn, "v_shipped_order_details")
    expected_cols = ["order_id", "company_name", "product_name", "quantity", "total_price"]
    assert cols == expected_cols, f"Column mismatch in v_shipped_order_details. Got {cols}, expected {expected_cols}"
    
    rows = test_harness.fetch_all_rows(conn, "SELECT order_id, company_name, product_name, quantity, total_price FROM v_shipped_order_details;")
    
    expected_rows = [
        (5001, "Apex Logistics", "Industrial Pallet", 10, 450.0),
        (5002, "Apex Logistics", "Barcode Scanner", 2, 300.0),
        (5003, "Beacon Retail", "Forklift Battery", 1, 1200.0),
        (5004, "Beacon Retail", "Industrial Pallet", 5, 225.0),
        (5005, "Crestline Manufacturing", "Barcode Scanner", 4, 600.0)
    ]
    
    assert len(rows) == len(expected_rows), f"Row count mismatch in v_shipped_order_details. Got {len(rows)}, expected {len(expected_rows)}"
    
    for i, (actual, expected) in enumerate(zip(rows, expected_rows)):
        assert actual == expected, f"Row {i} mismatch in v_shipped_order_details. Got {actual}, expected {expected}"
        
    print("PASS: v_shipped_order_details")

def test_customer_order_summary(conn):
    print("Testing v_customer_order_summary...")
    test_harness.assert_view_exists(conn, "v_customer_order_summary")
    
    cols = test_harness.get_view_columns(conn, "v_customer_order_summary")
    expected_cols = ["customer_id", "company_name", "total_quantity_ordered", "total_spent"]
    assert cols == expected_cols, f"Column mismatch in v_customer_order_summary. Got {cols}, expected {expected_cols}"
    
    rows = test_harness.fetch_all_rows(conn, "SELECT customer_id, company_name, total_quantity_ordered, total_spent FROM v_customer_order_summary;")
    
    expected_rows = [
        (1, "Apex Logistics", 12, 750.0),
        (2, "Beacon Retail", 6, 1425.0),
        (3, "Crestline Manufacturing", 4, 600.0)
    ]
    
    assert len(rows) == len(expected_rows), f"Row count mismatch in v_customer_order_summary. Got {len(rows)}, expected {len(expected_rows)}"
    
    for i, (actual, expected) in enumerate(zip(rows, expected_rows)):
        assert actual == expected, f"Row {i} mismatch in v_customer_order_summary. Got {actual}, expected {expected}"
        
    print("PASS: v_customer_order_summary")

def main():
    try:
        conn = test_harness.setup_database("solution.sql")
        test_shipped_order_details(conn)
        test_customer_order_summary(conn)
        print("ALL PRIVATE INNER JOIN TESTS PASSED!")
        sys.exit(0)
    except Exception as e:
        print(f"FAILED: Private inner join tests: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
