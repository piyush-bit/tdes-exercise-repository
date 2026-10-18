#include "currency_converter.hpp"

// ==========================================
// USDollar Implementation
// ==========================================

USDollar::USDollar() : amount_(0.0) {}

USDollar::USDollar(double amt) : amount_(amt) {}

USDollar::USDollar(const EuroCurrency& eur) : amount_(eur.getAmount() * EUR_TO_USD_RATE) {}

double USDollar::getAmount() const {
    return amount_;
}

void USDollar::setAmount(double amt) {
    amount_ = amt;
}

USDollar::operator double() const {
    return amount_;
}

USDollar::operator EuroCurrency() const {
    return EuroCurrency(amount_ * USD_TO_EUR_RATE);
}


// ==========================================
// EuroCurrency Implementation
// ==========================================

EuroCurrency::EuroCurrency() : amount_(0.0) {}

EuroCurrency::EuroCurrency(double amt) : amount_(amt) {}

EuroCurrency::EuroCurrency(const USDollar& usd) : amount_(usd.getAmount() * USD_TO_EUR_RATE) {}

double EuroCurrency::getAmount() const {
    return amount_;
}

void EuroCurrency::setAmount(double amt) {
    amount_ = amt;
}

EuroCurrency::operator double() const {
    return amount_;
}

EuroCurrency::operator USDollar() const {
    return USDollar(amount_ * EUR_TO_USD_RATE);
}


// ==========================================
// Helper Functions Implementation
// ==========================================

USDollar convertToUSD(double amount) {
    return USDollar(amount);
}

double convertToPrimitiveUSD(const USDollar& usd) {
    return static_cast<double>(usd);
}

EuroCurrency convertUSDToEUR(const USDollar& usd) {
    return EuroCurrency(usd);
}

USDollar convertEURToUSD(const EuroCurrency& eur) {
    return USDollar(eur);
}

EuroCurrency convertWithCustomRate(const USDollar& usd, double customRate) {
    return EuroCurrency(usd.getAmount() * customRate);
}
