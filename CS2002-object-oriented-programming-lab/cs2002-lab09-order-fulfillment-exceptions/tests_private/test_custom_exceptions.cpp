#include "order_fulfillment.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <typeinfo>

int main() {
    std::cout << "[Grading] Running Test Suite: Custom Exceptions...\n";
    OrderProcessor processor;

    // 1. Hierarchy test for InsufficientStockException
    {
        InsufficientStockException ex("Widget", 10, 3);
        const std::exception* basePtr = dynamic_cast<const std::exception*>(&ex);
        assert(basePtr != nullptr && "InsufficientStockException must inherit from std::exception");
        assert(ex.getItem() == "Widget");
        assert(ex.getRequested() == 10);
        assert(ex.getAvailable() == 3);
        std::string msg = ex.what();
        assert(msg.find("Widget") != std::string::npos);
        assert(msg.find("10") != std::string::npos);
        assert(msg.find("3") != std::string::npos);
        std::cout << "  - InsufficientStockException class design & getters verified\n";
    }

    // 2. Hierarchy test for PaymentFailedException
    {
        PaymentFailedException ex("ORD-999", 125.50, "Card expired");
        const std::exception* basePtr = dynamic_cast<const std::exception*>(&ex);
        assert(basePtr != nullptr && "PaymentFailedException must inherit from std::exception");
        assert(ex.getOrderId() == "ORD-999");
        assert(ex.getAmount() == 125.50);
        assert(ex.getReason() == "Card expired");
        std::string msg = ex.what();
        assert(msg.find("ORD-999") != std::string::npos);
        assert(msg.find("Card expired") != std::string::npos);
        std::cout << "  - PaymentFailedException class design & getters verified\n";
    }

    // 3. Stock boundary testing in OrderProcessor
    {
        // Equal stock (should succeed)
        Order oEqual{"ORD-001", "Headphones", 5, 5, 50.0, true, false, false};
        try {
            processor.processOrder(oEqual);
        } catch (...) {
            assert(false && "Equal stock should not throw an exception");
        }

        // Low stock by 1
        Order oLow{"ORD-002", "Headphones", 6, 5, 50.0, true, false, false};
        bool caughtStock = false;
        try {
            processor.processOrder(oLow);
        } catch (const InsufficientStockException& e) {
            caughtStock = true;
            assert(e.getItem() == "Headphones");
            assert(e.getRequested() == 6);
            assert(e.getAvailable() == 5);
        } catch (...) {
            assert(false && "Should throw InsufficientStockException");
        }
        assert(caughtStock);
        std::cout << "  - Stock boundary conditions verified\n";
    }

    // 4. Precedence test (Stock check takes precedence over payment check)
    {
        Order oBothBad{"ORD-003", "Mouse", 10, 2, 20.0, false, false, false};
        bool stockCaughtFirst = false;
        try {
            processor.processOrder(oBothBad);
        } catch (const InsufficientStockException&) {
            stockCaughtFirst = true;
        } catch (...) {
            stockCaughtFirst = false;
        }
        assert(stockCaughtFirst && "Stock validation must take precedence over payment validation");
        std::cout << "  - Exception precedence rules verified\n";
    }

    std::cout << "[PASS] All Custom Exception tests passed!\n";
    return 0;
}
