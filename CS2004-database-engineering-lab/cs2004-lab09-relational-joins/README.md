# CS2004 Lab 09: Supply Chain Relational Joins

## Overview
In relational database systems, data is normalized across multiple entity tables to reduce redundancy and maintain data integrity. Relational joins (`INNER JOIN`, `LEFT JOIN`) enable querying across related entities by matching foreign key relationships.

In this lab, you will design SQL views to query a Supply Chain Management & Inventory Tracking database consisting of three relational tables: `customers`, `products`, and `orders`.

---

## Schema Architecture

The database contains three tables:

### 1. `customers`
| Column | Type | Constraints | Description |
| :--- | :--- | :--- | :--- |
| `customer_id` | `INTEGER` | `PRIMARY KEY` | Unique customer identifier |
| `company_name` | `TEXT` | `NOT NULL` | Registered company name |
| `contact_name` | `TEXT` | `NOT NULL` | Primary contact person |
| `city` | `TEXT` | `NOT NULL` | City location |

### 2. `products`
| Column | Type | Constraints | Description |
| :--- | :--- | :--- | :--- |
| `product_id` | `INTEGER` | `PRIMARY KEY` | Unique product SKU identifier |
| `product_name` | `TEXT` | `NOT NULL` | Product descriptive name |
| `category` | `TEXT` | `NOT NULL` | Product category |
| `unit_price` | `REAL` | `NOT NULL` | Unit price in USD |

### 3. `orders`
| Column | Type | Constraints | Description |
| :--- | :--- | :--- | :--- |
| `order_id` | `INTEGER` | `PRIMARY KEY` | Unique order transaction ID |
| `customer_id` | `INTEGER` | `FOREIGN KEY` | References `customers(customer_id)` |
| `product_id` | `INTEGER` | `FOREIGN KEY` | References `products(product_id)` |
| `quantity` | `INTEGER` | `NOT NULL` | Ordered units count |
| `order_date` | `TEXT` | `NOT NULL` | Order date (YYYY-MM-DD) |

---

## Lab Tasks

You are required to implement four SQL `CREATE VIEW` statements in `solution.sql`:

### Task 1: Inner Join - Shipped Order Details (`v_shipped_order_details`)
Create a view named `v_shipped_order_details` that combines order records with matching customer and product records using `INNER JOIN`.
- **Columns to select**:
  - `order_id` (from `orders`)
  - `company_name` (from `customers`)
  - `product_name` (from `products`)
  - `quantity` (from `orders`)
  - `total_price` (calculated as `orders.quantity * products.unit_price`)
- **Ordering**: Order the output rows by `order_id` in ascending order (`ASC`).

### Task 2: Aggregated Inner Join - Customer Summary (`v_customer_order_summary`)
Create a view named `v_customer_order_summary` that aggregates ordering history for customers who have placed at least one order.
- **Columns to select**:
  - `customer_id` (from `customers`)
  - `company_name` (from `customers`)
  - `total_quantity_ordered` (`SUM` of `orders.quantity`)
  - `total_spent` (`SUM` of `orders.quantity * products.unit_price`)
- **Condition**: Use `INNER JOIN` between `customers`, `orders`, and `products`.
- **Grouping**: Group results by `customers.customer_id` and `customers.company_name`.
- **Ordering**: Order the output rows by `customer_id` in ascending order (`ASC`).

### Task 3: Outer Join - All Customers & Orders (`v_all_customers_orders`)
Create a view named `v_all_customers_orders` that returns **all** customers, including those who have placed zero orders.
- **Columns to select**:
  - `customer_id` (from `customers`)
  - `company_name` (from `customers`)
  - `order_id` (from `orders`)
  - `product_id` (from `orders`)
  - `quantity` (from `orders`)
- **Condition**: Use `LEFT JOIN` (or `LEFT OUTER JOIN`) from `customers` to `orders`.
- **Note**: Customers with no order records will have `NULL` values for `order_id`, `product_id`, and `quantity`.
- **Ordering**: Order the output rows by `customer_id` ASC, then `order_id` ASC.

### Task 4: Outer Join - All Products & Orders (`v_all_products_orders`)
Create a view named `v_all_products_orders` that returns **all** inventory products, including those that have never been ordered.
- **Columns to select**:
  - `product_id` (from `products`)
  - `product_name` (from `products`)
  - `order_id` (from `orders`)
  - `quantity` (from `orders`)
- **Condition**: Use `LEFT JOIN` (or `LEFT OUTER JOIN`) from `products` to `orders`.
- **Note**: Products with no order records will have `NULL` values for `order_id` and `quantity`.
- **Ordering**: Order the output rows by `product_id` ASC, then `order_id` ASC.

---

## Local Verification

Run the public test suite locally to verify your implementation:

```bash
make test-public
# or
./run
```

Grading is evaluated via test targets:
- `make test-submission-inner-joins` (5 points)
- `make test-submission-outer-joins` (5 points)
