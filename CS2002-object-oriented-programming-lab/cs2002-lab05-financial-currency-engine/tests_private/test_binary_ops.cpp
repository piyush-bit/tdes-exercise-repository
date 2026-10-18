#include <iostream>
#include <cassert>
#include <stdexcept>
#include "currency_engine.hpp"

int main() {
    int passed = 0;
    int failed = 0;

    std::cout << "--- Private Test Suite: Binary Operators ---" << std::endl;

    // Test 1: Addition (+)
    {
        CurrencyAmount c1(100, 50, "USD"); // 10050 cents
        CurrencyAmount c2(50, 25, "USD");  // 5025 cents
        CurrencyAmount res = c1 + c2;
        if (res.getCents() == 15075 && res.getCurrency() == "USD" && res.getDollars() == 150 && res.getCentsPart() == 75) {
            std::cout << "[PASSED] Binary Addition" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Binary Addition" << std::endl;
            failed++;
        }
    }

    // Test 2: Subtraction (-)
    {
        CurrencyAmount c1(20, 0, "EUR");
        CurrencyAmount c2(7, 50, "EUR");
        CurrencyAmount res = c1 - c2;
        if (res.getCents() == 1250 && res.getDollars() == 12 && res.getCentsPart() == 50) {
            std::cout << "[PASSED] Binary Subtraction" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Binary Subtraction" << std::endl;
            failed++;
        }
    }

    // Test 3: Negative Result Subtraction
    {
        CurrencyAmount c1(5, 0, "USD");
        CurrencyAmount c2(12, 0, "USD");
        CurrencyAmount res = c1 - c2;
        if (res.getCents() == -700 && res.getDollars() == -7 && res.getCentsPart() == 0) {
            std::cout << "[PASSED] Negative Result Subtraction" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Negative Result Subtraction" << std::endl;
            failed++;
        }
    }

    // Test 4: Equality (==)
    {
        CurrencyAmount c1(15, 99, "GBP");
        CurrencyAmount c2(15, 99, "GBP");
        CurrencyAmount c3(15, 99, "USD");
        CurrencyAmount c4(15, 98, "GBP");

        if ((c1 == c2) && !(c1 == c3) && !(c1 == c4)) {
            std::cout << "[PASSED] Equality Operator" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Equality Operator" << std::endl;
            failed++;
        }
    }

    // Test 5: Compound Addition (+=)
    {
        CurrencyAmount c1(10, 0, "USD");
        CurrencyAmount c2(4, 50, "USD");
        CurrencyAmount& ref = (c1 += c2);

        if (c1.getCents() == 1450 && &ref == &c1) {
            std::cout << "[PASSED] Compound Addition (+=" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Compound Addition (+=" << std::endl;
            failed++;
        }
    }

    // Test 6: Currency Mismatch Exception Handling
    {
        CurrencyAmount c_usd(10, 0, "USD");
        CurrencyAmount c_eur(10, 0, "EUR");
        bool threw_add = false;
        bool threw_sub = false;
        bool threw_compound = false;

        try {
            (void)(c_usd + c_eur);
        } catch (const std::invalid_argument&) {
            threw_add = true;
        }

        try {
            (void)(c_usd - c_eur);
        } catch (const std::invalid_argument&) {
            threw_sub = true;
        }

        try {
            c_usd += c_eur;
        } catch (const std::invalid_argument&) {
            threw_compound = true;
        }

        if (threw_add && threw_sub && threw_compound) {
            std::cout << "[PASSED] Currency Mismatch Exceptions" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Currency Mismatch Exceptions" << std::endl;
            failed++;
        }
    }

    std::cout << "Binary Operators Test Summary: " << passed << " passed, " << failed << " failed." << std::endl;
    return (failed == 0) ? 0 : 1;
}
