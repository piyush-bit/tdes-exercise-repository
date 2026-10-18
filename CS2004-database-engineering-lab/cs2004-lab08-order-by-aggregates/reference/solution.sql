-- CS2004 Lab 08: Executive Revenue ORDER BY & Aggregates in SQL
-- Reference Solution Implementation

-- Query 1: q1_sorted_orders
-- Select completed orders sorted by total_amount DESCENDING, then order_date ASCENDING.
CREATE VIEW IF NOT EXISTS q1_sorted_orders AS
SELECT 
    order_id,
    customer_id,
    order_date,
    total_amount,
    status
FROM orders
WHERE status = 'COMPLETED'
ORDER BY total_amount DESC, order_date ASC;


-- Query 2: q2_rep_commission_summary
-- Select sales reps sorted by commission_rate DESCENDING, last_name ASCENDING, first_name ASCENDING.
CREATE VIEW IF NOT EXISTS q2_rep_commission_summary AS
SELECT 
    rep_id,
    first_name,
    last_name,
    commission_rate,
    base_salary
FROM sales_reps
ORDER BY commission_rate DESC, last_name ASC, first_name ASC;


-- Query 3: q3_regional_revenue_aggregates
-- Aggregate completed orders by customer region_id.
-- Compute order_count, total_revenue, avg_order_value, min_order_value, max_order_value.
-- Sorted by region_id ASCENDING.
CREATE VIEW IF NOT EXISTS q3_regional_revenue_aggregates AS
SELECT 
    c.region_id AS region_id,
    COUNT(o.order_id) AS order_count,
    SUM(o.total_amount) AS total_revenue,
    AVG(o.total_amount) AS avg_order_value,
    MIN(o.total_amount) AS min_order_value,
    MAX(o.total_amount) AS max_order_value
FROM customers c
JOIN orders o ON c.customer_id = o.customer_id
WHERE o.status = 'COMPLETED'
GROUP BY c.region_id
ORDER BY c.region_id ASC;


-- Query 4: q4_category_revenue_having
-- Aggregate order items by product_category.
-- Compute total_units, category_revenue, avg_unit_price.
-- Filter groups with HAVING: category_revenue >= 500.0 AND total_units >= 10.
-- Sorted by category_revenue DESCENDING.
CREATE VIEW IF NOT EXISTS q4_category_revenue_having AS
SELECT 
    product_category,
    SUM(quantity) AS total_units,
    SUM(total_price) AS category_revenue,
    AVG(unit_price) AS avg_unit_price
FROM order_items
GROUP BY product_category
HAVING SUM(total_price) >= 500.0 AND SUM(quantity) >= 10
ORDER BY category_revenue DESC;


-- Query 5: q5_tier_metrics_sorted
-- Aggregate completed orders by customer_tier.
-- Compute unique_customers, total_orders, tier_revenue, avg_tier_order.
-- Filter groups with HAVING: tier_revenue >= 1000.0.
-- Sorted by tier_revenue DESCENDING.
CREATE VIEW IF NOT EXISTS q5_tier_metrics_sorted AS
SELECT 
    c.customer_tier AS customer_tier,
    COUNT(DISTINCT c.customer_id) AS unique_customers,
    COUNT(o.order_id) AS total_orders,
    SUM(o.total_amount) AS tier_revenue,
    AVG(o.total_amount) AS avg_tier_order
FROM customers c
JOIN orders o ON c.customer_id = o.customer_id
WHERE o.status = 'COMPLETED'
GROUP BY c.customer_tier
HAVING SUM(o.total_amount) >= 1000.0
ORDER BY tier_revenue DESC;
