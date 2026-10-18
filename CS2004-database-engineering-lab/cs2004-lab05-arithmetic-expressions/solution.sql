-- CS2004 Lab 05: Enterprise Payroll Tax & Salary Calculator
-- Write your SQL SELECT query below using arithmetic expressions and column aliases.

-- TODO: Select employee_id, employee_name, department, gross_salary, tax, bonus,
--       and compute:
--       1. gross_salary * 0.20 AS tax_deduction
--       2. gross_salary - tax + bonus AS net_salary
--       from the employees table ordered by employee_id ASC.

SELECT
    employee_id
FROM employees;
