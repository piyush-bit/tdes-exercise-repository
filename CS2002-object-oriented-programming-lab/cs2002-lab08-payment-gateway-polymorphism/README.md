# CS2002 Lab 08: Universal Payment Gateway Engine (C++ Polymorphism)

## Objective
Design and implement a scalable, object-oriented Universal Payment Gateway system in C++ using **Abstract Base Classes**, **Pure Virtual Methods**, **Virtual Destructors**, and **Dynamic Dispatch (Polymorphism)**.

---

## Background & Architecture

Modern e-commerce applications must process payments across multiple third-party payment providers (e.g., Stripe, PayPal, Cryptocurrency networks). Rather than writing separate processing pipelines for each gateway, object-oriented design allows us to define a uniform interface (`PaymentProcessor`) and use runtime dynamic dispatch to handle payments polymorphically.

```
                  +--------------------------+
                  |    PaymentProcessor      |  <-- Abstract Base Class
                  +--------------------------+
                  | # gatewayName            |
                  | # totalVolumeProcessed   |
                  | # successfulTransactions |
                  | # failedTransactions     |
                  +--------------------------+
                  | + processPayment()* = 0  |
                  | + calculateFee()* = 0    |
                  | + virtual ~PaymentProcessor() |
                  +--------------------------+
                               |
         +---------------------+---------------------+
         |                     |                     |
+------------------+  +------------------+  +------------------+
| StripeProcessor  |  | PayPalProcessor  |  | CryptoProcessor  |
+------------------+  +------------------+  +------------------+
| - apiKey         |  | - accountEmail   |  | - walletAddress  |
+------------------+  +------------------+  +------------------+
```

---

## Interface Specifications

### 1. `PaymentProcessor` (Abstract Base Class)
- **Data Members (Protected)**:
  - `std::string gatewayName`: Name of the payment gateway (e.g. `"Stripe"`, `"PayPal"`, `"Crypto"`).
  - `double totalVolumeProcessed`: Cumulative dollar amount successfully processed across all transactions.
  - `int successfulTransactions`: Count of successful payment operations.
  - `int failedTransactions`: Count of failed payment attempts.
- **Constructor & Destructor**:
  - `PaymentProcessor(const std::string& name)`: Initializes `gatewayName` and resets all tracking statistics (`0.0` volume, `0` counts).
  - `virtual ~PaymentProcessor() = default`: Virtual destructor ensuring derived class cleanup during polymorphic destruction.
- **Pure Virtual Methods**:
  - `virtual bool processPayment(double amount) = 0`: Pure virtual method to execute payment.
  - `virtual double calculateFee(double amount) const = 0`: Pure virtual method to calculate provider fee.
- **Query Methods**:
  - `getGatewayName()`, `getTotalVolumeProcessed()`, `getSuccessfulTransactions()`, `getFailedTransactions()`.

---

### 2. `StripeProcessor` (Derived Class)
- **Data Member (Private)**:
  - `std::string apiKey`: Stripe authentication key.
- **Rules & Calculations**:
  - Fee Formula: `(amount * 0.029) + 0.30` for valid amounts (`amount > 0.0`) and non-empty `apiKey`. Returns `0.0` otherwise.
  - Validation: `processPayment(double amount)` succeeds (`true`) if `amount > 0.0` and `apiKey` is non-empty.
  - On Success: Increments `successfulTransactions` by 1 and adds `amount` to `totalVolumeProcessed`.
  - On Failure: Increments `failedTransactions` by 1 and returns `false`.

---

### 3. `PayPalProcessor` (Derived Class)
- **Data Member (Private)**:
  - `std::string accountEmail`: Registered PayPal email address.
- **Rules & Calculations**:
  - Fee Formula: `(amount * 0.0349) + 0.49` for valid transactions. Returns `0.0` for invalid transactions.
  - Validation: `processPayment(double amount)` succeeds (`true`) if `amount > 0.0`, `amount <= 10000.0` (maximum transaction cap), and `accountEmail` is non-empty and contains `'@'`.
  - On Success: Increments `successfulTransactions` by 1 and adds `amount` to `totalVolumeProcessed`.
  - On Failure: Increments `failedTransactions` by 1 and returns `false`.

---

### 4. `CryptoProcessor` (Derived Class)
- **Data Member (Private)**:
  - `std::string walletAddress`: Blockchain wallet address (e.g. Ethereum hex address).
- **Rules & Calculations**:
  - Fee Formula: Flat network gas fee of `$1.50` for valid transactions. Returns `0.0` for invalid transactions.
  - Validation: `processPayment(double amount)` succeeds (`true`) if `amount >= 5.0` (minimum threshold), and `walletAddress` starts with `"0x"` and has a length `>= 10`.
  - On Success: Increments `successfulTransactions` by 1 and adds `amount` to `totalVolumeProcessed`.
  - On Failure: Increments `failedTransactions` by 1 and returns `false`.

---

### 5. `PaymentGatewayEngine` (Batch Manager)
- **Data Member (Private)**:
  - `std::vector<PaymentProcessor*> processors`: Vector storing registered base class pointers.
- **Methods**:
  - `void registerProcessor(PaymentProcessor* processor)`: Registers non-null payment processor pointer into internal collection.
  - `int processBatch(double amount)`: Iterates through registered processors and invokes `processPayment(amount)` via dynamic dispatch. Returns total number of successful transactions.
  - `double calculateTotalFees(double amount) const`: Iterates through registered processors and sums `calculateFee(amount)` via dynamic dispatch.
  - `size_t getProcessorCount() const`: Returns count of registered processors.
  - `void clearProcessors()`: Clears registered processors.

---

## File Structure

```
cs2002-lab08-payment-gateway-polymorphism/
├── Dockerfile                   # Build environment (gcc:13-bookworm)
├── manifest.json                # Lab metadata and evaluation target config
├── README.md                    # Problem specification
├── Makefile                     # Build & Strategy B test runner
├── run                          # Convenience wrapper script
├── payment_gateway.hpp          # Class interface definitions
├── payment_gateway.cpp          # Student implementation (editable)
├── public_test.cpp              # Local public test suite
├── reference/
│   └── payment_gateway.cpp      # Reference solution
└── tests_private/
    ├── test_virtual_dispatch.cpp # Private suite: Dynamic dispatch & destruction
    └── test_gateways.cpp         # Private suite: Gateway rules & calculations
```

---

## Instructions & Local Verification

1. Implement the stubs in `payment_gateway.cpp`.
2. Run public tests locally:
   ```bash
   make test-public
   # or
   ./run public
   ```
3. Clean build artifacts:
   ```bash
   make clean
   # or
   ./run clean
   ```
