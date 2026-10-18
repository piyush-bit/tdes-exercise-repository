#ifndef CURRENCY_CONVERTER_HPP
#define CURRENCY_CONVERTER_HPP

#include <iostream>
#include <cmath>

// Exchange rate constants:
// 1 USD = 0.85 EUR
// 1 EUR = 1.0 / 0.85 USD ≈ 1.176470588 USD
constexpr double USD_TO_EUR_RATE = 0.85;
constexpr double EUR_TO_USD_RATE = 1.0 / USD_TO_EUR_RATE;

// Forward declaration of EuroCurrency
class EuroCurrency;

class USDollar {
private:
    double amount_;

public:
    // Default constructor
    USDollar();

    // Primitive-to-Class Conversion Constructor (double -> USDollar)
    USDollar(double amt);

    // Class-to-Class Conversion Constructor (EuroCurrency -> USDollar)
    explicit USDollar(const EuroCurrency& eur);

    // Accessors and Mutators
    double getAmount() const;
    void setAmount(double amt);

    // Class-to-Primitive Conversion Operator (USDollar -> double)
    operator double() const;

    // Class-to-Class Conversion Operator (USDollar -> EuroCurrency)
    operator EuroCurrency() const;
};

class EuroCurrency {
private:
    double amount_;

public:
    // Default constructor
    EuroCurrency();

    // Primitive-to-Class Conversion Constructor (double -> EuroCurrency)
    EuroCurrency(double amt);

    // Class-to-Class Conversion Constructor (USDollar -> EuroCurrency)
    explicit EuroCurrency(const USDollar& usd);

    // Accessors and Mutators
    double getAmount() const;
    void setAmount(double amt);

    // Class-to-Primitive Conversion Operator (EuroCurrency -> double)
    operator double() const;

    // Class-to-Class Conversion Operator (EuroCurrency -> USDollar)
    operator USDollar() const;
};

// Utility & Helper Functions
USDollar convertToUSD(double amount);
double convertToPrimitiveUSD(const USDollar& usd);
EuroCurrency convertUSDToEUR(const USDollar& usd);
USDollar convertEURToUSD(const EuroCurrency& eur);
EuroCurrency convertWithCustomRate(const USDollar& usd, double customRate);

#endif // CURRENCY_CONVERTER_HPP
