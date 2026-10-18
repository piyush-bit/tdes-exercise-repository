# CS2004 Lab 05: Enterprise Payroll Tax & Salary Arithmetic Operators in SQL

## Problem Overview

As a Database Engineer at an enterprise financial services firm, you are tasked with creating SQL expressions to calculate payroll taxes, employee bonuses, and net take-home salary across company departments.

You are given an input table named `employees` with pre-populated payroll details. Your goal is to write a single SQL `SELECT` query in `solution.sql` that projects existing employee details and calculates computed columns using SQL arithmetic operators (`+`, `-`, `*`, `/`).

---

## Database Schema & Input Specifications

### Input Table: `employees`

| Column Name     | Data Type | Description                                      |
| :-------------- | :-------- | :----------------------------------------------- |
| `employee_id`   | INTEGER   | Unique primary key identifier for the employee   |
| `employee_name` | TEXT      | Full name of the employee                        |
| `department`    | TEXT      | Department name                                  |
| `gross_salary`  | REAL      | Base monthly gross salary before tax & deduction |
| `tax`           | REAL      | Standard base tax withholding                    |
| `bonus`         | REAL      | Annual performance bonus payment                 |

---

## Technical Specifications & Required Output Columns

Your SQL query must return a result set containing the original columns plus two computed columns with exact alias names:

1. **`employee_id`**: Employee ID from `employees` table.
2. **`employee_name`**: Employee full name from `employees` table.
3. **`department`**: Department from `employees` table.
4. **`gross_salary`**: Monthly gross salary.
5. **`tax`**: Base tax withholding.
6. **`bonus`**: Performance bonus.
7. **`tax_deduction`**: Calculated as `gross_salary * 0.20` (representing a 20% flat payroll tax deduction). Must be aliased as `tax_deduction`.
8. **`net_salary`**: Calculated as `gross_salary - tax + bonus`. Must be aliased as `net_salary`.

### SQL Arithmetic Rules & Expressions:
- **`tax_deduction`**: `gross_salary * 0.20 AS tax_deduction`
- **`net_salary`**: `gross_salary - tax + bonus AS net_salary`
- **Sorting**: Output records must be sorted by `employee_id ASC`.

---

## Sample Data & Expected Output

### Input Table `employees`

| employee_id | employee_name | department  | gross_salary | tax      | bonus    |
| :---------- | :------------ | :---------- | :----------- | :------- | :------- |
| 101         | Alice Smith   | Engineering | 85000.00     | 12000.00 | 5000.00  |
| 102         | Bob Jones     | Marketing   | 62000.00     | 8500.00  | 3000.00  |
| 103         | Charlie Brown | Finance     | 95000.00     | 15000.00 | 7500.00  |
| 104         | Diana Prince  | Executive   | 150000.00    | 25000.00 | 20000.00 |
| 105         | Evan Wright   | Operations  | 48000.50     | 6000.00  | 0.00     |

### Expected Query Output

| employee_id | employee_name | department  | gross_salary | tax      | bonus    | tax_deduction | net_salary |
| :---------- | :------------ | :---------- | :----------- | :------- | :------- | :------------ | :--------- |
| 101         | Alice Smith   | Engineering | 85000.00     | 12000.00 | 5000.00  | 17000.00      | 78000.00   |
| 102         | Bob Jones     | Marketing   | 62000.00     | 8500.00  | 3000.00  | 12400.00      | 56500.00   |
| 103         | Charlie Brown | Finance     | 95000.00     | 15000.00 | 7500.00  | 19000.00      | 87500.00   |
| 104         | Diana Prince  | Executive   | 150000.00    | 25000.00 | 20000.00 | 30000.00      | 145000.00  |
| 105         | Evan Wright   | Operations  | 48000.50     | 6000.00  | 0.00     | 9600.10       | 42000.50   |

---

## Submission & Verification

- Edit `solution.sql` to implement your SQL query.
- Test your query locally:
  ```bash
  make test-public
  # OR
  ./run
  ```
- Clean build temporary files:
  ```bash
  make clean
  ```
