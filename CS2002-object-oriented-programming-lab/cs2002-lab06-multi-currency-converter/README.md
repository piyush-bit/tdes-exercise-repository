# CS2002 Lab 06: E-Commerce FX Exchange & Type Converter

## Overview
In modern e-commerce systems, financial transactions often involve multiple international currencies. In C++, converting between primitive floating-point types (such as `double`) and custom financial classes (such as `USDollar` or `EuroCurrency`), as well as converting directly between class types, requires a firm understanding of **User-Defined Type Conversions**.

This lab covers three fundamental types of conversions in C++:
1. **Primitive-to-Class Conversion**: Using single-argument constructors (conversion constructors) to convert a primitive data type (like `double`) into a class object.
2. **Class-to-Primitive Conversion**: Using overloaded type cast operators (`operator double()`) to convert a class object into a primitive data type.
3. **Class-to-Class Conversion**: Using conversion constructors and/or conversion operators to transform objects of one class type (`USDollar`) into another class type (`EuroCurrency`).

---

## Objectives
- Understand and implement conversion constructors for primitive-to-class and class-to-class type casting.
- Implement conversion operator functions (`operator double()`, `operator EuroCurrency()`, `operator USDollar()`).
- Support conversion between USD and EUR using standard foreign exchange (FX) rates:
  - Default rate: `1.0 USD = 0.85 EUR`
  - Inverse rate: `1.0 EUR = (1.0 / 0.85) USD ≈ 1.17647 USD`
- Implement helper functions for currency conversions and custom exchange rates.

---

## Specifications

### Constants (`currency_converter.hpp`)
- `USD_TO_EUR_RATE = 0.85`
- `EUR_TO_USD_RATE = 1.0 / USD_TO_EUR_RATE`

### `USDollar` Class
- **Constructors**:
  - `USDollar()`: Initializes amount to `0.0`.
  - `USDollar(double amt)`: Conversion constructor converting a primitive `double` into `USDollar`.
  - `explicit USDollar(const EuroCurrency& eur)`: Conversion constructor converting `EuroCurrency` to `USDollar` using `EUR_TO_USD_RATE`.
- **Getters / Setters**:
  - `double getAmount() const`: Returns the currency amount.
  - `void setAmount(double amt)`: Sets the currency amount.
- **Conversion Operators**:
  - `operator double() const`: Converts `USDollar` to `double`.
  - `operator EuroCurrency() const`: Converts `USDollar` to `EuroCurrency` using `USD_TO_EUR_RATE`.

### `EuroCurrency` Class
- **Constructors**:
  - `EuroCurrency()`: Initializes amount to `0.0`.
  - `EuroCurrency(double amt)`: Conversion constructor converting a primitive `double` into `EuroCurrency`.
  - `explicit EuroCurrency(const USDollar& usd)`: Conversion constructor converting `USDollar` to `EuroCurrency` using `USD_TO_EUR_RATE`.
- **Getters / Setters**:
  - `double getAmount() const`: Returns the currency amount.
  - `void setAmount(double amt)`: Sets the currency amount.
- **Conversion Operators**:
  - `operator double() const`: Converts `EuroCurrency` to `double`.
  - `operator USDollar() const`: Converts `EuroCurrency` to `USDollar` using `EUR_TO_USD_RATE`.

### Helper Functions
- `USDollar convertToUSD(double amount)`: Converts a `double` amount to a `USDollar` object.
- `double convertToPrimitiveUSD(const USDollar& usd)`: Converts a `USDollar` object to a `double`.
- `EuroCurrency convertUSDToEUR(const USDollar& usd)`: Converts a `USDollar` object to `EuroCurrency`.
- `USDollar convertEURToUSD(const EuroCurrency& eur)`: Converts a `EuroCurrency` object to `USDollar`.
- `EuroCurrency convertWithCustomRate(const USDollar& usd, double customRate)`: Converts `USDollar` to `EuroCurrency` using a caller-specified exchange rate (`amount * customRate`).

---

## File Structure
- `currency_converter.hpp`: Header file declaring `USDollar`, `EuroCurrency`, and helper functions (Do not modify).
- `currency_converter.cpp`: Source file where you must implement all class methods and helper functions.
- `public_test.cpp`: Public test suite used for local verification.
- `Makefile`: Build script for compilation and evaluation.
- `run`: Executable helper script.

---

## Tasks & Instructions
1. Open `currency_converter.cpp`.
2. Complete all `// TODO:` stubs for `USDollar`, `EuroCurrency`, and utility functions.
3. Test your solution locally:
   ```bash
   ./run
   # or
   make test-public
   ```
4. Clean build artifacts:
   ```bash
   ./run clean
   # or
   make clean
   ```

---

## Evaluation & Grading Breakdown
Total Points: **10 Points**

| Target | Description | Points |
| :--- | :--- | :--- |
| `make test-public` | Basic verification test | 0 pts (Public) |
| `make test-submission-basic-class-conversion` | Tests primitive-to-class and class-to-primitive conversions | 5 pts (Private) |
| `make test-submission-class-class-conversion` | Tests class-to-class conversions, implicit/explicit casts, and custom rates | 5 pts (Private) |
