-- CS2004 Lab 09: Supply Chain Relational Joins
-- Fill in the SQL queries below to create the required views.

-- TODO: Task 1 - Implement v_shipped_order_details
-- Perform INNER JOIN between orders, customers, and products.
-- Columns: order_id, company_name, product_name, quantity, total_price
-- Order by order_id ASC.
DROP VIEW IF EXISTS v_shipped_order_details;
CREATE VIEW v_shipped_order_details AS
SELECT 
    0 AS order_id, 
    '' AS company_name, 
    '' AS product_name, 
    0 AS quantity, 
    0.0 AS total_price 
WHERE 0;

-- TODO: Task 2 - Implement v_customer_order_summary
-- Perform INNER JOIN between customers, orders, products and aggregate by customer.
-- Columns: customer_id, company_name, total_quantity_ordered, total_spent
-- Order by customer_id ASC.
DROP VIEW IF EXISTS v_customer_order_summary;
CREATE VIEW v_customer_order_summary AS
SELECT 
    0 AS customer_id, 
    '' AS company_name, 
    0 AS total_quantity_ordered, 
    0.0 AS total_spent 
WHERE 0;

-- TODO: Task 3 - Implement v_all_customers_orders
-- Perform LEFT JOIN from customers to orders.
-- Columns: customer_id, company_name, order_id, product_id, quantity
-- Order by customer_id ASC, order_id ASC.
DROP VIEW IF EXISTS v_all_customers_orders;
CREATE VIEW v_all_customers_orders AS
SELECT 
    0 AS customer_id, 
    '' AS company_name, 
    0 AS order_id, 
    0 AS product_id, 
    0 AS quantity 
WHERE 0;

-- TODO: Task 4 - Implement v_all_products_orders
-- Perform LEFT JOIN from products to orders.
-- Columns: product_id, product_name, order_id, quantity
-- Order by product_id ASC, order_id ASC.
DROP VIEW IF EXISTS v_all_products_orders;
CREATE VIEW v_all_products_orders AS
SELECT 
    0 AS product_id, 
    '' AS product_name, 
    0 AS order_id, 
    0 AS quantity 
WHERE 0;
