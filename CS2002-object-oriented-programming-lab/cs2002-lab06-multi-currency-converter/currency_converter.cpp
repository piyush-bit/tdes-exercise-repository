#include "currency_converter.hpp"

// ==========================================
// USDollar Implementation
// ==========================================

// TODO: Implement Default Constructor (initializes amount_ to 0.0)
USDollar::USDollar() : amount_(0.0) {}

// TODO: Implement Primitive-to-Class Conversion Constructor (double -> USDollar)
USDollar::USDollar(double amt) : amount_(0.0) {
    // TODO: Set amount_ to amt
    (void)amt;
}

// TODO: Implement Class-to-Class Conversion Constructor (EuroCurrency -> USDollar)
USDollar::USDollar(const EuroCurrency& eur) : amount_(0.0) {
    // TODO: Convert EuroCurrency to USDollar using EUR_TO_USD_RATE
    (void)eur;
}

double USDollar::getAmount() const {
    // TODO: Return amount_
    return 0.0;
}

void USDollar::setAmount(double amt) {
    // TODO: Set amount_ to amt
    (void)amt;
}

// TODO: Implement Class-to-Primitive Conversion Operator (USDollar -> double)
USDollar::operator double() const {
    // TODO: Return amount_
    return 0.0;
}

// TODO: Implement Class-to-Class Conversion Operator (USDollar -> EuroCurrency)
USDollar::operator EuroCurrency() const {
    // TODO: Convert USDollar to EuroCurrency using USD_TO_EUR_RATE
    return EuroCurrency(0.0);
}


// ==========================================
// EuroCurrency Implementation
// ==========================================

// TODO: Implement Default Constructor (initializes amount_ to 0.0)
EuroCurrency::EuroCurrency() : amount_(0.0) {}

// TODO: Implement Primitive-to-Class Conversion Constructor (double -> EuroCurrency)
EuroCurrency::EuroCurrency(double amt) : amount_(0.0) {
    // TODO: Set amount_ to amt
    (void)amt;
}

// TODO: Implement Class-to-Class Conversion Constructor (USDollar -> EuroCurrency)
EuroCurrency::EuroCurrency(const USDollar& usd) : amount_(0.0) {
    // TODO: Convert USDollar to EuroCurrency using USD_TO_EUR_RATE
    (void)usd;
}

double EuroCurrency::getAmount() const {
    // TODO: Return amount_
    return 0.0;
}

void EuroCurrency::setAmount(double amt) {
    // TODO: Set amount_ to amt
    (void)amt;
}

// TODO: Implement Class-to-Primitive Conversion Operator (EuroCurrency -> double)
EuroCurrency::operator double() const {
    // TODO: Return amount_
    return 0.0;
}

// TODO: Implement Class-to-Class Conversion Operator (EuroCurrency -> USDollar)
EuroCurrency::operator USDollar() const {
    // TODO: Convert EuroCurrency to USDollar using EUR_TO_USD_RATE
    return USDollar(0.0);
}


// ==========================================
// Helper Functions Implementation
// ==========================================

USDollar convertToUSD(double amount) {
    // TODO: Return USDollar constructed from double amount
    (void)amount;
    return USDollar();
}

double convertToPrimitiveUSD(const USDollar& usd) {
    // TODO: Return primitive double from USDollar
    (void)usd;
    return 0.0;
}

EuroCurrency convertUSDToEUR(const USDollar& usd) {
    // TODO: Convert USDollar object to EuroCurrency object
    (void)usd;
    return EuroCurrency();
}

USDollar convertEURToUSD(const EuroCurrency& eur) {
    // TODO: Convert EuroCurrency object to USDollar object
    (void)eur;
    return USDollar();
}

EuroCurrency convertWithCustomRate(const USDollar& usd, double customRate) {
    // TODO: Convert USDollar to EuroCurrency using customRate
    (void)usd;
    (void)customRate;
    return EuroCurrency();
}
