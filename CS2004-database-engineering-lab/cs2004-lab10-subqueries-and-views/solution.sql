-- CS2004 Lab 10: Executive Dashboard Subqueries & Reporting Views
-- Author your SQL view definitions below.

-- Task 1: Scalar Subquery
-- Create a view named 'above_avg_salary_employees' selecting employee_id, name, department_id, salary
-- for employees earning strictly more than the overall average salary across all employees.
-- Order by salary DESC, employee_id ASC.
-- TODO: Implement view above_avg_salary_employees
DROP VIEW IF EXISTS above_avg_salary_employees;
CREATE VIEW above_avg_salary_employees AS
SELECT NULL AS employee_id, '' AS name, NULL AS department_id, 0.0 AS salary WHERE 0;

-- Task 2: IN / NOT IN Subquery
-- Create a view named 'products_sold_in_high_budget_depts' selecting distinct product_id, product_name, category
-- for products sold by employees in departments with budget > 100000.
-- Order by product_id ASC.
-- TODO: Implement view products_sold_in_high_budget_depts
DROP VIEW IF EXISTS products_sold_in_high_budget_depts;
CREATE VIEW products_sold_in_high_budget_depts AS
SELECT NULL AS product_id, '' AS product_name, '' AS category WHERE 0;

-- Task 3: Correlated / Nested WHERE Subquery
-- Create a view named 'sales_above_dept_avg' selecting sale_id, employee_id, product_id, total_amount, sale_date
-- for sales where total_amount is strictly greater than the average total_amount of sales in the same department.
-- Order by sale_id ASC.
-- TODO: Implement view sales_above_dept_avg
DROP VIEW IF EXISTS sales_above_dept_avg;
CREATE VIEW sales_above_dept_avg AS
SELECT NULL AS sale_id, NULL AS employee_id, NULL AS product_id, 0.0 AS total_amount, '' AS sale_date WHERE 0;

-- Task 4: Executive Reporting View
-- Create a view named 'executive_sales_summary' joining sales, employees, departments, products.
-- Columns: sale_id, employee_name, department_name, product_name, category, quantity, total_amount, sale_date.
-- Order by sale_date DESC, sale_id ASC.
-- TODO: Implement view executive_sales_summary
DROP VIEW IF EXISTS executive_sales_summary;
CREATE VIEW executive_sales_summary AS
SELECT NULL AS sale_id, '' AS employee_name, '' AS department_name, '' AS product_name, '' AS category, 0 AS quantity, 0.0 AS total_amount, '' AS sale_date WHERE 0;

-- Task 5: Department Performance Reporting View
-- Create a view named 'department_performance_dashboard' summarizing each department.
-- Columns: department_id, department_name, total_employees, total_sales_count, total_revenue, avg_sale_amount.
-- Must include departments with zero sales (total_revenue=0.0, avg_sale_amount=0.0).
-- Order by total_revenue DESC, department_id ASC.
-- TODO: Implement view department_performance_dashboard
DROP VIEW IF EXISTS department_performance_dashboard;
CREATE VIEW department_performance_dashboard AS
SELECT NULL AS department_id, '' AS department_name, 0 AS total_employees, 0 AS total_sales_count, 0.0 AS total_revenue, 0.0 AS avg_sale_amount WHERE 0;
