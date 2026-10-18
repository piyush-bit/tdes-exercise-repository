#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "currency_converter.hpp"

void assertNear(double actual, double expected, double tol, const std::string& msg) {
    if (std::abs(actual - expected) > tol) {
        std::cerr << "[FAIL] " << msg << " | Expected: " << expected << ", Got: " << actual << std::endl;
        std::exit(1);
    }
}

int main() {
    std::cout << "=== Running Public Tests for Multi-Currency FX Converter ===" << std::endl;

    // Test 1: Primitive-to-Class (double -> USDollar)
    USDollar usd1(100.0);
    assertNear(usd1.getAmount(), 100.0, 1e-6, "Primitive-to-Class USDollar constructor failed");
    std::cout << "[PASS] Primitive-to-Class USDollar constructor" << std::endl;

    // Test 2: Class-to-Primitive (USDollar -> double)
    double rawUsd = usd1;
    assertNear(rawUsd, 100.0, 1e-6, "Class-to-Primitive USDollar operator failed");
    std::cout << "[PASS] Class-to-Primitive USDollar operator double()" << std::endl;

    // Test 3: Primitive-to-Class (double -> EuroCurrency)
    EuroCurrency eur1(85.0);
    assertNear(eur1.getAmount(), 85.0, 1e-6, "Primitive-to-Class EuroCurrency constructor failed");
    std::cout << "[PASS] Primitive-to-Class EuroCurrency constructor" << std::endl;

    // Test 4: Class-to-Primitive (EuroCurrency -> double)
    double rawEur = eur1;
    assertNear(rawEur, 85.0, 1e-6, "Class-to-Primitive EuroCurrency operator failed");
    std::cout << "[PASS] Class-to-Primitive EuroCurrency operator double()" << std::endl;

    // Test 5: Helper function USD -> EUR conversion
    EuroCurrency convertedEur = convertUSDToEUR(usd1);
    assertNear(convertedEur.getAmount(), 85.0, 1e-4, "USD to EUR conversion failed");
    std::cout << "[PASS] convertUSDToEUR helper function" << std::endl;

    std::cout << "=== All Public Tests Passed Successfully! ===" << std::endl;
    return 0;
}
