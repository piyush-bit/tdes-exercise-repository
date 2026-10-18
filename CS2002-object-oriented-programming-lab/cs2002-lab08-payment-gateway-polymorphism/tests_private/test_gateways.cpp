#include "payment_gateway.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

static bool approxEqual(double a, double b, double epsilon = 0.001) {
    return std::abs(a - b) < epsilon;
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << " Private Test: Gateway Specific Implementations" << std::endl;
    std::cout << "==========================================" << std::endl;

    int passed = 0;
    int failed = 0;

    // Test 1: Stripe Validation and Fee Rules
    {
        std::cout << "[Test 1] Stripe Implementation Rules ... ";
        StripeProcessor stripeValid("sk_live_valid_key");
        StripeProcessor stripeInvalid("");

        bool p1 = stripeValid.processPayment(100.0); // fee: 2.90 + 0.30 = 3.20
        bool p2 = stripeValid.processPayment(-10.0); // fail
        bool p3 = stripeInvalid.processPayment(100.0); // fail

        if (p1 && !p2 && !p3 &&
            approxEqual(stripeValid.calculateFee(100.0), 3.20) &&
            approxEqual(stripeValid.calculateFee(0.0), 0.0) &&
            approxEqual(stripeInvalid.calculateFee(100.0), 0.0) &&
            stripeValid.getSuccessfulTransactions() == 1 &&
            stripeValid.getFailedTransactions() == 1 &&
            approxEqual(stripeValid.getTotalVolumeProcessed(), 100.0)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    // Test 2: PayPal Validation and Upper Bound Cap Rules
    {
        std::cout << "[Test 2] PayPal Implementation Rules ... ";
        PayPalProcessor paypalValid("buyer@domain.com");
        PayPalProcessor paypalBadEmail("invalid_email_format");

        bool p1 = paypalValid.processPayment(500.0); // fee: 17.45 + 0.49 = 17.94
        bool p2 = paypalValid.processPayment(10000.01); // Exceeds $10,000 cap -> fail
        bool p3 = paypalBadEmail.processPayment(50.0); // Bad email -> fail

        if (p1 && !p2 && !p3 &&
            approxEqual(paypalValid.calculateFee(500.0), 17.94) &&
            approxEqual(paypalValid.calculateFee(15000.0), 0.0) &&
            paypalValid.getSuccessfulTransactions() == 1 &&
            paypalValid.getFailedTransactions() == 1 &&
            approxEqual(paypalValid.getTotalVolumeProcessed(), 500.0)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    // Test 3: Crypto Minimum Threshold and Address Validation Rules
    {
        std::cout << "[Test 3] Crypto Implementation Rules ... ";
        CryptoProcessor cryptoValid("0x1234567890ABCDEF");
        CryptoProcessor cryptoShortWallet("0x1234");
        CryptoProcessor cryptoNoPrefix("1234567890ABCDEF");

        bool p1 = cryptoValid.processPayment(100.0); // fee: flat $1.50
        bool p2 = cryptoValid.processPayment(4.99); // Under $5.00 threshold -> fail
        bool p3 = cryptoShortWallet.processPayment(100.0); // Short wallet -> fail
        bool p4 = cryptoNoPrefix.processPayment(100.0); // No 0x prefix -> fail

        if (p1 && !p2 && !p3 && !p4 &&
            approxEqual(cryptoValid.calculateFee(100.0), 1.50) &&
            approxEqual(cryptoValid.calculateFee(3.0), 0.0) &&
            approxEqual(cryptoShortWallet.calculateFee(100.0), 0.0) &&
            cryptoValid.getSuccessfulTransactions() == 1 &&
            cryptoValid.getFailedTransactions() == 1 &&
            approxEqual(cryptoValid.getTotalVolumeProcessed(), 100.0)) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
            failed++;
        }
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << " Gateway Implementation Tests: " << passed << " passed, " << failed << " failed." << std::endl;
    std::cout << "==========================================" << std::endl;

    return (failed == 0) ? 0 : 1;
}
