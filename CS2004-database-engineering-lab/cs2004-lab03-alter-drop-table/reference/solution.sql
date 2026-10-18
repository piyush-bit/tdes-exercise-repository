-- Reference Solution for CS2004 Lab 03: E-Commerce Schema Migration (ALTER & DROP TABLE)

-- Task 1: Add 'category' column (TEXT) to 'products' table
ALTER TABLE products ADD COLUMN category TEXT;

-- Task 2: Rename column 'stock_quantity' to 'stock' in 'products' table
ALTER TABLE products RENAME COLUMN stock_quantity TO stock;

-- Task 3: Drop deprecated 'legacy_orders' table
DROP TABLE legacy_orders;
