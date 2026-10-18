#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "currency_converter.hpp"

static void assertNear(double actual, double expected, double tol, const std::string& msg) {
    if (std::abs(actual - expected) > tol) {
        std::cerr << "[FAIL] " << msg << " | Expected: " << expected << ", Got: " << actual << std::endl;
        std::exit(1);
    }
}

int main() {
    std::cout << "=== Running Private Tests: Basic & Primitive Conversions ===" << std::endl;

    // 1. Default constructor checks
    USDollar defaultUsd;
    assertNear(defaultUsd.getAmount(), 0.0, 1e-6, "Default USDollar amount should be 0.0");
    
    EuroCurrency defaultEur;
    assertNear(defaultEur.getAmount(), 0.0, 1e-6, "Default EuroCurrency amount should be 0.0");
    std::cout << "[PASS] Default constructors" << std::endl;

    // 2. Accessors & Mutators
    USDollar mutUsd;
    mutUsd.setAmount(1234.56);
    assertNear(mutUsd.getAmount(), 1234.56, 1e-6, "USDollar setAmount/getAmount failed");

    EuroCurrency mutEur;
    mutEur.setAmount(789.01);
    assertNear(mutEur.getAmount(), 789.01, 1e-6, "EuroCurrency setAmount/getAmount failed");
    std::cout << "[PASS] Accessors and Mutators" << std::endl;

    // 3. Primitive-to-Class (double -> class)
    USDollar pUsd = 250.75; // Implicit conversion constructor call
    assertNear(pUsd.getAmount(), 250.75, 1e-6, "Implicit double -> USDollar conversion constructor failed");

    EuroCurrency pEur = 499.99; // Implicit conversion constructor call
    assertNear(pEur.getAmount(), 499.99, 1e-6, "Implicit double -> EuroCurrency conversion constructor failed");
    std::cout << "[PASS] Primitive-to-Class implicit conversion constructors" << std::endl;

    // 4. Class-to-Primitive (class -> double)
    double valUsd = static_cast<double>(pUsd);
    assertNear(valUsd, 250.75, 1e-6, "static_cast<double>(USDollar) failed");

    double valEur = static_cast<double>(pEur);
    assertNear(valEur, 499.99, 1e-6, "static_cast<double>(EuroCurrency) failed");
    std::cout << "[PASS] Class-to-Primitive conversion operators" << std::endl;

    // 5. Primitive Helpers (convertToUSD, convertToPrimitiveUSD)
    USDollar helperUsd = convertToUSD(99.9);
    assertNear(helperUsd.getAmount(), 99.9, 1e-6, "convertToUSD helper failed");

    double helperVal = convertToPrimitiveUSD(helperUsd);
    assertNear(helperVal, 99.9, 1e-6, "convertToPrimitiveUSD helper failed");
    std::cout << "[PASS] Primitive conversion helper functions" << std::endl;

    // 6. Zero & Negative values
    USDollar zeroUsd(0.0);
    assertNear(zeroUsd.getAmount(), 0.0, 1e-6, "Zero USDollar failed");

    EuroCurrency negEur(-50.25);
    assertNear(negEur.getAmount(), -50.25, 1e-6, "Negative EuroCurrency failed");
    double negVal = negEur;
    assertNear(negVal, -50.25, 1e-6, "Negative EuroCurrency class-to-primitive failed");
    std::cout << "[PASS] Edge cases (zero and negative amounts)" << std::endl;

    std::cout << "=== All Basic Conversion Private Tests Passed! ===" << std::endl;
    return 0;
}
