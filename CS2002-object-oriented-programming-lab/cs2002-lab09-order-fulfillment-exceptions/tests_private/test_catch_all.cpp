#include "order_fulfillment.hpp"
#include <iostream>
#include <cassert>
#include <string>

int main() {
    std::cout << "[Grading] Running Test Suite: Catch-All & Exception Ordering...\n";
    OrderProcessor processor;

    // 1. Stock Error catching precedence
    {
        Order oStock{"ORD-701", "Graphics Card", 2, 1, 799.99, true, false, false};
        std::string res = executeOrderPipeline(oStock, processor);
        assert(res.rfind("STOCK_ERROR:", 0) == 0 && "Must return string starting with STOCK_ERROR:");
        assert(res.find("Graphics Card") != std::string::npos);
        std::cout << "  - Specific InsufficientStockException handler verified\n";
    }

    // 2. Payment Error catching precedence
    {
        Order oPayment{"ORD-702", "CPU", 1, 10, 349.99, false, false, false};
        std::string res = executeOrderPipeline(oPayment, processor);
        assert(res.rfind("PAYMENT_ERROR:", 0) == 0 && "Must return string starting with PAYMENT_ERROR:");
        assert(res.find("ORD-702") != std::string::npos);
        std::cout << "  - Specific PaymentFailedException handler verified\n";
    }

    // 3. Standard Exception catching
    {
        Order oStdError{"ORD-703", "RAM", 1, 10, 89.99, true, true, false};
        std::string res = executeOrderPipeline(oStdError, processor);
        assert(res.rfind("STANDARD_ERROR:", 0) == 0 && "Must return string starting with STANDARD_ERROR:");
        assert(res.find("Database connection failed") != std::string::npos);
        std::cout << "  - std::exception fallback handler verified\n";
    }

    // 4. Catch-All (...) Fallback Handler for unknown exception
    {
        Order oUnknown{"ORD-704", "SSD", 1, 10, 119.99, true, false, true};
        std::string res = executeOrderPipeline(oUnknown, processor);
        assert(res == "UNKNOWN_ERROR: Handled by catch-all fallback handler");
        std::cout << "  - catch(...) fallback handler verified\n";
    }

    // 5. Success Path
    {
        Order oSuccess{"ORD-705", "Power Supply", 1, 5, 99.99, true, false, false};
        std::string res = executeOrderPipeline(oSuccess, processor);
        assert(res == "SUCCESS: Order ORD-705 processed successfully");
        std::cout << "  - Success execution path verified\n";
    }

    std::cout << "[PASS] All Catch-All and exception pipeline tests passed!\n";
    return 0;
}
