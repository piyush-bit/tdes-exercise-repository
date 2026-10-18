-- CS2004 Lab 09: Supply Chain Relational Joins - Reference Solution

-- Task 1: Inner Join - Shipped Order Details
DROP VIEW IF EXISTS v_shipped_order_details;
CREATE VIEW v_shipped_order_details AS
SELECT 
    o.order_id,
    c.company_name,
    p.product_name,
    o.quantity,
    (o.quantity * p.unit_price) AS total_price
FROM orders o
INNER JOIN customers c ON o.customer_id = c.customer_id
INNER JOIN products p ON o.product_id = p.product_id
ORDER BY o.order_id ASC;

-- Task 2: Aggregated Inner Join - Customer Order Summary
DROP VIEW IF EXISTS v_customer_order_summary;
CREATE VIEW v_customer_order_summary AS
SELECT 
    c.customer_id,
    c.company_name,
    SUM(o.quantity) AS total_quantity_ordered,
    SUM(o.quantity * p.unit_price) AS total_spent
FROM customers c
INNER JOIN orders o ON c.customer_id = o.customer_id
INNER JOIN products p ON o.product_id = p.product_id
GROUP BY c.customer_id, c.company_name
ORDER BY c.customer_id ASC;

-- Task 3: Outer Join - All Customers & Orders (LEFT JOIN)
DROP VIEW IF EXISTS v_all_customers_orders;
CREATE VIEW v_all_customers_orders AS
SELECT 
    c.customer_id,
    c.company_name,
    o.order_id,
    o.product_id,
    o.quantity
FROM customers c
LEFT JOIN orders o ON c.customer_id = o.customer_id
ORDER BY c.customer_id ASC, o.order_id ASC;

-- Task 4: Outer Join - All Products & Orders (LEFT JOIN)
DROP VIEW IF EXISTS v_all_products_orders;
CREATE VIEW v_all_products_orders AS
SELECT 
    p.product_id,
    p.product_name,
    o.order_id,
    o.quantity
FROM products p
LEFT JOIN orders o ON p.product_id = o.product_id
ORDER BY p.product_id ASC, o.order_id ASC;
