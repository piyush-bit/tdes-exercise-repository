-- CS2004 Lab 04: Order Fulfillment CRUD DML Operations
-- Reference Solution

-- Task 1: INSERT Operations
INSERT INTO orders (customer_id, order_date, total_amount, status, shipping_address)
VALUES (105, '2024-02-01', 500.00, 'PENDING', '500 Maple Dr');

INSERT INTO orders (customer_id, order_date, total_amount, status, shipping_address)
VALUES (102, '2024-02-02', 75.25, 'PROCESSING', '200 Oak Ave');

-- Task 2: UPDATE Operations
UPDATE orders
SET status = 'PROCESSING'
WHERE status = 'PENDING' AND order_date <= '2024-01-15';

UPDATE orders
SET total_amount = total_amount * 0.90
WHERE total_amount > 300.00;

-- Task 3: DELETE Operations
DELETE FROM orders
WHERE status = 'CANCELLED';

-- Task 4: SELECT Operation
SELECT order_id, customer_id, total_amount, status
FROM orders
WHERE status != 'CANCELLED'
ORDER BY total_amount DESC, order_id ASC;
