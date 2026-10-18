#include "currency_engine.hpp"

// Default constructor (0 cents, "USD")
CurrencyAmount::CurrencyAmount()
    : total_cents_(0), currency_code_("USD") {}

// Parameterized constructor (dollars, cents, currency_code)
CurrencyAmount::CurrencyAmount(long long dollars, int cents, const std::string& currency)
    : currency_code_(currency) {
    int abs_cents = std::abs(cents);
    if (dollars >= 0) {
        total_cents_ = dollars * 100 + abs_cents;
    } else {
        total_cents_ = dollars * 100 - abs_cents;
    }
}

// Parameterized constructor (total_cents, currency_code)
CurrencyAmount::CurrencyAmount(long long total_cents, const std::string& currency)
    : total_cents_(total_cents), currency_code_(currency) {}

// Getters
long long CurrencyAmount::getCents() const {
    return total_cents_;
}

long long CurrencyAmount::getDollars() const {
    return total_cents_ / 100;
}

int CurrencyAmount::getCentsPart() const {
    return static_cast<int>(std::abs(total_cents_ % 100));
}

std::string CurrencyAmount::getCurrency() const {
    return currency_code_;
}

// Overloaded Binary Operators
CurrencyAmount CurrencyAmount::operator+(const CurrencyAmount& other) const {
    if (currency_code_ != other.currency_code_) {
        throw std::invalid_argument("Currency mismatch");
    }
    return CurrencyAmount(total_cents_ + other.total_cents_, currency_code_);
}

CurrencyAmount CurrencyAmount::operator-(const CurrencyAmount& other) const {
    if (currency_code_ != other.currency_code_) {
        throw std::invalid_argument("Currency mismatch");
    }
    return CurrencyAmount(total_cents_ - other.total_cents_, currency_code_);
}

bool CurrencyAmount::operator==(const CurrencyAmount& other) const {
    return (currency_code_ == other.currency_code_) && (total_cents_ == other.total_cents_);
}

CurrencyAmount& CurrencyAmount::operator+=(const CurrencyAmount& other) {
    if (currency_code_ != other.currency_code_) {
        throw std::invalid_argument("Currency mismatch");
    }
    total_cents_ += other.total_cents_;
    return *this;
}

// Overloaded Unary Operators
CurrencyAmount CurrencyAmount::operator-() const {
    return CurrencyAmount(-total_cents_, currency_code_);
}

CurrencyAmount& CurrencyAmount::operator++() {
    total_cents_ += 1;
    return *this;
}

CurrencyAmount CurrencyAmount::operator++(int) {
    CurrencyAmount temp = *this;
    total_cents_ += 1;
    return temp;
}

// Stream Insertion Operator
std::ostream& operator<<(std::ostream& os, const CurrencyAmount& amount) {
    long long total = amount.total_cents_;
    if (total < 0) {
        long long abs_total = std::abs(total);
        long long dollars = abs_total / 100;
        int cents = static_cast<int>(abs_total % 100);
        os << amount.currency_code_ << " -" << dollars << "." << std::setw(2) << std::setfill('0') << cents;
    } else {
        long long dollars = total / 100;
        int cents = static_cast<int>(total % 100);
        os << amount.currency_code_ << " " << dollars << "." << std::setw(2) << std::setfill('0') << cents;
    }
    return os;
}
