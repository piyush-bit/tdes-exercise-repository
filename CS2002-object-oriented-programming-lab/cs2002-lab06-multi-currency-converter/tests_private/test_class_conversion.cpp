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
    std::cout << "=== Running Private Tests: Class-to-Class Conversions ===" << std::endl;

    // 1. Explicit Conversion Constructor USDollar -> EuroCurrency
    USDollar usd100(100.0);
    EuroCurrency eurFromUsd(usd100);
    assertNear(eurFromUsd.getAmount(), 85.0, 1e-4, "USDollar to EuroCurrency conversion constructor failed");
    std::cout << "[PASS] USDollar to EuroCurrency conversion constructor (rate 0.85)" << std::endl;

    // 2. Explicit Conversion Constructor EuroCurrency -> USDollar
    EuroCurrency eur85(85.0);
    USDollar usdFromEur(eur85);
    assertNear(usdFromEur.getAmount(), 100.0, 1e-4, "EuroCurrency to USDollar conversion constructor failed");
    std::cout << "[PASS] EuroCurrency to USDollar conversion constructor (rate 1.0/0.85)" << std::endl;

    // 3. Conversion Operator: USDollar -> EuroCurrency (operator EuroCurrency())
    USDollar usd200(200.0);
    EuroCurrency eurOp = static_cast<EuroCurrency>(usd200);
    assertNear(eurOp.getAmount(), 170.0, 1e-4, "operator EuroCurrency() failed");
    std::cout << "[PASS] USDollar::operator EuroCurrency()" << std::endl;

    // 4. Conversion Operator: EuroCurrency -> USDollar (operator USDollar())
    EuroCurrency eur170(170.0);
    USDollar usdOp = static_cast<USDollar>(eur170);
    assertNear(usdOp.getAmount(), 200.0, 1e-4, "operator USDollar() failed");
    std::cout << "[PASS] EuroCurrency::operator USDollar()" << std::endl;

    // 5. Roundtrip conversion USD -> EUR -> USD
    USDollar originalUsd(500.0);
    EuroCurrency intermediateEur(originalUsd);
    USDollar roundtripUsd(intermediateEur);
    assertNear(roundtripUsd.getAmount(), 500.0, 1e-4, "USD -> EUR -> USD roundtrip failed");
    std::cout << "[PASS] USD -> EUR -> USD roundtrip conversion" << std::endl;

    // 6. Helper Functions (convertUSDToEUR and convertEURToUSD)
    EuroCurrency hEur = convertUSDToEUR(USDollar(300.0));
    assertNear(hEur.getAmount(), 255.0, 1e-4, "convertUSDToEUR helper failed");

    USDollar hUsd = convertEURToUSD(EuroCurrency(255.0));
    assertNear(hUsd.getAmount(), 300.0, 1e-4, "convertEURToUSD helper failed");
    std::cout << "[PASS] convertUSDToEUR & convertEURToUSD helper functions" << std::endl;

    // 7. Custom Exchange Rate Conversion (convertWithCustomRate)
    USDollar baseUsd(100.0);
    EuroCurrency custom1 = convertWithCustomRate(baseUsd, 0.92);
    assertNear(custom1.getAmount(), 92.0, 1e-6, "convertWithCustomRate failed for rate 0.92");

    EuroCurrency custom2 = convertWithCustomRate(baseUsd, 1.15);
    assertNear(custom2.getAmount(), 115.0, 1e-6, "convertWithCustomRate failed for rate 1.15");
    std::cout << "[PASS] convertWithCustomRate dynamic FX exchange" << std::endl;

    // 8. Large value and zero conversion tests
    USDollar zeroUsd(0.0);
    EuroCurrency zeroEur(zeroUsd);
    assertNear(zeroEur.getAmount(), 0.0, 1e-6, "Zero USD to EUR failed");

    USDollar largeUsd(1e6);
    EuroCurrency largeEur(largeUsd);
    assertNear(largeEur.getAmount(), 850000.0, 1e-2, "Large USD to EUR failed");
    std::cout << "[PASS] Edge cases (zero and large values)" << std::endl;

    std::cout << "=== All Class-to-Class Private Tests Passed! ===" << std::endl;
    return 0;
}
