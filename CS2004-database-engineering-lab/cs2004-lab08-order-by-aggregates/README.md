# CS2004 Lab 08: Executive Sales & Revenue Summary Analytics

## Overview

In enterprise data engineering, C-level executives rely on clean, ordered, and aggregated analytics to make strategic revenue decisions. Raw transactional tables contain millions of line items; SQL aggregation (`COUNT`, `SUM`, `AVG`, `MIN`, `MAX`), grouping (`GROUP BY`), threshold filtering (`HAVING`), and precise sorting (`ORDER BY ASC/DESC`) transform raw records into executive-ready metrics.

In this lab, you will author five SQL analytical views inside `solution.sql` against an enterprise sales database schema.

---

## Schema Architecture

The database contains five relational tables:

```text
sales_regions (region_id, region_name, country)
sales_reps (rep_id, first_name, last_name, region_id, base_salary, commission_rate)
customers (customer_id, customer_name, customer_tier, region_id)
orders (order_id, customer_id, rep_id, order_date, status, total_amount)
order_items (item_id, order_id, product_category, quantity, unit_price, total_price)
```

### Table Definitions

1. `sales_regions`:
   - `region_id` (INTEGER, PRIMARY KEY)
   - `region_name` (TEXT)
   - `country` (TEXT)

2. `sales_reps`:
   - `rep_id` (INTEGER, PRIMARY KEY)
   - `first_name` (TEXT)
   - `last_name` (TEXT)
   - `region_id` (INTEGER, FOREIGN KEY -> `sales_regions.region_id`)
   - `base_salary` (REAL)
   - `commission_rate` (REAL)

3. `customers`:
   - `customer_id` (INTEGER, PRIMARY KEY)
   - `customer_name` (TEXT)
   - `customer_tier` (TEXT) - e.g., 'Bronze', 'Silver', 'Gold', 'Platinum'
   - `region_id` (INTEGER, FOREIGN KEY -> `sales_regions.region_id`)

4. `orders`:
   - `order_id` (INTEGER, PRIMARY KEY)
   - `customer_id` (INTEGER, FOREIGN KEY -> `customers.customer_id`)
   - `rep_id` (INTEGER, FOREIGN KEY -> `sales_reps.rep_id`)
   - `order_date` (TEXT) - ISO-8601 date string, e.g. `'2026-03-15'`
   - `status` (TEXT) - `'COMPLETED'`, `'PENDING'`, or `'CANCELLED'`
   - `total_amount` (REAL)

5. `order_items`:
   - `item_id` (INTEGER, PRIMARY KEY)
   - `order_id` (INTEGER, FOREIGN KEY -> `orders.order_id`)
   - `product_category` (TEXT)
   - `quantity` (INTEGER)
   - `unit_price` (REAL)
   - `total_price` (REAL)

---

## Task Requirements

You must implement five SQL views in `solution.sql`:

### Query 1: `q1_sorted_orders`
*Objective: Rank completed orders by monetary revenue with chronological tie-breaking.*
- **Source:** `orders`
- **Filter:** `status = 'COMPLETED'`
- **Columns:** `order_id`, `customer_id`, `order_date`, `total_amount`, `status`
- **Ordering:**
  - Primary: `total_amount` **DESCENDING**
  - Secondary (tie-breaker): `order_date` **ASCENDING**

### Query 2: `q2_rep_commission_summary`
*Objective: Order sales representatives by sales commission tier and alphabetical name.*
- **Source:** `sales_reps`
- **Columns:** `rep_id`, `first_name`, `last_name`, `commission_rate`, `base_salary`
- **Ordering:**
  - Primary: `commission_rate` **DESCENDING**
  - Secondary: `last_name` **ASCENDING**
  - Tertiary: `first_name` **ASCENDING**

### Query 3: `q3_regional_revenue_aggregates`
*Objective: Calculate executive regional KPI summaries across completed sales.*
- **Source:** `orders` joined with `customers`
- **Filter:** `orders.status = 'COMPLETED'`
- **Grouping:** `GROUP BY customers.region_id`
- **Columns:**
  - `region_id`: `customers.region_id`
  - `order_count`: Total number of completed orders (`COUNT(orders.order_id)`)
  - `total_revenue`: Sum of completed order totals (`SUM(orders.total_amount)`)
  - `avg_order_value`: Average completed order total (`AVG(orders.total_amount)`)
  - `min_order_value`: Minimum completed order total (`MIN(orders.total_amount)`)
  - `max_order_value`: Maximum completed order total (`MAX(orders.total_amount)`)
- **Ordering:** `region_id` **ASCENDING**

### Query 4: `q4_category_revenue_having`
*Objective: Aggregate product line performance and filter low-volume categories using HAVING.*
- **Source:** `order_items`
- **Grouping:** `GROUP BY product_category`
- **Columns:**
  - `product_category`: Name of product category
  - `total_units`: Total quantity sold across items (`SUM(quantity)`)
  - `category_revenue`: Total revenue from item sales (`SUM(total_price)`)
  - `avg_unit_price`: Average unit price (`AVG(unit_price)`)
- **HAVING Condition:** `SUM(total_price) >= 500.0 AND SUM(quantity) >= 10`
- **Ordering:** `category_revenue` **DESCENDING**

### Query 5: `q5_tier_metrics_sorted`
*Objective: Analyze customer tier spending metrics, applying aggregate thresholds and revenue sorting.*
- **Source:** `customers` joined with `orders`
- **Filter:** `orders.status = 'COMPLETED'`
- **Grouping:** `GROUP BY customers.customer_tier`
- **Columns:**
  - `customer_tier`: Tier designation ('Bronze', 'Silver', etc.)
  - `unique_customers`: Number of distinct customers placing completed orders (`COUNT(DISTINCT customers.customer_id)`)
  - `total_orders`: Total completed orders in tier (`COUNT(orders.order_id)`)
  - `tier_revenue`: Total revenue generated by tier (`SUM(orders.total_amount)`)
  - `avg_tier_order`: Average order amount in tier (`AVG(orders.total_amount)`)
- **HAVING Condition:** `SUM(orders.total_amount) >= 1000.0`
- **Ordering:** `tier_revenue` **DESCENDING**

---

## Evaluation & Testing

Run local tests using the provided wrapper or Makefile:

```bash
./run public
# or
make test-public
```

Grading consists of two evaluation suites:
1. `test-submission-sorting-ordering` (5 pts): Verifies `q1_sorted_orders` and `q2_rep_commission_summary` multi-column sorting contracts.
2. `test-submission-group-aggregates` (5 pts): Verifies `q3_regional_revenue_aggregates`, `q4_category_revenue_having`, and `q5_tier_metrics_sorted` mathematical aggregates, grouping, HAVING filters, and output structures.
