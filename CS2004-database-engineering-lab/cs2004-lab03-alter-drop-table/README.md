# CS2004 Lab 03: E-Commerce Schema Migration (ALTER & DROP TABLE)

## Overview

In this lab, you will perform database schema migration operations on an existing e-commerce SQLite database using Data Definition Language (DDL). As business requirements evolve, database schemas must adapt by introducing new attributes, refactoring column names for clarity, and retiring obsolete legacy tables without causing data loss.

---

## Initial Base Schema

Prior to executing your migration script, the database contains the following pre-existing tables:

### 1. `products` Table

| Column Name | Data Type | Constraints / Attributes | Description |
| :--- | :--- | :--- | :--- |
| `product_id` | `INTEGER` | `PRIMARY KEY AUTOINCREMENT` | Unique product identifier. |
| `product_name` | `TEXT` | `NOT NULL` | Name of the product. |
| `price` | `REAL` | `NOT NULL` | Unit price of the product. |
| `stock_quantity` | `INTEGER` | `DEFAULT 0` | Current quantity available in stock. |

### 2. `legacy_orders` Table (Deprecated)

| Column Name | Data Type | Constraints / Attributes | Description |
| :--- | :--- | :--- | :--- |
| `order_id` | `INTEGER` | `PRIMARY KEY AUTOINCREMENT` | Legacy order record identifier. |
| `customer_id` | `INTEGER` | `NOT NULL` | Customer ID associated with order. |
| `order_details` | `TEXT` | | Raw order payload text. |

---

## Migration Requirements

You must complete the SQL script in `solution.sql` to execute the following three DDL operations:

### Task 1: Add New Column (`ALTER TABLE ... ADD COLUMN`)
Alter the `products` table to add a new column named `category` with data type `TEXT`.

### Task 2: Rename Column (`ALTER TABLE ... RENAME COLUMN`)
Alter the `products` table to rename the existing column `stock_quantity` to `stock`.

### Task 3: Drop Deprecated Table (`DROP TABLE`)
Remove the deprecated `legacy_orders` table from the database schema using `DROP TABLE`.

---

## Setup & Testing

1. Edit `solution.sql` to write your DDL statements.
2. Run the public test suite locally:
   ```bash
   make test-public
   ```
   or using the convenience runner script:
   ```bash
   ./run
   ```

---

## Submission & Grading

Your submission will be evaluated on:
1. **ALTER TABLE Migration (5 pts)**: Correctly adding the `category` column (`TEXT`) and renaming `stock_quantity` to `stock` while preserving pre-existing row data in `products`.
2. **DROP TABLE Migration (5 pts)**: Completely removing the `legacy_orders` table from the database catalog.
