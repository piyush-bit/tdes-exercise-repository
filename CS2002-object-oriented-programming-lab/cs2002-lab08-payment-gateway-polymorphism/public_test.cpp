#include "payment_gateway.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

// Helper macro for testing double equality
static bool approxEqual(double a, double b, double epsilon = 0.001) {
    return std::abs(a - b) < epsilon;
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << " CS2002 Lab 08: Public Test Suite" << std::endl;
    std::cout << "==========================================" << std::endl;

    int passed = 0;
    int failed = 0;

    // Test 1: Dynamic dispatch via Base Pointer for Stripe
    {
        std::cout << "[Test 1] Stripe Polymorphic Dispatch ... ";
        StripeProcessor stripe("sk_live_test_12345");
        PaymentProcessor* basePtr = &stripe;

        if (basePtr->getGatewayName() == "Stripe" &&
            basePtr->processPayment(100.0) &&
            approxEqual(basePtr->calculateFee(100.0), 3.20) &&
            approxEqual(basePtr->getTotalVolumeProcessed(), 100.0)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    // Test 2: Dynamic dispatch via Base Pointer for PayPal
    {
        std::cout << "[Test 2] PayPal Polymorphic Dispatch ... ";
        PayPalProcessor paypal("user@example.com");
        PaymentProcessor* basePtr = &paypal;

        if (basePtr->getGatewayName() == "PayPal" &&
            basePtr->processPayment(200.0) &&
            approxEqual(basePtr->calculateFee(200.0), 7.47) &&
            approxEqual(basePtr->getTotalVolumeProcessed(), 200.0)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    // Test 3: Dynamic dispatch via Base Pointer for Crypto
    {
        std::cout << "[Test 3] Crypto Polymorphic Dispatch ... ";
        CryptoProcessor crypto("0x1234567890abcdef");
        PaymentProcessor* basePtr = &crypto;

        if (basePtr->getGatewayName() == "Crypto" &&
            basePtr->processPayment(50.0) &&
            approxEqual(basePtr->calculateFee(50.0), 1.50) &&
            approxEqual(basePtr->getTotalVolumeProcessed(), 50.0)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    // Test 4: PaymentGatewayEngine Batch Processing
    {
        std::cout << "[Test 4] PaymentGatewayEngine Batch Processing ... ";
        StripeProcessor stripe("sk_live_abc");
        PayPalProcessor paypal("vendor@store.com");
        CryptoProcessor crypto("0xdeadbeef12345678");

        PaymentGatewayEngine engine;
        engine.registerProcessor(&stripe);
        engine.registerProcessor(&paypal);
        engine.registerProcessor(&crypto);

        int successfulCount = engine.processBatch(100.0);
        double totalFees = engine.calculateTotalFees(100.0);

        // Fees: Stripe (3.20) + PayPal (3.98) + Crypto (1.50) = 8.68
        if (engine.getProcessorCount() == 3 &&
            successfulCount == 3 &&
            approxEqual(totalFees, 8.68)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL (Count: " << successfulCount << ", Fees: " << totalFees << ")" << std::endl;
            failed++;
        }
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << " Summary: " << passed << " passed, " << failed << " failed." << std::endl;
    std::cout << "==========================================" << std::endl;

    return (failed == 0) ? 0 : 1;
}
