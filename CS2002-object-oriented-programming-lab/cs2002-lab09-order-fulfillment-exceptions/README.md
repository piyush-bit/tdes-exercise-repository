# CS2002 Lab 09: Order Fulfillment Exception Engine

## Overview

In robust C++ application design, runtime errors—such as inventory shortages, payment authorization failures, or external database dropouts—must be handled gracefully using structured exception handling.

In this lab, you will build an **Order Fulfillment Exception Engine** for an e-commerce platform. You will implement custom exception classes derived from `std::exception`, an `OrderProcessor` class that validates order constraints and throws appropriate exceptions, and an `executeOrderPipeline` function that uses polymorphic catch blocks and a catch-all (`catch(...)`) fallback handler.

---

## Learning Objectives

1. Create custom exception classes (`InsufficientStockException`, `PaymentFailedException`) inheriting from `std::exception`.
2. Override the `what()` method to return detailed, formatted error messages.
3. Throw specific exceptions based on business logic validation in `OrderProcessor::processOrder`.
4. Implement `executeOrderPipeline` using ordered exception handlers (most specific to least specific) and a `catch(...)` catch-all fallback handler.

---

## File Structure

```
cs2002-lab09-order-fulfillment-exceptions/
├── manifest.json              # Lab metadata and grading configuration
├── README.md                  # Problem specification
├── Dockerfile                 # Environment definition (lab-cpp-runner:v1.0)
├── Makefile                   # Build targets (test-public and grading targets)
├── run                        # Helper script
├── order_fulfillment.hpp      # Header file (Do NOT edit)
├── order_fulfillment.cpp      # Student boilerplate (Editable)
├── public_test.cpp            # Public test suite
├── reference/
│   └── order_fulfillment.cpp  # Reference solution (Hidden during grading)
└── tests_private/             # Private test suites (Hidden during grading)
    ├── test_custom_exceptions.cpp
    └── test_catch_all.cpp
```

---

## Specification & Contract

### 1. Data Structures (`order_fulfillment.hpp`)

`Order` struct represents an order in the fulfillment system:
```cpp
struct Order {
    std::string orderId;
    std::string item;
    int quantity;
    int availableStock;
    double amount;
    bool paymentValid;
    bool systemError;   // Triggers std::runtime_error
    bool unknownError;  // Triggers raw non-std exception
};
```

### 2. Custom Exceptions

- **`InsufficientStockException`** (inherits from `std::exception`)
  - **Constructor:** `InsufficientStockException(const std::string& item, int requested, int available)`
  - **Methods:**
    - `const char* what() const noexcept override;` -> returns message formatted as:
      `"Insufficient stock for item '<item>': requested <requested>, available <available>"`
    - `std::string getItem() const;`
    - `int getRequested() const;`
    - `int getAvailable() const;`

- **`PaymentFailedException`** (inherits from `std::exception`)
  - **Constructor:** `PaymentFailedException(const std::string& orderId, double amount, const std::string& reason)`
  - **Methods:**
    - `const char* what() const noexcept override;` -> returns message formatted as:
      `"Payment failed for order <orderId> (Amount: <amount>): <reason>"`
    - `std::string getOrderId() const;`
    - `double getAmount() const;`
    - `std::string getReason() const;`

### 3. `OrderProcessor` Class

- `void processOrder(const Order& order);`
  - Validates order in the following priority order:
    1. If `order.quantity > order.availableStock`: throw `InsufficientStockException(order.item, order.quantity, order.availableStock)`.
    2. If `!order.paymentValid`: throw `PaymentFailedException(order.orderId, order.amount, "Payment authorization failed")`.
    3. If `order.systemError`: throw `std::runtime_error("Database connection failed during order processing")`.
    4. If `order.unknownError`: throw `500` (or raw integer/non-std exception).
    5. If all checks pass, complete processing cleanly without throwing.

### 4. Pipeline Function

- `std::string executeOrderPipeline(const Order& order, OrderProcessor& processor);`
  - Executes `processor.processOrder(order)` inside a `try` block.
  - Catches exceptions using appropriate catch handlers:
    - `InsufficientStockException`: returns `"STOCK_ERROR: " + e.what()`
    - `PaymentFailedException`: returns `"PAYMENT_ERROR: " + e.what()`
    - `std::exception`: returns `"STANDARD_ERROR: " + e.what()`
    - `catch (...)`: returns `"UNKNOWN_ERROR: Handled by catch-all fallback handler"`
  - If no exception occurs, returns `"SUCCESS: Order " + order.orderId + " processed successfully"`.

---

## Local Testing

Run public tests:
```bash
./run public
# OR
make test-public
```

Clean build artifacts:
```bash
./run clean
# OR
make clean
```

---

## Grading Breakdown

| Target | Points | Description |
| :--- | :--- | :--- |
| `make test-public` | 0 pts | Local public suite verification |
| `make test-submission-custom-exceptions` | 5 pts | Custom exception hierarchy, getters, formatting, and validation precedence |
| `make test-submission-catch-all-handler` | 5 pts | Catch block ordering and catch-all `catch(...)` fallback handling |
| **Total** | **10 pts** | |
