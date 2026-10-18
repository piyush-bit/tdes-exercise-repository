#include "order_fulfillment.hpp"
#include <iostream>
#include <cassert>
#include <string>

int main() {
    std::cout << "Running Public Tests for Order Fulfillment Exception Engine...\n";

    OrderProcessor processor;

    // Test 1: Exception throwing - Stock
    {
        Order o1{"ORD-101", "Laptop", 5, 2, 999.99, true, false, false};
        bool caught = false;
        try {
            processor.processOrder(o1);
        } catch (const InsufficientStockException& e) {
            caught = true;
            assert(e.getItem() == "Laptop");
            assert(e.getRequested() == 5);
            assert(e.getAvailable() == 2);
        }
        assert(caught);
        std::cout << "[PASS] Test 1: InsufficientStockException thrown correctly\n";
    }

    // Test 2: Exception throwing - Payment
    {
        Order o2{"ORD-102", "Phone", 1, 10, 499.00, false, false, false};
        bool caught = false;
        try {
            processor.processOrder(o2);
        } catch (const PaymentFailedException& e) {
            caught = true;
            assert(e.getOrderId() == "ORD-102");
            assert(e.getAmount() == 499.00);
        }
        assert(caught);
        std::cout << "[PASS] Test 2: PaymentFailedException thrown correctly\n";
    }

    // Test 3: Pipeline Success
    {
        Order o3{"ORD-103", "Tablet", 1, 5, 299.99, true, false, false};
        std::string res = executeOrderPipeline(o3, processor);
        assert(res.rfind("SUCCESS:", 0) == 0);
        std::cout << "[PASS] Test 3: Pipeline success case handled\n";
    }

    // Test 4: Pipeline Stock Error
    {
        Order o4{"ORD-104", "Monitor", 10, 3, 199.99, true, false, false};
        std::string res = executeOrderPipeline(o4, processor);
        assert(res.rfind("STOCK_ERROR:", 0) == 0);
        std::cout << "[PASS] Test 4: Pipeline stock error caught\n";
    }

    // Test 5: Pipeline Catch-All Handler
    {
        Order o5{"ORD-105", "Keyboard", 1, 10, 49.99, true, false, true};
        std::string res = executeOrderPipeline(o5, processor);
        assert(res == "UNKNOWN_ERROR: Handled by catch-all fallback handler");
        std::cout << "[PASS] Test 5: Catch-all handler caught unknown exception\n";
    }

    std::cout << "\nAll Public Tests Passed Successfully!\n";
    return 0;
}
