#include <iostream>
#include <cassert>
#include <sstream>
#include "currency_engine.hpp"

int main() {
    int passed = 0;
    int failed = 0;

    std::cout << "--- Private Test Suite: Unary Operators ---" << std::endl;

    // Test 1: Unary Negation (-)
    {
        CurrencyAmount c1(10, 50, "USD"); // 1050 cents
        CurrencyAmount neg1 = -c1;
        CurrencyAmount double_neg = -neg1;

        if (neg1.getCents() == -1050 && neg1.getCurrency() == "USD" && double_neg.getCents() == 1050) {
            std::cout << "[PASSED] Unary Negation" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Unary Negation" << std::endl;
            failed++;
        }
    }

    // Test 2: Prefix Increment (++c)
    {
        CurrencyAmount c(9, 99, "EUR"); // 999 cents
        CurrencyAmount& ref = ++c;      // should become 1000 cents (10.00 EUR)

        if (c.getCents() == 1000 && c.getDollars() == 10 && c.getCentsPart() == 0 && &ref == &c) {
            std::cout << "[PASSED] Prefix Increment" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Prefix Increment" << std::endl;
            failed++;
        }
    }

    // Test 3: Postfix Increment (c++)
    {
        CurrencyAmount c(9, 99, "JPY"); // 999 cents
        CurrencyAmount prev = c++;       // prev should be 999, c should be 1000

        if (prev.getCents() == 999 && c.getCents() == 1000) {
            std::cout << "[PASSED] Postfix Increment" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Postfix Increment" << std::endl;
            failed++;
        }
    }

    // Test 4: Chained Prefix Increments (++++c)
    {
        CurrencyAmount c(5, 0, "USD"); // 500 cents
        ++++c;                        // should become 502 cents

        if (c.getCents() == 502 && c.getCentsPart() == 2) {
            std::cout << "[PASSED] Chained Prefix Increment" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Chained Prefix Increment" << std::endl;
            failed++;
        }
    }

    // Test 5: Output Formatting (operator<<)
    {
        CurrencyAmount c_pos(12, 5, "USD");   // USD 12.05
        CurrencyAmount c_neg(-12, 5, "EUR");  // EUR -12.05
        CurrencyAmount c_zero(0, 0, "GBP");   // GBP 0.00

        std::ostringstream os1, os2, os3;
        os1 << c_pos;
        os2 << c_neg;
        os3 << c_zero;

        if (os1.str() == "USD 12.05" && os2.str() == "EUR -12.05" && os3.str() == "GBP 0.00") {
            std::cout << "[PASSED] Output Formatting" << std::endl;
            passed++;
        } else {
            std::cout << "[FAILED] Output Formatting (Got: '" << os1.str() << "', '" 
                      << os2.str() << "', '" << os3.str() << "')" << std::endl;
            failed++;
        }
    }

    std::cout << "Unary Operators Test Summary: " << passed << " passed, " << failed << " failed." << std::endl;
    return (failed == 0) ? 0 : 1;
}
