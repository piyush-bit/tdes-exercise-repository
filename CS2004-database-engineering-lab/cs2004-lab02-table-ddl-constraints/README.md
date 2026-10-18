# CS2004 Lab 02: Digital Wallet Table Schema & Constraints

## Overview

In this lab, you will design the database table schema for a digital wallet fintech application using SQLite Data Definition Language (DDL). Proper database constraints guarantee data integrity at the database layer, preventing invalid entries such as orphan wallets, duplicate account numbers, or missing mandatory attributes.

---

## Requirements

You must complete the SQL script in `solution.sql` to create a table named `user_wallets` with the exact column specifications and constraints listed below.

### Table Specification: `user_wallets`

| Column Name | Data Type | Constraints / Attributes | Description |
| :--- | :--- | :--- | :--- |
| `wallet_id` | `INTEGER` | `PRIMARY KEY AUTOINCREMENT` | Unique auto-incrementing primary key identifier for the wallet. |
| `user_id` | `INTEGER` | `NOT NULL` | The unique identifier of the user who owns the wallet. Must not be NULL. |
| `account_number` | `TEXT` | `UNIQUE`, `NOT NULL` | The account number string associated with the wallet. Must be UNIQUE and NOT NULL. |
| `balance` | `REAL` | `DEFAULT 0.00` | Current monetary balance in the wallet. Defaults to `0.00` when unspecified. |
| `currency` | `TEXT` | `DEFAULT 'USD'` | Three-letter ISO currency code. Defaults to `'USD'` when unspecified. |

---

## Setup & Testing

1. Edit `solution.sql` to write your `CREATE TABLE` DDL statement.
2. Run the public test suite locally to verify basic table creation and column setup:
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
1. **Table Structure (5 pts)**: Correct table name (`user_wallets`), columns (`wallet_id`, `user_id`, `account_number`, `balance`, `currency`), data types, and default values (`balance = 0.00`, `currency = 'USD'`).
2. **Constraints Validation (5 pts)**: Strict enforcement of `PRIMARY KEY`, `NOT NULL` on `user_id` & `account_number`, and `UNIQUE` constraint on `account_number`.
