# CS2002 Lab 05: High-Precision Financial Currency Engine

## Overview

In financial computing systems, floating-point data types (`float`, `double`) are unsuitable for representing money due to IEEE 754 precision limitations and rounding artifacts (e.g., `0.1 + 0.2 != 0.3`). Financial institutions mandate fixed-point integer representation (e.g., storing monetary balances in total cents) to ensure zero rounding loss.

In this lab, you will design and implement `CurrencyAmount`, a C++ class representing monetary values using fixed-precision integer cents and an ISO currency code string (e.g. `"USD"`, `"EUR"`, `"GBP"`). You will practice **operator overloading** in C++ to provide natural mathematical syntax (`+`, `-`, `==`, `+=`, `-`, `++`, `<<`) for financial calculations while enforcing currency code integrity.

---

## Objectives

1. **Fixed-Point Monetary Representation**: Store balances internally as total integer cents (`long long`) to eliminate floating-point representation errors.
2. **Binary Operator Overloading**: Implement binary arithmetic (`+`, `-`), compound assignment (`+=`), and equality (`==`) with strict currency mismatch checking (`std::invalid_argument`).
3. **Unary Operator Overloading**: Implement unary negation (`-`) and prefix/postfix increment operators (`++`) to increment balances by 1 cent.
4. **Stream Output Formatting**: Overload the `<<` operator to produce clean, standard monetary string representations (e.g., `"USD 12.34"` or `"EUR -0.05"`).

---

## Class Specification: `CurrencyAmount`

The class `CurrencyAmount` is declared in `currency_engine.hpp`. Implement all member functions and friend operators in `currency_engine.cpp`.

### Data Members (Private)

- `long long total_cents_`: Balance stored in integer cents (1 dollar = 100 cents). Can be positive, negative, or zero.
- `std::string currency_code_`: ISO currency code string (default `"USD"`).

---

### Constructors

- `CurrencyAmount()`
  - Default constructor.
  - Initializes `total_cents_ = 0` and `currency_code_ = "USD"`.

- `CurrencyAmount(long long dollars, int cents, const std::string& currency = "USD")`
  - Parameterized constructor.
  - Converts dollars and cents into `total_cents_`.
  - For positive dollars (`dollars >= 0`), `total_cents_ = dollars * 100 + abs(cents)`.
  - For negative dollars (`dollars < 0`), `total_cents_ = dollars * 100 - abs(cents)`.

- `CurrencyAmount(long long total_cents, const std::string& currency)`
  - Parameterized constructor.
  - Directly sets `total_cents_` to the provided integer cents and `currency_code_` to `currency`.

---

### Getters

- `long long getCents() const`: Returns total integer cents (`total_cents_`).
- `long long getDollars() const`: Returns the integer dollars component (`total_cents_ / 100`).
- `int getCentsPart() const`: Returns the fractional cents component as an integer from 0 to 99 (`abs(total_cents_ % 100)`).
- `std::string getCurrency() const`: Returns the ISO currency code string.

---

### Overloaded Binary Operators

- `CurrencyAmount operator+(const CurrencyAmount& other) const`
  - Returns a new `CurrencyAmount` representing the sum of two amounts.
  - Throws `std::invalid_argument("Currency mismatch")` if currency codes differ.

- `CurrencyAmount operator-(const CurrencyAmount& other) const`
  - Returns a new `CurrencyAmount` representing the difference of two amounts.
  - Throws `std::invalid_argument("Currency mismatch")` if currency codes differ.

- `bool operator==(const CurrencyAmount& other) const`
  - Returns `true` if both the currency codes and total cents are equal; `false` otherwise.

- `CurrencyAmount& operator+=(const CurrencyAmount& other)`
  - Adds `other` to `*this` in-place and returns a reference to `*this`.
  - Throws `std::invalid_argument("Currency mismatch")` if currency codes differ.

---

### Overloaded Unary Operators

- `CurrencyAmount operator-() const`
  - Unary negation operator.
  - Returns a new `CurrencyAmount` with negated cents and the same currency code.

- `CurrencyAmount& operator++()`
  - Prefix increment operator (`++c`).
  - Increments `total_cents_` by 1 cent.
  - Returns a reference to `*this`.

- `CurrencyAmount operator++(int)`
  - Postfix increment operator (`c++`).
  - Increments `total_cents_` by 1 cent.
  - Returns a copy of the `CurrencyAmount` object *before* the increment took place.

---

### Stream Insertion Operator

- `friend std::ostream& operator<<(std::ostream& os, const CurrencyAmount& amount)`
  - Overloads output stream insertion.
  - Formats monetary output as `"<Currency> <Dollars>.<Cents>"` with cents zero-padded to 2 decimal places.
  - Examples:
    - 1234 cents USD $\rightarrow$ `"USD 12.34"`
    - 5 cents USD $\rightarrow$ `"USD 0.05"`
    - 0 cents GBP $\rightarrow$ `"GBP 0.00"`
    - -5 cents EUR $\rightarrow$ `"EUR -0.05"`
    - -1234 cents USD $\rightarrow$ `"USD -12.34"`

---

## Local Verification & Usage

Run the public test suite locally to verify your implementation:

```bash
make test-public
# or using the run wrapper:
./run
```

To clean generated binaries and temporary files:

```bash
make clean
```
