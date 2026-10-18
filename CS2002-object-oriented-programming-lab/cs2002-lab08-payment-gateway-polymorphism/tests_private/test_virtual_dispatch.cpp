#include "payment_gateway.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

static bool approxEqual(double a, double b, double epsilon = 0.001) {
    return std::abs(a - b) < epsilon;
}

// Track destructor execution for verifying virtual destructor dispatch
static int destructorCount = 0;

class DestructorTestProcessor : public PaymentProcessor {
public:
    DestructorTestProcessor() : PaymentProcessor("DestructorTest") {}
    ~DestructorTestProcessor() override {
        destructorCount++;
    }
    bool processPayment(double amount) override {
        (void)amount;
        return true;
    }
    double calculateFee(double amount) const override {
        (void)amount;
        return 0.0;
    }
};

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << " Private Test: Virtual Dispatch & Polymorphism" << std::endl;
    std::cout << "==========================================" << std::endl;

    int passed = 0;
    int failed = 0;

    // Test 1: Polymorphic Dispatch via Vector of Base Pointers
    {
        std::cout << "[Test 1] Vector of PaymentProcessor Pointers ... ";
        StripeProcessor s1("key_1");
        PayPalProcessor p1("user1@test.com");
        CryptoProcessor c1("0xabcdef123456789");

        std::vector<PaymentProcessor*> queue = { &s1, &p1, &c1 };
        int successCount = 0;
        double totalVolume = 0.0;

        for (auto* proc : queue) {
            if (proc->processPayment(150.0)) {
                successCount++;
            }
            totalVolume += proc->getTotalVolumeProcessed();
        }

        if (successCount == 3 && approxEqual(totalVolume, 450.0)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL (Success: " << successCount << ", Vol: " << totalVolume << ")" << std::endl;
            failed++;
        }
    }

    // Test 2: Polymorphic Dispatch via C++ Reference
    {
        std::cout << "[Test 2] Base Class Reference Dispatch ... ";
        PayPalProcessor paypal("admin@service.org");
        PaymentProcessor& baseRef = paypal;

        bool ok1 = baseRef.processPayment(500.0);
        double fee = baseRef.calculateFee(500.0);
        std::string name = baseRef.getGatewayName();

        if (ok1 && approxEqual(fee, 17.94) && name == "PayPal") {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    // Test 3: Virtual Destructor Dispatch
    {
        std::cout << "[Test 3] Virtual Destructor Cleanup ... ";
        destructorCount = 0;
        PaymentProcessor* dynamicProc = new DestructorTestProcessor();
        delete dynamicProc; // Must invoke ~DestructorTestProcessor() via virtual ~PaymentProcessor()

        if (destructorCount == 1) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL (Destructor count: " << destructorCount << ")" << std::endl;
            failed++;
        }
    }

    // Test 4: PaymentGatewayEngine Dynamic Engine Batch & Fees
    {
        std::cout << "[Test 4] Engine Clear & Re-register ... ";
        StripeProcessor stripe("sk_test_99");
        PayPalProcessor paypal("shop@store.com");

        PaymentGatewayEngine engine;
        engine.registerProcessor(&stripe);
        engine.registerProcessor(&paypal);
        assert(engine.getProcessorCount() == 2);

        int batch1 = engine.processBatch(50.0);
        engine.clearProcessors();

        if (batch1 == 2 && engine.getProcessorCount() == 0) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << " Virtual Dispatch Tests: " << passed << " passed, " << failed << " failed." << std::endl;
    std::cout << "==========================================" << std::endl;

    return (failed == 0) ? 0 : 1;
}
