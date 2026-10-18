#include <iostream>
#include <cassert>
#include <sstream>
#include "currency_engine.hpp"

int main() {
    int passed = 0;
    int failed = 0;

    std::cout << "--- CS2002 Lab 05 Public Tests ---" << std::endl;

    // Test 1: Addition
    {
        CurrencyAmount c1(10, 50, "USD");
        CurrencyAmount c2(5, 25, "USD");
        CurrencyAmount result = c1 + c2;
        if (result.getCents() == 1575 && result.getCurrency() == "USD") {
            std::cout << "[PASSED] Test Addition (10.50 + 5.25 = 15.75)" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Test Addition (Expected 1575 cents USD, got " 
                      << result.getCents() << " " << result.getCurrency() << ")" << std::endl;
            failed++;
        }
    }

    // Test 2: Equality
    {
        CurrencyAmount c1(10, 50, "USD");
        CurrencyAmount c2(10, 50, "USD");
        CurrencyAmount c3(10, 50, "EUR");
        CurrencyAmount c4(5, 25, "USD");

        if ((c1 == c2) && !(c1 == c3) && !(c1 == c4)) {
            std::cout << "[PASSED] Test Equality" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Test Equality" << std::endl;
            failed++;
        }
    }

    // Test 3: Negation
    {
        CurrencyAmount c1(10, 50, "USD");
        CurrencyAmount neg_c1 = -c1;
        if (neg_c1.getCents() == -1050 && neg_c1.getCurrency() == "USD") {
            std::cout << "[PASSED] Test Unary Negation" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Test Unary Negation (Expected -1050 cents, got " 
                      << neg_c1.getCents() << ")" << std::endl;
            failed++;
        }
    }

    // Test 4: Stream Output
    {
        CurrencyAmount c1(12, 34, "USD");
        std::ostringstream oss;
        oss << c1;
        if (oss.str() == "USD 12.34") {
            std::cout << "[PASSED] Test Stream Output" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Test Stream Output (Expected 'USD 12.34', got '" 
                      << oss.str() << "')" << std::endl;
            failed++;
        }
    }

    std::cout << "\nSummary: " << passed << " passed, " << failed << " failed." << std::endl;
    return (failed == 0) ? 0 : 1;
}
