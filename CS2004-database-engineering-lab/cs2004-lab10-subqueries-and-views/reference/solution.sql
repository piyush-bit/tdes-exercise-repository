-- CS2004 Lab 10 Reference Solution
-- Executive Dashboard Subqueries & Reporting Views

-- Task 1: Scalar Subquery
DROP VIEW IF EXISTS above_avg_salary_employees;
CREATE VIEW above_avg_salary_employees AS
SELECT employee_id, name, department_id, salary
FROM employees
WHERE salary > (SELECT AVG(salary) FROM employees)
ORDER BY salary DESC, employee_id ASC;

-- Task 2: IN / NOT IN Subquery
DROP VIEW IF EXISTS products_sold_in_high_budget_depts;
CREATE VIEW products_sold_in_high_budget_depts AS
SELECT DISTINCT p.product_id, p.product_name, p.category
FROM products p
WHERE p.product_id IN (
    SELECT s.product_id
    FROM sales s
    JOIN employees e ON s.employee_id = e.employee_id
    WHERE e.department_id IN (
        SELECT d.department_id
        FROM departments d
        WHERE d.budget > 100000
    )
)
ORDER BY p.product_id ASC;

-- Task 3: Correlated / Nested WHERE Subquery
DROP VIEW IF EXISTS sales_above_dept_avg;
CREATE VIEW sales_above_dept_avg AS
SELECT s.sale_id, s.employee_id, s.product_id, s.total_amount, s.sale_date
FROM sales s
JOIN employees e ON s.employee_id = e.employee_id
WHERE s.total_amount > (
    SELECT AVG(s2.total_amount)
    FROM sales s2
    JOIN employees e2 ON s2.employee_id = e2.employee_id
    WHERE e2.department_id = e.department_id
)
ORDER BY s.sale_id ASC;

-- Task 4: Executive Reporting View
DROP VIEW IF EXISTS executive_sales_summary;
CREATE VIEW executive_sales_summary AS
SELECT 
    s.sale_id,
    e.name AS employee_name,
    d.department_name,
    p.product_name,
    p.category,
    s.quantity,
    s.total_amount,
    s.sale_date
FROM sales s
JOIN employees e ON s.employee_id = e.employee_id
JOIN departments d ON e.department_id = d.department_id
JOIN products p ON s.product_id = p.product_id
ORDER BY s.sale_date DESC, s.sale_id ASC;

-- Task 5: Department Performance Reporting View
DROP VIEW IF EXISTS department_performance_dashboard;
CREATE VIEW department_performance_dashboard AS
SELECT 
    d.department_id,
    d.department_name,
    COUNT(DISTINCT e.employee_id) AS total_employees,
    COUNT(s.sale_id) AS total_sales_count,
    COALESCE(SUM(s.total_amount), 0.0) AS total_revenue,
    COALESCE(AVG(s.total_amount), 0.0) AS avg_sale_amount
FROM departments d
LEFT JOIN employees e ON d.department_id = e.department_id
LEFT JOIN sales s ON e.employee_id = s.employee_id
GROUP BY d.department_id, d.department_name
ORDER BY total_revenue DESC, d.department_id ASC;
