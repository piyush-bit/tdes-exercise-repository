# CS2004 Lab 10: Executive Dashboard Subqueries & Reporting Views

## Overview
In this lab, you will master advanced SQL techniques for querying corporate databases:
1. **Scalar Subqueries**: Using single-value subquery expressions inside `WHERE` filtering clauses.
2. **Set Comparison Subqueries (`IN`)**: Filtering records based on membership in a nested query result set.
3. **Correlated Subqueries**: Authoring nested subqueries that evaluate dynamically per row of the outer query.
4. **Reporting Views (`CREATE VIEW`)**: Constructing reusable virtual tables to power executive dashboards and department analytics.

---

## Database Schema
The database models an enterprise organization with four key tables:

```
+------------------+       +------------------+
|   departments    |       |    employees     |
+------------------+       +------------------+
| department_id PK |<------| employee_id  PK  |
| department_name  |       | name             |
| budget           |       | department_id FK |
+------------------+       | salary           |
                           | hire_date        |
                           +------------------+
                                    ^
                                    |
+------------------+       +------------------+
|     products     |       |      sales       |
+------------------+       +------------------+
| product_id    PK |<------| sale_id      PK  |
| product_name     |       | employee_id  FK  |
| category         |       | product_id   FK  |
| price            |       | quantity         |
+------------------+       | sale_date        |
                           | total_amount     |
                           +------------------+
```

### Table Definitions
- **`departments`**: `department_id` (INTEGER, PK), `department_name` (TEXT), `budget` (REAL)
- **`employees`**: `employee_id` (INTEGER, PK), `name` (TEXT), `department_id` (INTEGER, FK), `salary` (REAL), `hire_date` (TEXT)
- **`products`**: `product_id` (INTEGER, PK), `product_name` (TEXT), `category` (TEXT), `price` (REAL)
- **`sales`**: `sale_id` (INTEGER, PK), `employee_id` (INTEGER, FK), `product_id` (INTEGER, FK), `quantity` (INTEGER), `sale_date` (TEXT), `total_amount` (REAL)

---

## Tasks & Specifications

All your SQL views must be written in [`solution.sql`](file:///Users/piyush/Developer/tdes-exercise-repository/CS2004-database-engineering-lab/cs2004-lab10-subqueries-and-views/solution.sql).

### Task 1: Scalar Subquery (`above_avg_salary_employees`)
Create a view named **`above_avg_salary_employees`** that identifies high-earning staff.
- **Columns**: `employee_id`, `name`, `department_id`, `salary`
- **Filter**: Employees whose `salary` is strictly greater (`>`) than the overall average salary across all employees.
- **Ordering**: `salary` DESC, `employee_id` ASC.

### Task 2: Subquery with `IN` (`products_sold_in_high_budget_depts`)
Create a view named **`products_sold_in_high_budget_depts`** that selects top product lines.
- **Columns**: `product_id`, `product_name`, `category` (SELECT DISTINCT)
- **Filter**: Products that have been sold by employees who belong to a department with a `budget` strictly greater than `$100,000` (`budget > 100000`).
- **Ordering**: `product_id` ASC.

### Task 3: Correlated Subquery (`sales_above_dept_avg`)
Create a view named **`sales_above_dept_avg`** that highlights standout individual transactions.
- **Columns**: `sale_id`, `employee_id`, `product_id`, `total_amount`, `sale_date`
- **Filter**: Sales records where `total_amount` is strictly greater (`>`) than the average `total_amount` of all sales made within that employee's department.
- **Ordering**: `sale_id` ASC.

### Task 4: Executive Reporting View (`executive_sales_summary`)
Create a view named **`executive_sales_summary`** that joins all entity details into a flat reporting feed.
- **Columns**:
  1. `sale_id`
  2. `employee_name` (from `employees.name`)
  3. `department_name` (from `departments.department_name`)
  4. `product_name` (from `products.product_name`)
  5. `category` (from `products.category`)
  6. `quantity`
  7. `total_amount`
  8. `sale_date`
- **Ordering**: `sale_date` DESC, `sale_id` ASC.

### Task 5: Department Performance Reporting View (`department_performance_dashboard`)
Create a view named **`department_performance_dashboard`** for high-level management metrics.
- **Columns**:
  1. `department_id`
  2. `department_name`
  3. `total_employees` (COUNT of distinct employees assigned to the department)
  4. `total_sales_count` (COUNT of sales records associated with the department's employees)
  5. `total_revenue` (SUM of `total_amount` for sales in the department; must return `0.0` if no sales exist)
  6. `avg_sale_amount` (AVG of `total_amount` for sales in the department; must return `0.0` if no sales exist)
- **Requirement**: Must use `LEFT JOIN` so that all departments (including departments with zero employees or zero sales) are present in the output. Use `COALESCE` to output `0.0` instead of `NULL` for revenue and average metrics.
- **Grouping**: Group by `department_id`, `department_name`.
- **Ordering**: `total_revenue` DESC, `department_id` ASC.

---

## Testing & Verification

Run the public test suite locally using Make or the `run` wrapper script:

```bash
# Using make:
make test-public

# Using run script:
./run
```

Grading runs automatically against hidden evaluation test suites when submitted.
