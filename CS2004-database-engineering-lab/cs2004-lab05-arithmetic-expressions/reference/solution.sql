-- Reference Solution for CS2004 Lab 05: Enterprise Payroll Tax & Salary Calculator

SELECT
    employee_id,
    employee_name,
    department,
    gross_salary,
    tax,
    bonus,
    gross_salary * 0.20 AS tax_deduction,
    gross_salary - tax + bonus AS net_salary
FROM employees
ORDER BY employee_id ASC;
