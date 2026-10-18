#include "currency_engine.hpp"

// Default constructor (0 cents, "USD")
CurrencyAmount::CurrencyAmount()
    : total_cents_(0), currency_code_("USD") {}

// Parameterized constructor (dollars, cents, currency_code)
CurrencyAmount::CurrencyAmount(long long dollars, int cents, const std::string& currency) {
    // TODO: Initialize total_cents_ and currency_code_ correctly
    (void)dollars;
    (void)cents;
    total_cents_ = 0;
    currency_code_ = currency;
}

// Parameterized constructor (total_cents, currency_code)
CurrencyAmount::CurrencyAmount(long long total_cents, const std::string& currency) {
    // TODO: Initialize total_cents_ and currency_code_
    total_cents_ = total_cents;
    currency_code_ = currency;
}

// Getters
long long CurrencyAmount::getCents() const {
    // TODO: Return total_cents_
    return total_cents_;
}

long long CurrencyAmount::getDollars() const {
    // TODO: Return integer dollars part
    return 0;
}

int CurrencyAmount::getCentsPart() const {
    // TODO: Return fractional cents part (0-99)
    return 0;
}

std::string CurrencyAmount::getCurrency() const {
    // TODO: Return currency code
    return currency_code_;
}

// Overloaded Binary Operators
CurrencyAmount CurrencyAmount::operator+(const CurrencyAmount& other) const {
    // TODO: Check currency match (throw std::invalid_argument on mismatch) and return sum
    (void)other;
    return CurrencyAmount();
}

CurrencyAmount CurrencyAmount::operator-(const CurrencyAmount& other) const {
    // TODO: Check currency match (throw std::invalid_argument on mismatch) and return difference
    (void)other;
    return CurrencyAmount();
}

bool CurrencyAmount::operator==(const CurrencyAmount& other) const {
    // TODO: Return true if currency and total cents match, false otherwise
    (void)other;
    return false;
}

CurrencyAmount& CurrencyAmount::operator+=(const CurrencyAmount& other) {
    // TODO: Check currency match (throw std::invalid_argument on mismatch) and add to *this
    (void)other;
    return *this;
}

// Overloaded Unary Operators
CurrencyAmount CurrencyAmount::operator-() const {
    // TODO: Return negated CurrencyAmount
    return CurrencyAmount();
}

CurrencyAmount& CurrencyAmount::operator++() {
    // TODO: Implement prefix increment (+1 cent), return reference to *this
    return *this;
}

CurrencyAmount CurrencyAmount::operator++(int) {
    // TODO: Implement postfix increment (+1 cent), return copy of object prior to increment
    return CurrencyAmount();
}

// Stream Insertion Operator
std::ostream& operator<<(std::ostream& os, const CurrencyAmount& amount) {
    // TODO: Format output as "<Currency> <Dollars>.<Cents>" (e.g. "USD 12.34" or "EUR -0.05")
    (void)amount;
    return os;
}
