#ifndef CURRENCY_ENGINE_HPP
#define CURRENCY_ENGINE_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <sstream>

class CurrencyAmount {
private:
    long long total_cents_;
    std::string currency_code_;

public:
    // Default constructor (0 cents, "USD")
    CurrencyAmount();

    // Parameterized constructor (dollars, cents, currency_code)
    CurrencyAmount(long long dollars, int cents, const std::string& currency = "USD");

    // Parameterized constructor (total_cents, currency_code)
    CurrencyAmount(long long total_cents, const std::string& currency);

    // Getters
    long long getCents() const;
    long long getDollars() const;
    int getCentsPart() const;
    std::string getCurrency() const;

    // Overloaded Binary Operators
    CurrencyAmount operator+(const CurrencyAmount& other) const;
    CurrencyAmount operator-(const CurrencyAmount& other) const;
    bool operator==(const CurrencyAmount& other) const;
    CurrencyAmount& operator+=(const CurrencyAmount& other);

    // Overloaded Unary Operators
    CurrencyAmount operator-() const;
    CurrencyAmount& operator++();       // Prefix increment (+1 cent)
    CurrencyAmount operator++(int);     // Postfix increment (+1 cent)

    // Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& os, const CurrencyAmount& amount);
};

#endif // CURRENCY_ENGINE_HPP
