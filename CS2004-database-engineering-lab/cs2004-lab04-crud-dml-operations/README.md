# CS2004 Lab 04: E-Commerce Order Fulfillment DML Pipeline

## Overview
In this lab, you will author SQL Data Manipulation Language (DML) statements to perform CRUD (Create, Read, Update, Delete) operations on an E-Commerce Order Fulfillment database.

Your SQL statements will execute sequentially on a pre-populated SQLite database table named `orders`.

---

## Database Schema

The `orders` table is defined as follows:

```sql
CREATE TABLE orders (
    order_id INTEGER PRIMARY KEY AUTOINCREMENT,
    customer_id INTEGER NOT NULL,
    order_date TEXT NOT NULL,          -- ISO-8601 format: 'YYYY-MM-DD'
    total_amount REAL NOT NULL,
    status TEXT NOT NULL,              -- e.g. 'PENDING', 'PROCESSING', 'SHIPPED', 'CANCELLED'
    shipping_address TEXT NOT NULL
);
```

### Initial Seed Data

Prior to executing your `solution.sql`, the database contains the following 5 records:

| order_id | customer_id | order_date | total_amount | status | shipping_address |
|---|---|---|---|---|---|
| 1 | 101 | 2024-01-10 | 150.00 | PENDING | 100 Main St |
| 2 | 102 | 2024-01-12 | 200.50 | SHIPPED | 200 Oak Ave |
| 3 | 103 | 2024-01-15 | 50.00 | CANCELLED | 300 Pine Rd |
| 4 | 101 | 2024-01-18 | 320.00 | PENDING | 100 Main St |
| 5 | 104 | 2024-01-20 | 45.00 | CANCELLED | 400 Elm St |

---

## Tasks & Requirements

Write your SQL queries inside `solution.sql`.

### Task 1: INSERT Operations
Insert the following two new order records into the `orders` table:
1. `customer_id`: `105`, `order_date`: `'2024-02-01'`, `total_amount`: `500.00`, `status`: `'PENDING'`, `shipping_address`: `'500 Maple Dr'`
2. `customer_id`: `102`, `order_date`: `'2024-02-02'`, `total_amount`: `75.25`, `status`: `'PROCESSING'`, `shipping_address`: `'200 Oak Ave'`

### Task 2: UPDATE Operations
Execute the following updates on the `orders` table:
1. Update `status` to `'PROCESSING'` for all orders where `status` is `'PENDING'` and `order_date` is on or before `'2024-01-15'`.
2. Apply a 10% discount to `total_amount` (`total_amount = total_amount * 0.90`) for all orders where `total_amount` is greater than `300.00`.

### Task 3: DELETE Operations
1. Delete all records from `orders` where `status` is `'CANCELLED'`.

### Task 4: SELECT Operation
Execute a query retrieving order details:
1. Select columns `order_id`, `customer_id`, `total_amount`, and `status` from `orders` where `status` is NOT `'CANCELLED'`.
2. Order the resulting rows by `total_amount` in **DESCENDING** order, breaking ties by `order_id` in **ASCENDING** order.

---

## Verification

To run tests locally:

```bash
make test-public
# or
./run public
```
